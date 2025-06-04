import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Header
from nav_msgs.msg import Path
from traj_planning_msg.msg import PathList
from scipy.spatial.transform import Rotation as R
from std_msgs.msg import Float64
from rclpy.qos import QoSProfile, QoSDurabilityPolicy
import random
import carla
import numpy as np


class TrajectorySelecter(Node):
    def __init__(self):
        super().__init__('trajectory_selecter')
        
        self.subscription = self.create_subscription(PathList, 
                                                     '/carla/hero/traj_list', 
                                                     self.path_callback,
                                                     10)

        qos = QoSProfile(depth=10)
        qos.durability = QoSDurabilityPolicy.TRANSIENT_LOCAL

        self.path_publisher = self.create_publisher(Path, '/carla/hero/waypoints', qos)
        self.speed_publisher = self.create_publisher(Float64, '/carla/hero/speed_command', qos)

        self.interval = 2.0  # meters between waypoints
        self.num_points = 10

        # Initialize CARLA client
        self.client = carla.Client('localhost', 2000)
        self.client.set_timeout(2.0)
        self.world = self.client.get_world()
        self.carla_map = self.world.get_map()


    def path_callback(self, msg: PathList):
        
        path_list = msg.paths

        # policy selection, naive for now
        # index = random.randint(0,2)

        bounds_costs = np.zeros((len(path_list)))
        for idx, path in enumerate(path_list):
            bounds_costs[idx] = self.evaluate_path(path)

        selected_idx = np.argmin(bounds_costs)
        selected_traj = path_list[selected_idx]
        selected_traj.header.stamp = self.get_clock().now().to_msg()
        self.path_publisher.publish(selected_traj)

        speed = Float64()
        speed.data = 10.0
        self.speed_publisher.publish(speed)

        print(f"Published selected trajectory {selected_idx} at speed {speed.data} m/s")


    def evaluate_path(self, path: Path):
        total_deviation = 0.0
        valid_points = 0

        for pose_stamped in path.poses:
            pose = pose_stamped.pose
            location = carla.Location(
                x=pose.position.x,
                y=pose.position.y,
                z=pose.position.z
            )
            try:
                waypoint = self.carla_map.get_waypoint(
                    location,
                    project_to_road=True,
                    lane_type=carla.LaneType.Driving
                )
                centerline_location = waypoint.transform.location
                deviation = location.distance(centerline_location)
                total_deviation += deviation
                valid_points += 1
            except Exception as e:
                self.get_logger().warn(f"Waypoint not found for location {location}: {e}")
                continue

        if valid_points == 0:
            return float('inf')  # Penalize paths with no valid points

        return total_deviation


def main(args=None):
    print("Trajectory Selecter")
    rclpy.init(args=args)
    node = TrajectorySelecter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()