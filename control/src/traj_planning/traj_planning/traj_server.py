import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry, Path
from geometry_msgs.msg import Quaternion, PoseStamped
from std_msgs.msg import Header
from tf_transformations import euler_from_quaternion
from scipy.spatial.transform import Rotation as R
from traj_planning_msg.msg import PathList

from tf_transformations import quaternion_from_euler
from math import cos, sin, atan2, tan, hypot
import numpy as np
from traj_planning.constants import *
from itertools import product

def generate_combinations(numbers, num_picks):
    """
    Generate all possible combinations of choices by picking `num_picks` times from the list `numbers`.

    Parameters:
    - numbers (list[int]): The list of numbers to pick from.
    - num_picks (int): The number of times to pick.

    Returns:
    - list[list[int]]: All possible combinations of length `num_picks`.
    """
    if not numbers or num_picks <= 0:
        return []

    # Use itertools.product to generate combinations
    combinations = list(product(numbers, repeat=num_picks))
    combinations = [list(element) for element in combinations]
    return combinations


def dynamics(acc, steering, x_in, y_in, v_in, phi_in, b_in):
    """
    Computes the next state of the bicycle using a simple bicycle model.

    Parameters:
    - acc (float): Acceleration.
    - steering (float): Steering angle.
    - x_in (float): Current x-coordinate.
    - y_in (float): Current y-coordinate.
    - v_in (float): Current velocity.
    - phi_in (float): Current heading angle.
    - b_in (float): Current slip angle.

    Returns:
    - tuple[float, float, float, float, float]: Updated (x, y, v, phi, b).
    """
    # Update positions
    x_next = x_in + v_in * cos(phi_in + b_in) * DT
    y_next = y_in + v_in * sin(phi_in + b_in) * DT

    # Update heading angle
    phi_next = phi_in + (v_in / LR) * sin(b_in) * DT

    # Update velocity
    v_next = v_in + acc * DT
    # velocity limit
    if v_next > VELOCITY_LIMIT:
        v_next = VELOCITY_LIMIT
    v_next = max(0, v_next)  # Prevent negative velocity

    b_next = atan2(LR * tan(steering), LR + LF)

    return x_next, y_next, v_next, phi_next, b_next
    

class TrajectoryServer(Node):
    def __init__(self):
        super().__init__('trajectory_server')

        self.subscription_odom = self.create_subscription(
            Odometry,
            '/carla/hero/odometry',
            self.odom_callback,
            10
        )

        self.subscription_selected_path = self.create_subscription(
            Path,
            '/carla/hero/selected_waypoints',
            self.selected_path_callback,
            10
        )

        self.publisher = self.create_publisher(PathList, '/carla/hero/traj_list', 10)

        self.interval = 2.0
        self.num_points = 5
        self.threshold_distance = 4.0

        self.waiting_for_completion = False
        self.selected_path = None

        self.get_logger().info('TrajectoryServer initialized.')

    def selected_path_callback(self, msg: Path):
        self.selected_path = msg
        self.waiting_for_completion = True
        self.get_logger().info("Received selected trajectory.")

    def odom_callback(self, msg: Odometry):
        pose = msg.pose.pose
        x = pose.position.x
        y = pose.position.y

        vx = msg.twist.twist.linear.x
        vy = msg.twist.twist.linear.y
        speed = (vx**2 + vy**2) ** 0.5
        
        if self.waiting_for_completion and self.selected_path:
            last_pose = self.selected_path.poses[-1].pose.position
            dx = x - last_pose.x
            dy = y - last_pose.y
            dist = hypot(dx, dy)

            if dist < self.threshold_distance:
                self.waiting_for_completion = False
                self.get_logger().info("Trajectory completed. Publishing new one.")
                self.publish_new_trajectories(x, y, pose.orientation, speed)
            return

        if not self.waiting_for_completion:
            self.publish_new_trajectories(x, y, pose.orientation, speed)


    def publish_new_trajectories(self, x, y, orientation_q, speed):
        orientation_list = [orientation_q.x, orientation_q.y, orientation_q.z, orientation_q.w]
        _, _, yaw = euler_from_quaternion(orientation_list)

        traj_list = []
        action_choices = generate_combinations(ACTION_LST, MPC_HORIZON)

        # assuming 0 wheel slip at the instant of planning
        x_temp, y_temp, v_temp, phi_temp, b_temp = x, y, speed, yaw, 0

        for action_sequence in action_choices:

            header = Header()
            header.stamp = self.get_clock().now().to_msg()
            header.frame_id = "map"

            path = Path()
            path.header = header

            for action in action_sequence:
                acc = action[0] * ACCELERATION_INCREMENT
                steering = action[1] * STEERING_INCREMENT

                for _ in range(ACTION_INTERVAL):
                    x_temp, y_temp, v_temp, phi_temp, b_temp = dynamics(acc, steering, x_temp, y_temp, v_temp, phi_temp, b_temp)

                    # Orientation as quaternion
                    q = quaternion_from_euler(0, 0, phi_temp)

                    pose_stamped = PoseStamped()
                    pose_stamped.header = header
                    pose_stamped.pose.position.x = x_temp
                    pose_stamped.pose.position.y = y_temp
                    pose_stamped.pose.position.z = 0.0
                    pose_stamped.pose.orientation = Quaternion(x=q[0], y=q[1], z=q[2], w=q[3])

                    path.poses.append(pose_stamped)

                traj_list.append(path)

        path_list = PathList()
        path_list.paths = traj_list

        self.publisher.publish(path_list)
        self.get_logger().info(f"Published {len(traj_list)} dynamics-based trajectories.")


def main(args=None):
    rclpy.init(args=args)
    node = TrajectoryServer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
