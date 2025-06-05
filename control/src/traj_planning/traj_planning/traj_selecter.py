# import rclpy
# from rclpy.node import Node
# from nav_msgs.msg import Odometry
# from geometry_msgs.msg import PoseStamped
# from std_msgs.msg import Header
# from nav_msgs.msg import Path
# from traj_planning_msg.msg import PathList
# from scipy.spatial.transform import Rotation as R
# from std_msgs.msg import Float64
# from rclpy.qos import QoSProfile, QoSDurabilityPolicy
# import random
# import carla
# import numpy as np
# from visualization_msgs.msg import MarkerArray

# class TrajectorySelecter(Node):
#     def __init__(self):
#         super().__init__('trajectory_selecter')
        
#         self.subscription = self.create_subscription(PathList, 
#                                                      '/carla/hero/traj_list', 
#                                                      self.path_callback,
#                                                      10)
#         self.subscription = self.create_subscription(MarkerArray, 
#                                                         '/carla/road_network', 
#                                                         self.path_callback,
#                                                         10)

#         qos = QoSProfile(depth=10)
#         qos.durability = QoSDurabilityPolicy.TRANSIENT_LOCAL

#         self.path_publisher = self.create_publisher(Path, '/carla/hero/waypoints', qos)
#         self.speed_publisher = self.create_publisher(Float64, '/carla/hero/speed_command', qos)

#         self.interval = 2.0  # meters between waypoints
#         self.num_points = 10

#         # Initialize CARLA client
#         self.client = carla.Client('localhost', 2000)
#         self.client.set_timeout(2.0)
#         self.world = self.client.get_world()
#         self.carla_map = self.world.get_map()


#     def path_callback(self, msg: PathList):
        
#         path_list = msg.paths

#         # policy selection, naive for now
#         # index = random.randint(0,2)

#         bounds_costs = np.zeros((len(path_list)))
#         for idx, path in enumerate(path_list):
#             bounds_costs[idx] = self.evaluate_path(path)

#         selected_idx = np.argmin(bounds_costs)
#         selected_traj = path_list[selected_idx]
#         selected_traj.header.stamp = self.get_clock().now().to_msg()
#         self.path_publisher.publish(selected_traj)

#         speed = Float64()
#         speed.data = 10.0
#         self.speed_publisher.publish(speed)

#         print(bounds_costs)
#         print(f"Published selected trajectory {selected_idx} at speed {speed.data} m/s")


#     def evaluate_path(self, path: Path):
#         total_deviation = 0.0
#         valid_points = 0

#         for pose_stamped in path.poses:
#             pose = pose_stamped.pose
#             location = carla.Location(
#                 x=pose.position.x,
#                 y=pose.position.y,
#                 z=pose.position.z
#             )
#             try:
#                 waypoint = self.carla_map.get_waypoint(
#                     location,
#                     project_to_road=True,
#                     lane_type=carla.LaneType.Driving
#                 )
#                 centerline_location = waypoint.transform.location
#                 deviation = location.distance(centerline_location)
#                 total_deviation += deviation
#                 valid_points += 1
#             except Exception as e:
#                 self.get_logger().warn(f"Waypoint not found for location {location}: {e}")
#                 continue

#         if valid_points == 0:
#             return float('inf')  # Penalize paths with no valid points

#         return total_deviation


# def main(args=None):
#     print("Trajectory Selecter")
#     rclpy.init(args=args)
#     node = TrajectorySelecter()
#     rclpy.spin(node)
#     node.destroy_node()
#     rclpy.shutdown()


# if __name__ == '__main__':
#     main()

import rclpy
from rclpy.node import Node
from nav_msgs.msg import Path
from visualization_msgs.msg import MarkerArray
from traj_planning_msg.msg import PathList
from geometry_msgs.msg import Point
from std_msgs.msg import Float64, Header
from rclpy.qos import QoSProfile, QoSDurabilityPolicy
import numpy as np

class TrajectorySelecter(Node):
    def __init__(self):
        super().__init__('trajectory_selecter')

        self.subscription = self.create_subscription(
            PathList, '/carla/hero/traj_list', self.path_callback, 10)

        self.road_network_sub = self.create_subscription(
            MarkerArray, '/carla_road_network', self.road_network_callback, 10)

        qos = QoSProfile(depth=10)
        qos.durability = QoSDurabilityPolicy.TRANSIENT_LOCAL

        self.path_publisher = self.create_publisher(Path, '/carla/hero/waypoints', qos)
        self.speed_publisher = self.create_publisher(Float64, '/carla/hero/speed_command', qos)

        self.road_segments = []  # List of tuples: (Point, Point)

        self.get_logger().info("TrajectorySelecter initialized using MarkerArray for road map.")

    def road_network_callback(self, msg: MarkerArray):
        self.road_segments.clear()
        for marker in msg.markers:
            if marker.type != marker.LINE_STRIP or len(marker.points) < 2:
                continue  # skip non-line markers or degenerate lines

            # Convert LINE_STRIP points into line segments
            for i in range(len(marker.points) - 1):
                p1 = marker.points[i]
                p2 = marker.points[i + 1]
                self.road_segments.append((p1, p2))
        
        self.get_logger().info(f"Loaded {len(self.road_segments)} road line segments from MarkerArray.")


    def path_callback(self, msg: PathList):
        path_list = msg.paths

        if not self.road_segments:
            self.get_logger().warn("No road network received yet.")
            return

        bounds_costs = np.zeros(len(path_list))
        for idx, path in enumerate(path_list):
            bounds_costs[idx] = self.evaluate_path(path)

        selected_idx = np.argmin(bounds_costs)
        selected_traj = path_list[selected_idx]
        selected_traj.header.stamp = self.get_clock().now().to_msg()
        self.path_publisher.publish(selected_traj)

        speed = Float64()
        speed.data = 10.0
        self.speed_publisher.publish(speed)

        self.get_logger().info(f"Published selected trajectory {selected_idx} at speed {speed.data} m/s")

    def evaluate_path(self, path: Path):
        total_deviation = 0.0
        valid_points = 0

        for pose_stamped in path.poses:
            p = pose_stamped.pose.position
            point = np.array([p.x, p.y, p.z])
            min_dist = float('inf')

            for start, end in self.road_segments:
                a = np.array([start.x, start.y, start.z])
                b = np.array([end.x, end.y, end.z])
                ab = b - a
                ap = point - a
                t = np.clip(np.dot(ap, ab) / np.dot(ab, ab), 0.0, 1.0)
                closest = a + t * ab
                dist = np.linalg.norm(point - closest)
                if dist < min_dist:
                    min_dist = dist

            if min_dist < float('inf'):
                total_deviation += min_dist
                valid_points += 1

        if valid_points == 0:
            return float('inf')

        return total_deviation / valid_points


def main(args=None):
    rclpy.init(args=args)
    node = TrajectorySelecter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
