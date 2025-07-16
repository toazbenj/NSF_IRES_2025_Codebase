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
from local_planner.cost_utils import project_point_to_reference_trajectory


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

        self.subscription_global_path = self.create_subscription(
            Path,
            '/waypoints',
            self.global_path_callback,
            10
        )
        self.global_path = None


        self.publisher = self.create_publisher(TrajectoryList, '/ego_racecar/traj_list', 10)

        self.selected_path = None
        self.latest_pose = None
        self.paused = False
        self.is_first_publish = True

        self.create_subscription(Bool, '/pause_state', self.pause_callback, 10)

        # Timer to trigger trajectory publishing
        self.timer = self.create_timer(ACTION_INTERVAL, self.timer_callback)

        self.get_logger().info('TrajectoryServer initialized.')

    def global_path_callback(self, msg: Path):
        self.global_path = msg

    def selected_path_callback(self, msg: Path):
        if self.paused:
            return

        self.selected_path = msg
        self.get_logger().info("Received selected trajectory.")
        self.is_first_publish = True


    def odom_callback(self, msg: Odometry):
        if self.paused:
            return

        self.latest_pose = msg

    #     pose = msg.pose.pose
    #     x = float(pose.position.x)
    #     y = float(pose.position.y)

    #     vx = float(msg.twist.twist.linear.x)
    #     vy = float(msg.twist.twist.linear.y)
    #     speed = float((vx**2 + vy**2) ** 0.5)

    #     if self.selected_path is None:
    #         self.publish_new_trajectories(x, y, pose.orientation, speed)
    #         return

    #     # Compute distance along the selected trajectory
    #     total_dist = 0.0
    #     for i in range(len(self.selected_path.poses) - 1):
    #         p1 = self.selected_path.poses[i].pose.position
    #         p2 = self.selected_path.poses[i + 1].pose.position
    #         total_dist += hypot(p2.x - p1.x, p2.y - p1.y)

    #     # Find closest point on the path
    #     _, _, closest_idx = project_point_to_reference_trajectory(pose.position, self.selected_path)

    #     # Compute progress ratio
    #     covered_dist = 0.0
    #     for i in range(closest_idx):
    #         p1 = self.selected_path.poses[i].pose.position
    #         p2 = self.selected_path.poses[i + 1].pose.position
    #         covered_dist += hypot(p2.x - p1.x, p2.y - p1.y)

    #     progress_ratio = covered_dist / total_dist if total_dist > 0 else 0
    #     self.get_logger().info(f"Progress Ratio: {progress_ratio}")


    #     # self.get_logger().info("Odom callback")

    #     if progress_ratio >= PROGRESS_RESET_RATIO and self.is_first_publish:
    #         self.publish_new_trajectories(x, y, pose.orientation, speed)
    #         self.is_first_publish = False

    def timer_callback(self):
        if self.paused or self.latest_pose is None:
            return

        pose = self.latest_pose.pose.pose
        x = float(pose.position.x)
        y = float(pose.position.y)

        vx = float(self.latest_pose.twist.twist.linear.x)
        vy = float(self.latest_pose.twist.twist.linear.y)
        speed = float((vx**2 + vy**2) ** 0.5)

        self.publish_new_trajectories(x, y, pose.orientation, speed)

    def publish_new_trajectories(self, x, y, orientation_q, speed):
        if self.paused:
            return

        orientation_list = [orientation_q.x, orientation_q.y, orientation_q.z, orientation_q.w]
        _, _, yaw = euler_from_quaternion(orientation_list)
        yaw = float(yaw)
        # yaw = self.get_tangent_yaw_from_path(x, y) if self.global_path else float(yaw)

        traj_list = []
        action_choices = generate_combinations(ACTION_LST, MPC_HORIZON)

        for action_sequence in action_choices:
            x_temp, y_temp, v_temp, phi_temp, b_temp = x, y, speed, yaw, 0

            header = Header()
            header.stamp = self.get_clock().now().to_msg()
            header.frame_id = "map"

            traj = Trajectory()
            traj.header = header

            for action in action_sequence:
                acc = action[0] * ACCELERATION_INCREMENT
                steering = action[1] * STEERING_INCREMENT

                for _ in range(int(ACTION_INTERVAL/DT)):
                    x_temp, y_temp, v_temp, phi_temp, b_temp = dynamics(
                        acc, steering, x_temp, y_temp, v_temp, phi_temp, b_temp
                    )

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
        self.get_logger().info("Trajectory list published")

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