import rclpy
from rclpy.node import Node
from nav_msgs.msg import Path
from visualization_msgs.msg import MarkerArray
from traj_planning_msg.msg import TrajectoryList, TrajectoryList
from geometry_msgs.msg import Point
from std_msgs.msg import Float64, Header
from rclpy.qos import QoSProfile, QoSDurabilityPolicy
import numpy as np
from traj_planning.constants import *


class TrajectorySelecter(Node):
    def __init__(self):
        super().__init__('trajectory_selecter')

        self.subscription = self.create_subscription(
            TrajectoryList, '/carla/hero/traj_list', self.local_path_callback, 10)

        self.road_network_sub = self.create_subscription(
            Path, '/carla/hero/waypoints', self.global_path_callback, 10)

        qos = QoSProfile(depth=10)
        qos.durability = QoSDurabilityPolicy.TRANSIENT_LOCAL

        self.path_publisher = self.create_publisher(Path, '/carla/hero/selected_waypoints', qos)
        self.speed_publisher = self.create_publisher(Float64, '/carla/hero/speed_command', qos)

        self.reference_path = None

        self.get_logger().info("TrajectorySelecter initialized")

    def global_path_callback(self, msg: Path):
        if msg != self.reference_path:
            self.reference_path = msg
            self.get_logger().info(f"New reference path received")

    def local_path_callback(self, msg: TrajectoryList):
        path_list = msg.paths

        if not self.reference_path:
            self.get_logger().warn("No road network received yet.")
            return

        costs = np.zeros(len(path_list))
        for idx, path in enumerate(path_list):
            costs[idx] = self.evaluate_path(path.path)

        self.get_logger().info(f"Costs: {costs}")

        selected_idx = np.argmin(costs)
        selected_traj = path_list[selected_idx]
        selected_traj.header.stamp = self.get_clock().now().to_msg()

        self.path_publisher.publish(selected_traj.path)
        self.speed_publisher.publish(selected_traj.speed)

        self.get_logger().info(f"Published selected trajectory {selected_idx} at speed {selected_traj.speed.data} m/s")

    def evaluate_path(self, path: Path):
        progress_cost = self.progress_costs(path)
        bounds_cost = self.bounds_costs(path)
        cost = RELATIVE_PROGRESS_WEIGHT_1 * progress_cost + BOUNDS_WEIGHT_1 * bounds_cost
        return cost

    def project_point_to_reference_trajectory(self, point):
        min_dist = float('inf')
        closest_ref_pt = None
        for ref_pose in self.reference_path.poses:
            rp = ref_pose.pose.position
            ref_point = np.array([rp.x, rp.y, rp.z])
            dist = np.linalg.norm(point - ref_point)
            if dist < min_dist:
                min_dist = dist
                closest_ref_pt = ref_point

        return min_dist, closest_ref_pt

    def progress_costs(self, path: Path):
        pose_stamped = path.poses[-1].pose.position
        traj_end_pt = np.array([pose_stamped.x, pose_stamped.y, pose_stamped.z])

        _, end_ref_pt = self.project_point_to_reference_trajectory(traj_end_pt)

        pose_stamped = path.poses[0].pose.position
        traj_start_pt = np.array([pose_stamped.x, pose_stamped.y, pose_stamped.z])
        _, start_ref_pt = self.project_point_to_reference_trajectory(traj_start_pt)

        dist = np.linalg.norm(start_ref_pt - end_ref_pt)

        # incentive is negative cost
        return -dist

    def bounds_costs(self, path: Path):
        total_deviation = 0.0
        valid_points = 0

        if not self.reference_path or not self.reference_path.poses:
            return float('inf')

        for pose_stamped in path.poses:
            p = pose_stamped.pose.position
            point = np.array([p.x, p.y, p.z])
            min_dist, _ = self.project_point_to_reference_trajectory(point)

            total_deviation +=  1 - np.exp(-(2/BOUNDS_SPREAD * min_dist) ** 2)
            valid_points += 1

        if valid_points == 0:
            return float('inf')
        
        return total_deviation


def main(args=None):
    rclpy.init(args=args)
    node = TrajectorySelecter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
