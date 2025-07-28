import rclpy
from rclpy.node import Node
from local_planner_msgs.msg import TrajectoryList, Trajectory
from geometry_msgs.msg import Point
from nav_msgs.msg import Path, Odometry
from visualization_msgs.msg import Marker, MarkerArray
from std_msgs.msg import ColorRGBA
from local_planner import cost_utils
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import OccupancyGrid, MapMetaData
from tf_transformations import euler_from_quaternion
import math


class TrajectoryVisualizer(Node):
    def __init__(self):
        super().__init__('trajectory_visualizer')

        # Declare and read parameters
        self.declare_parameter('NAMESPACE', '/ego_racecar')
        self.declare_parameter('DRIVE_TOPIC', '/drive')
        self.declare_parameter('COLOR', 'green')
        self.declare_parameter('BOUNDS_WEIGHT', 100)
        self.declare_parameter('PROGRESS_WEIGHT', 1)
        self.declare_parameter('BOUNDS_SPREAD', 5)


        self.namespace = self.get_parameter('NAMESPACE').get_parameter_value().string_value
        self.drive_topic = self.get_parameter('DRIVE_TOPIC').get_parameter_value().string_value
        self.color = self.get_parameter('COLOR').get_parameter_value().string_value
        self.bounds_weight = self.get_parameter('BOUNDS_WEIGHT').value
        self.progress_weight = self.get_parameter('PROGRESS_WEIGHT').value
        self.bounds_spread = self.get_parameter('BOUNDS_SPREAD').value


        self.get_logger().info(f"Using namespace: {self.namespace}, color: {self.color}")

        self.odom_sub = self.create_subscription(
            Odometry,
            f'{self.namespace}/odom',
            self.odom_callback,
            10
        )

        self.traj_lst_sub = self.create_subscription(
            TrajectoryList,
            f'{self.namespace}/traj_list',
            self.path_list_callback,
            10
        )

        self.selected_waypoints_sub = self.create_subscription(
            Path,
            f'{self.namespace}/selected_waypoints',
            self.selected_path_callback,
            10
        )

        self.waypoints_sub = self.create_subscription(
            Path,
            self.namespace + '/waypoints',
            self.global_path_callback,
            10
        )

        self.traj_lst_pub = self.create_publisher(MarkerArray, f'{self.namespace}/trajectories', 10)
        self.selected_traj_pub = self.create_publisher(MarkerArray, f'{self.namespace}/selected_trajectory', 10)

        # self.timer = self.create_timer(100.0, self.timer_callback)

        # self.cost_pub = self.create_publisher(MarkerArray, 'cost_map_markers', 10)
        self.cost_map_pub = self.create_publisher(OccupancyGrid, f'{self.namespace}/cost_map', 10)

        self.reference_path = None 
        self.ego_pose = None
        self.trajectory_counter = 0  # In __init__()

    def path_list_callback(self, msg: TrajectoryList):
        marker_array = MarkerArray()

        for idx, trajectory in enumerate(msg.paths):
            marker = Marker()
            marker.header = trajectory.header
            marker.ns = 'trajectories'
            marker.id = idx
            marker.type = Marker.LINE_STRIP
            marker.action = Marker.ADD
            marker.scale.x = 0.1  # Line width
            marker.color = ColorRGBA(r=1.0, g=0.0, b=0.0, a=1.0)  # Red, opaque
            marker.points = [pose.pose.position for pose in trajectory.path.poses]

            marker_array.markers.append(marker)

        self.traj_lst_pub.publish(marker_array)
        self.cost_visual_callback()

    def selected_path_callback(self, msg: Path):
        marker_array = MarkerArray()
        marker = Marker()
        marker.header = msg.header
        marker.ns = 'selected_trajectory'
        marker.id = self.trajectory_counter
        self.trajectory_counter += 1

        marker.type = Marker.LINE_STRIP
        marker.action = Marker.ADD
        marker.scale.x = 0.1  # Line width
        marker.color = ColorRGBA(r=0.0, g=0.0, b=1.0, a=1.0)  # Red, opaque
        marker.points = [pose.pose.position for pose in msg.poses]
        marker_array.markers.append(marker)

        self.selected_traj_pub.publish(marker_array)

        # self.get_logger().info("Selected Path callback")
        # self.get_logger().info(f"Selected path has {len(msg.poses)} poses")

    def cost_visual_callback(self):
        if self.reference_path is None:
            self.get_logger().warn("Reference path not available.")
            return
        
        if self.ego_pose is None:
            self.get_logger().warn("Ego pose not available.")
            return
        # self.get_logger().info("Cost callback start")

        resolution = 1.0 # meters per cell
        width = 5  # number of cells in x
        height = 5  # number of cells in y
        half_width_m = (width * resolution) / 2.0
        half_height_m = (height * resolution) / 2.0

        # origin_x = self.ego_pose.position.x - half_width_m
        # origin_y = self.ego_pose.position.y - half_height_m

        # Extract yaw from quaternion
        quat = self.ego_pose.orientation
        _, _, yaw = euler_from_quaternion([quat.x, quat.y, quat.z, quat.w])

        # Offset forward in the direction the car is facing
        offset_distance = 2.0  # meters in front of the car
        offset_x = offset_distance * math.cos(yaw)
        offset_y = offset_distance * math.sin(yaw)

        # Grid origin is slightly ahead of car
        center_x = self.ego_pose.position.x + offset_x
        center_y = self.ego_pose.position.y + offset_y

        origin_x = center_x - half_width_m
        origin_y = center_y - half_height_m

        # Compute grid of path samples
        data = []
        max_cost = -float('inf')
        min_cost = float('inf')
        paths = []

        for j in range(height):
            y = origin_y + j * resolution
            for i in range(width):
                x = origin_x + i * resolution
                path = Path()
                pose = PoseStamped()
                pose.pose.position.x = x
                pose.pose.position.y = y
                pose.pose.position.z = 0.0
                path.poses.append(pose)
                paths.append(path)

        # Compute costs
        for path in paths:
            cost = sum(cost_utils.evaluate_static_path(path, self.reference_path, self.bounds_spread))
            max_cost = max(max_cost, cost)
            min_cost = min(min_cost, cost)
            data.append(cost)

        cost_range = max(max_cost - min_cost, 1e-6)

        # Convert cost to OccupancyGrid format (0-100)
        grid = OccupancyGrid()
        grid.header.stamp = self.get_clock().now().to_msg()
        grid.header.frame_id = "map"

        grid.info = MapMetaData()
        grid.info.resolution = resolution
        grid.info.width = width
        grid.info.height = height
        grid.info.origin.position.x = origin_x
        grid.info.origin.position.y = origin_y
        grid.info.origin.position.z = 0.0
        grid.info.origin.orientation.w = 1.0

        grid_data = []
        for raw_cost in data:
            norm_cost = int(100.0 * (raw_cost - min_cost) / cost_range)
            norm_cost = min(max(norm_cost, 0), 100)
            grid_data.append(norm_cost)

        grid.data = grid_data
        self.cost_map_pub.publish(grid)

    # def timer_callback(self):
    #     if self.reference_path:
    #         self.get_logger().info("Cost visual callback triggered.")
    #         self.cost_visual_callback()


    def global_path_callback(self, msg: Path):
        if msg != self.reference_path:
            self.reference_path = msg
            self.get_logger().info(f"New reference path received")

    def odom_callback(self, msg: Odometry):
        self.ego_pose = msg.pose.pose


def main(args=None):
    rclpy.init(args=args)
    node = TrajectoryVisualizer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
