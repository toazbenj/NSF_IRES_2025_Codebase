import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry, Path
from geometry_msgs.msg import Quaternion, PoseStamped
from std_msgs.msg import Header, Float64
from tf_transformations import euler_from_quaternion
from scipy.spatial.transform import Rotation as R
from local_planner_msgs.msg import TrajectoryList, Trajectory

from tf_transformations import quaternion_from_euler
from math import cos, sin, atan2, tan, hypot
from local_planner.constants import *
from itertools import product
from std_msgs.msg import Bool


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
    - b_in (float): Current slip angle.cos

    Returns:
    - tuple[float, float, float, float, float]: Updated (x, y, v, phi, b).
    """
    # Update positions

    # issues with float types here, speed and path now included together in message

    # print(f'v_in: {v_in}')
    # print(f'phi/b_in: {cos(phi_in + b_in)}')
    # v_in = v_in.data

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
            '/ego_racecar/odom',
            self.odom_callback,
            10
        )

        self.subscription_selected_path = self.create_subscription(
            Path,
            '/ego_racecar/selected_waypoints',
            self.selected_path_callback,
            10
        )

        self.publisher = self.create_publisher(TrajectoryList, '/ego_racecar/traj_list', 10)

        self.interval = 2.0
        self.num_points = 5

        # only half of planned distance covered before replanning (meters)
        # assuming 10 m/s speed
        # self.threshold_distance = DT * ACTION_INTERVAL * 8 * MPC_HORIZON / 2
        self.threshold_distance = 0.5


        self.waiting_for_completion = False
        self.selected_path = None

        self.paused = False
        self.create_subscription(Bool, '/pause_state', self.pause_callback, 10)
        self.get_logger().info('TrajectoryServer initialized.')

    def selected_path_callback(self, msg: Path):
        if self.paused:
            return

        self.selected_path = msg
        self.waiting_for_completion = True
        self.get_logger().info("Received selected trajectory.")

    def odom_callback(self, msg: Odometry):
        if self.paused:
            return

        pose = msg.pose.pose
        x = float(pose.position.x)
        y = float(pose.position.y)

        vx = float(msg.twist.twist.linear.x)
        vy = float(msg.twist.twist.linear.y)
        speed = float((vx**2 + vy**2) ** 0.5)  # Explicitly convert to Python float
        
        # print(f'1: {speed}')

        if self.waiting_for_completion and self.selected_path:
            last_pose = self.selected_path.poses[-1].pose.position
            dx = x - last_pose.x
            dy = y - last_pose.y
            dist = hypot(dx, dy)

            if dist < self.threshold_distance:
                self.waiting_for_completion = False
                # self.get_logger().info(f"Trajectory completed. Lookahead ={self.threshold_distance}m")
                # self.get_logger().info('Serving new trajectories')
                self.publish_new_trajectories(x, y, pose.orientation, speed)
            return

        if not self.waiting_for_completion:
            # self.get_logger().info('Serving new trajectories')
            self.publish_new_trajectories(x, y, pose.orientation, speed)


    def publish_new_trajectories(self, x, y, orientation_q, speed):
        if self.paused:
            return

        orientation_list = [orientation_q.x, orientation_q.y, orientation_q.z, orientation_q.w]
        _, _, yaw = euler_from_quaternion(orientation_list)

        yaw = float(yaw)

        traj_list = []

        action_choices = generate_combinations(ACTION_LST, MPC_HORIZON)

        for action_sequence in action_choices:
            # assuming 0 wheel slip at the instant of planning
            x_temp, y_temp, v_temp, phi_temp, b_temp = x, y, speed, yaw, 0

            # print(f'2: {speed}')

            header = Header()
            header.stamp = self.get_clock().now().to_msg()
            header.frame_id = "map"

            traj = Trajectory()
            traj.header = header

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

                    traj.path.poses.append(pose_stamped)

            speed_float = Float64()
            speed_float.data = float(v_temp)
            traj.speed = speed_float
            traj_list.append(traj)

        path_list = TrajectoryList()
        path_list.paths = traj_list

        self.publisher.publish(path_list)
        # self.get_logger().info(f"Published {len(traj_list)} trajectories.")

    def pause_callback(self, msg):
        self.paused = msg.data

def main(args=None):
    rclpy.init(args=args)
    node = TrajectoryServer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
