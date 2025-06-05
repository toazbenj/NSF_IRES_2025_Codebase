import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry, Path
from geometry_msgs.msg import Quaternion, PoseStamped
from std_msgs.msg import Header
from tf_transformations import euler_from_quaternion
from scipy.spatial.transform import Rotation as R
from traj_planning_msg.msg import PathList
import math

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
            '/carla/hero/waypoints',
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

        if self.waiting_for_completion and self.selected_path:
            last_pose = self.selected_path.poses[-1].pose.position
            dx = x - last_pose.x
            dy = y - last_pose.y
            dist = math.hypot(dx, dy)

            if dist < self.threshold_distance:
                self.waiting_for_completion = False
                self.get_logger().info("Trajectory completed. Publishing new one.")
                self.publish_new_trajectories(x, y, pose.orientation)
            return

        if not self.waiting_for_completion:
            self.publish_new_trajectories(x, y, pose.orientation)


    def publish_new_trajectories(self, x, y, orientation_q):
        orientation_list = [orientation_q.x, orientation_q.y, orientation_q.z, orientation_q.w]
        _, _, yaw = euler_from_quaternion(orientation_list)

        yaw_offsets = [0.2, 0.1, 0.0, -0.1, -0.2]
        speed_set = [10.0]
        traj_list = []

        for offset in yaw_offsets:
            for speed in speed_set:
                adjusted_yaw = yaw + offset
                spacing = speed * 0.2

                header = Header()
                header.stamp = self.get_clock().now().to_msg()
                header.frame_id = "map"

                path = Path()
                path.header = header

                for i in range(1, self.num_points):
                    dx = i * spacing * math.cos(adjusted_yaw)
                    dy = i * spacing * math.sin(adjusted_yaw)
                    px = x + dx
                    py = y + dy

                    r = R.from_euler('z', adjusted_yaw / self.num_points)
                    q = r.as_quat()

                    pose_stamped = PoseStamped()
                    pose_stamped.header = header
                    pose_stamped.pose.position.x = px
                    pose_stamped.pose.position.y = py
                    pose_stamped.pose.position.z = 0.0
                    pose_stamped.pose.orientation = Quaternion(x=q[0], y=q[1], z=q[2], w=q[3])

                    path.poses.append(pose_stamped)

                traj_list.append(path)

        path_list = PathList()
        path_list.paths = traj_list

        self.publisher.publish(path_list)
        self.get_logger().info(f"Published {len(traj_list)} trajectories.")

def main(args=None):
    rclpy.init(args=args)
    node = TrajectoryServer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
