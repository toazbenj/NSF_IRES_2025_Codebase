import rclpy
from rclpy.node import Node
from nav_msgs.msg import Path
from visualization_msgs.msg import MarkerArray
from local_planner_msgs.msg import TrajectoryList, TrajectoryList
from geometry_msgs.msg import Point
from std_msgs.msg import Float64, Header
from rclpy.qos import QoSProfile, QoSDurabilityPolicy
import numpy as np
from local_planner.constants import *
from local_planner.cost_utils import evaluate_path
from std_msgs.msg import Bool

class TrajectorySelecter(Node):
    def __init__(self):
        super().__init__('trajectory_selecter')

        self.action_space_sub = self.create_subscription(
            TrajectoryList, '/ego_racecar/traj_list', self.local_path_callback, 10)

        self.global_path_sub = self.create_subscription(
            Path, '/waypoints', self.global_path_callback, 10)

        qos = QoSProfile(depth=10)
        qos.durability = QoSDurabilityPolicy.TRANSIENT_LOCAL

        self.path_publisher = self.create_publisher(Path, '/ego_racecar/selected_waypoints', qos)
        self.speed_publisher = self.create_publisher(Float64, '/ego_racecar/speed_command', qos)

        self.reference_path = None

        self.paused = False
        self.create_subscription(Bool, '/pause_state', self.pause_callback, 10)

        self.get_logger().info("TrajectorySelecter initialized")

    def global_path_callback(self, msg: Path):
        if self.paused:
            return

        if msg != self.reference_path:
            self.reference_path = msg
            self.get_logger().info(f"New reference path received")

    def local_path_callback(self, msg: TrajectoryList):
        if self.paused:
            return

        path_list = msg.paths

        if not self.reference_path:
            self.get_logger().warn("No road network received yet.")
            return

        costs = np.zeros(len(path_list))
        for idx, path in enumerate(path_list):
            costs[idx] = evaluate_path(path.path, self.reference_path)

        self.get_logger().info(f"Costs: {costs}")

        selected_idx = np.argmin(costs)
        selected_traj = path_list[selected_idx]
        selected_traj.header.stamp = self.get_clock().now().to_msg()

        self.path_publisher.publish(selected_traj.path)
        self.speed_publisher.publish(selected_traj.speed)

        self.get_logger().info(f"Published selected trajectory {selected_idx} at speed {selected_traj.speed.data} m/s")

    def pause_callback(self, msg):
        self.paused = msg.data

def main(args=None):
    rclpy.init(args=args)
    node = TrajectorySelecter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
