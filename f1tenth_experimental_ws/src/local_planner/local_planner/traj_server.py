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


def dynamics(acc, steering, x_in, y_in, v_in, phi_in, b_in, v_max, dt, lf, lr):
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

    x_next = x_in + v_in * cos(phi_in + b_in) * dt
    y_next = y_in + v_in * sin(phi_in + b_in) * dt

    # Update heading angle
    phi_next = phi_in + (v_in / lr) * sin(b_in) * dt

    # Update velocity
    v_next = v_in + acc * dt
    # velocity limit
    if v_next > v_max:
        v_next = v_max
    v_next = max(0, v_next)  # Prevent negative velocity

    b_next = atan2(lr * tan(steering), lr + lf)

    return x_next, y_next, v_next, phi_next, b_next

class TrajectoryServer(Node):
    def __init__(self):
        super().__init__('trajectory_server')

        # Declare parameters with defaults (used if no YAML passed)
        self.declare_parameter('NAMESPACE', '/ego_racecar')
        self.declare_parameter('STEERING_INCREMENT', 0.6109)
        self.declare_parameter('ACCELERATION_INCREMENT', 1.0)
        self.declare_parameter('PROGRESS_RESET_RATIO', 0.25)
        self.declare_parameter('ACTION_INTERVAL', 0.1)

        # parameter not loading properly for car
        self.declare_parameter('ACTION_LST', [-1.0, -1.0, 
                                                -1.0, 0.0,
                                                -1.0, 1.0, 
                                                0.0, -1.0,
                                                0.0, 0.0,
                                                0.0, 1.0,
                                                1.0, -1.0, 
                                                1.0, 0.0,
                                                1.0, 1.0, 
                                                1.0, -0.5,
                                                1.0, 0.5])

        # physical
        self.declare_parameter('GLOBAL_PATH_TOPIC', '/path')
        self.declare_parameter('ODOM_TOPIC', '/pf/pose/odom')
        self.declare_parameter('SPEED_TOPIC', '/target_speed')
        self.declare_parameter('SELECTED_PATH_TOPIC', '/ego_racecar/selected_path')

        self.declare_parameter('MAX_SPEED', 2.0)
        self.declare_parameter('DT', 0.5)
        self.declare_parameter('LF', 1)
        self.declare_parameter('LR', 1)
        self.declare_parameter('RECEDING_HORIZON', 3.0)

        # Load them from the parameter server
        self.namespace = self.get_parameter('NAMESPACE').get_parameter_value().string_value
        self.steering_increment = self.get_parameter('STEERING_INCREMENT').value
        self.acceleration_increment = self.get_parameter('ACCELERATION_INCREMENT').value
        self.progress_reset_ratio = self.get_parameter('PROGRESS_RESET_RATIO').value
        self.action_interval = self.get_parameter('ACTION_INTERVAL').value

        # physical
        self.global_path_topic = self.get_parameter('GLOBAL_PATH_TOPIC').get_parameter_value().string_value
        self.odom_topic = self.get_parameter('ODOM_TOPIC').get_parameter_value().string_value
        self.speed_topic = self.get_parameter('SPEED_TOPIC').get_parameter_value().string_value
        self.selected_path_topic = self.get_parameter('SELECTED_PATH_TOPIC').get_parameter_value().string_value

        flat = self.get_parameter('ACTION_LST').get_parameter_value().double_array_value
        self.get_logger().info(f'flat: {flat}')
        self.action_lst = [(flat[i], flat[i+1]) for i in range(0, len(flat)-1, 2)]
        self.get_logger().info(f'action space: {self.action_lst }')
        self.get_logger().info(f'ACCELERATION_INCREMENT: {self.acceleration_increment}')
        self.get_logger().info(f'namaespace: {self.namespace}')

        self.max_speed = self.get_parameter('MAX_SPEED').value
        self.dt = self.get_parameter('DT').value
        self.lf = self.get_parameter('LF').value
        self.lr = self.get_parameter('LR').value
        self.receding_horizon = self.get_parameter('RECEDING_HORIZON').value

        self.subscription_odom = self.create_subscription(
            Odometry,
            self.odom_topic,
            self.odom_callback,
            10
        )
        self.subscription_selected_path = self.create_subscription(
            Path,
            self.selected_path_topic,
            self.selected_path_callback,
            10
        )
        self.subscription_global_path = self.create_subscription(
            Path,
            self.global_path_topic,
            self.global_path_callback,
            10
        )

        self.timer = self.create_timer(self.action_interval, self.timer_callback)

        self.publisher = self.create_publisher(TrajectoryList, f'{self.namespace}/traj_list', 10)
     
        self.global_path = None
        self.selected_path = None
        self.latest_pose = None
        self.is_first_publish = True

        self.get_logger().info('TrajectoryServer initialized.')

    def global_path_callback(self, msg: Path):
        self.global_path = msg

    def selected_path_callback(self, msg: Path):
        self.selected_path = msg
        self.get_logger().info("Received selected trajectory.")
        self.is_first_publish = True


    def odom_callback(self, msg: Odometry):
        self.latest_pose = msg

    def timer_callback(self):

        # if self.latest_pose is not None:
        #     pose = self.latest_pose.pose.pose
        # else:
        #     return

        pose = self.latest_pose.pose.pose


        x = float(pose.position.x)
        y = float(pose.position.y)
        orientation = pose.orientation

        vx = float(self.latest_pose.twist.twist.linear.x)
        vy = float(self.latest_pose.twist.twist.linear.y)
        speed = float((vx ** 2 + vy ** 2) ** 0.5)

        if self.selected_path is None:
            self.publish_new_trajectories(x, y, orientation, speed)
            return

        # --- Compute progress ---
        total_dist = 0.0
        for i in range(len(self.selected_path.poses) - 1):
            p1 = self.selected_path.poses[i].pose.position
            p2 = self.selected_path.poses[i + 1].pose.position
            total_dist += hypot(p2.x - p1.x, p2.y - p1.y)

        # Find closest point index
        _, _, closest_idx = project_point_to_reference_trajectory(pose.position, self.selected_path)

        covered_dist = 0.0
        for i in range(closest_idx):
            p1 = self.selected_path.poses[i].pose.position
            p2 = self.selected_path.poses[i + 1].pose.position
            covered_dist += hypot(p2.x - p1.x, p2.y - p1.y)

        progress_ratio = covered_dist / total_dist if total_dist > 0 else 0.0

        self.get_logger().info(f"Progress ratio: {progress_ratio:.2f}")

        # Re-plan if progress exceeds threshold and first time
        if progress_ratio >= self.progress_reset_ratio and self.is_first_publish:
            self.publish_new_trajectories(x, y, orientation, speed)
            self.is_first_publish = False


    def publish_new_trajectories(self, x, y, orientation_q, speed):

        orientation_list = [orientation_q.x, orientation_q.y, orientation_q.z, orientation_q.w]
        _, _, yaw = euler_from_quaternion(orientation_list)
        yaw = float(yaw)
        # yaw = self.get_tangent_yaw_from_path(x, y) if self.global_path else float(yaw)

        # self.selected_path[-1]

        traj_list = []
        action_choices = generate_combinations(self.action_lst, 1)

        for action_sequence in action_choices:
            x_temp, y_temp, v_temp, phi_temp, b_temp = x, y, speed, yaw, 0

            header = Header()
            header.stamp = self.get_clock().now().to_msg()
            # header.frame_id = "map"
            header.frame_id = "odom"


            traj = Trajectory()
            traj.header = header

            for action in action_sequence:
                acc = action[0] * self.acceleration_increment
                steering = action[1] * self.steering_increment

                for _ in range(int(self.receding_horizon/self.dt)):
                    x_temp, y_temp, v_temp, phi_temp, b_temp = dynamics(
                        acc, steering, x_temp, y_temp, v_temp, phi_temp, b_temp, 
                        self.max_speed, self.dt, self.lf, self.lr
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


def main(args=None):
    rclpy.init(args=args)
    node = TrajectoryServer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()