import rclpy
from rclpy.node import Node
from nav_msgs.msg import Path
from visualization_msgs.msg import MarkerArray
from local_planner_msgs.msg import TrajectoryList
from geometry_msgs.msg import Point
from std_msgs.msg import Float64, Header
from rclpy.qos import QoSProfile, QoSDurabilityPolicy
import numpy as np
from local_planner.cost_utils import evaluate_static_path, calc_proximity_costs
from local_planner.cost_utils import build_kdtree, nearest_point, project_point_to_reference_trajectory

from std_msgs.msg import Bool
from local_planner.cost_adjust_cvx import find_adjusted_costs
from std_msgs.msg import Float32MultiArray

import cProfile
import logging
import os
import atexit

PROFILE_PATH = os.path.expanduser('~/traj_selecter_test.prof')
logging.basicConfig(level=logging.INFO)

class TrajectorySelecter(Node):
    def __init__(self):
        super().__init__('trajectory_selecter')

        # Declare and read parameters
        self.declare_parameter('NAMESPACE', '/ego_racecar')
        self.declare_parameter('OPPONENT_NAMESPACE', '/opp_racecar')

        self.declare_parameter('PROGRESS_WEIGHT', 1.0)
        self.declare_parameter('BOUNDS_WEIGHT', 100.0)
        self.declare_parameter('BOUNDS_SPREAD', 5.0)
        self.declare_parameter('PROXIMITY_WEIGHT', 1.0)
        self.declare_parameter('PROXIMITY_SPREAD', 0.25)

        self.declare_parameter('IS_VECTOR_COST', False)

        self.declare_parameter('OPP_PROGRESS_WEIGHT', 1.0)
        self.declare_parameter('OPP_BOUNDS_WEIGHT', 100.0)
        self.declare_parameter('OPP_BOUNDS_SPREAD', 5.0)
        self.declare_parameter('OPP_PROXIMITY_WEIGHT', 1.0)
        self.declare_parameter('OPP_PROXIMITY_SPREAD', 0.25)

        self.namespace = self.get_parameter('NAMESPACE').get_parameter_value().string_value
        self.opponent_namespace = self.get_parameter('OPPONENT_NAMESPACE').get_parameter_value().string_value

        self.bounds_weight = self.get_parameter('BOUNDS_WEIGHT').value
        self.progress_weight = self.get_parameter('PROGRESS_WEIGHT').value
        self.bounds_spread = self.get_parameter('BOUNDS_SPREAD').value
        self.proximity_weight = self.get_parameter('PROXIMITY_WEIGHT').value
        self.proximity_spread = self.get_parameter('PROXIMITY_SPREAD').value

        self.opp_bounds_weight = self.get_parameter('OPP_BOUNDS_WEIGHT').value
        self.opp_progress_weight = self.get_parameter('OPP_PROGRESS_WEIGHT').value
        self.opp_bounds_spread = self.get_parameter('OPP_BOUNDS_SPREAD').value
        self.opp_proximity_weight = self.get_parameter('OPP_PROXIMITY_WEIGHT').value
        self.opp_proximity_spread = self.get_parameter('OPP_PROXIMITY_SPREAD').value

        self.action_space_sub = self.create_subscription(
            TrajectoryList, f'{self.namespace}/traj_list', self.local_path_callback, 10)
        
        self.opponent_action_space_sub = self.create_subscription(
            TrajectoryList, f'{self.opponent_namespace}/traj_list', self.opponent_path_callback, 10)

        # self.global_path_sub = self.create_subscription(
        #     Path, self.namespace + '/waypoints', self.global_path_callback, 10)

        qos = QoSProfile(depth=10)
        qos.durability = QoSDurabilityPolicy.TRANSIENT_LOCAL
        self.global_path_sub = self.create_subscription(
              Path, self.namespace + '/waypoints', self.global_path_callback, qos)

        # self.opponent_cost_subscriptoin = self.create_subscription(
        #     Float32MultiArray, f'{self.opponent_namespace}/composite_cost_arr', self.opponent_cost_callback, 10)
        # self.cost_publisher = self.create_publisher(Float32MultiArray, f'{self.namespace}/composite_cost_arr', qos)

        qos = QoSProfile(depth=10)
        qos.durability = QoSDurabilityPolicy.TRANSIENT_LOCAL
        self.path_publisher = self.create_publisher(Path, f'{self.namespace}/selected_waypoints', qos)
        self.speed_publisher = self.create_publisher(Float64, f'{self.namespace}/speed_command', qos)

        self.opponent_path_list = None
        self.reference_path = None
        self.kdtree = None
        self.ref_points = None

        self.is_vector_cost = self.get_parameter('IS_VECTOR_COST').value

        self.get_logger().info("TrajectorySelecter initialized")

    def global_path_callback(self, msg: Path):
        # if msg != self.reference_path:
        #     self.reference_path = msg
        #     self.get_logger().info(f"New reference path received")
        
        self.reference_path = msg
        self.get_logger().info(f"New reference path received")
        self.kdtree, self.ref_points = build_kdtree(self.reference_path)

    def opponent_cost_callback(self, msg: Float32MultiArray):
        self.opponent_composite_cost_arr = np.array(msg.data, dtype=np.float32)
        self.select_trajectory_callback()

    def opponent_path_callback(self, msg: TrajectoryList):
        self.opponent_path_list = msg.paths

    def make_cost_matrices(self, path_list, opponent_path_list, bounds_spread, proximity_spread):
        progress_costs = np.zeros((len(path_list), len(path_list)), dtype=np.float32)
        bounds_costs = np.zeros((len(path_list), len(path_list)), dtype=np.float32)
        proximity_costs = np.zeros((len(path_list), len(path_list)), dtype=np.float32)

        for idx1, path in enumerate(path_list):
            single_prog_cost, single_bound_cost = evaluate_static_path(
                path.path, self.kdtree, self.ref_points, self.bounds_spread)

            prog_row = np.full(len(path_list), single_prog_cost, dtype=np.float32)
            bounds_row = np.full(len(path_list), single_bound_cost, dtype=np.float32)

            progress_costs[idx1] = prog_row
            bounds_costs[idx1] = bounds_row

            if opponent_path_list is not None:

                for idx2, opponent_path in enumerate(opponent_path_list):
                    proximity_costs[idx1][idx2] = calc_proximity_costs(path.path, opponent_path.path, proximity_spread)
            else:
                self.get_logger().warn("No opponent trajectories.")

        return progress_costs, bounds_costs, proximity_costs

    def local_path_callback(self, msg: TrajectoryList):
        self.path_list = msg.paths

        if not self.reference_path:
            self.get_logger().warn("No road network received yet.")
            return
    
        self.progress_costs, self.bounds_costs, self.proximity_costs = self.make_cost_matrices(self.path_list, 
                                                                                               self.opponent_path_list,
                                                                                               self.bounds_spread, 
                                                                                               self.proximity_spread)
        if self.is_vector_cost:
            opp_progress_costs, opp_bounds_costs, opp_proximity_costs = self.make_cost_matrices(self.opponent_path_list,
                                                                                                self.path_list, 
                                                                                                self.opp_bounds_spread, 
                                                                                                self.opp_proximity_spread)
            opponent_composite_cost_arr = self.opp_progress_weight * opp_progress_costs +\
                                          self.opp_bounds_weight * opp_bounds_costs +\
                                          self.opp_proximity_weight * opp_proximity_costs

        # publish cost matrix to the other car
        # msg = Float32MultiArray()
        # arr = self.progress_weight * self.progress_costs + self.bounds_weight * self.bounds_costs + self.proximity_weight * self.proximity_costs
        # arr = np.array(arr, dtype=np.float32)  # Ensure float32 type
        # # msg.data = arr.tolist()
        # # msg.data = [float(x) for x in arr]  # Ensure all elements are Python floats
        # msg.data = arr.flatten().astype(np.float32).tolist()  # Flatten and cast
        # self.cost_publisher.publish(msg)

        if self.is_vector_cost:
            E = find_adjusted_costs(self.progress_costs, self.bounds_costs, self.proximity_costs, opponent_composite_cost_arr)
            
            if E is None:
                # print("no minima")
                composite_cost_arr = self.progress_weight * self.progress_costs + self.bounds_weight * self.bounds_costs + self.proximity_weight * self.proximity_costs
            else:
                print("adjustment success")
                composite_cost_arr = self.progress_costs + E
        else:
            composite_cost_arr = self.progress_weight * self.progress_costs + self.bounds_weight * self.bounds_costs + self.proximity_weight * self.proximity_costs


        # for debugging, force weighted sum, vector cost decisions currently just wrong
        # composite_cost_arr = self.progress_weight * self.progress_costs + self.bounds_weight * self.bounds_costs + self.proximity_weight * self.proximity_costs


        self.get_logger().info(f"Costs: {composite_cost_arr}")

        self.action_index = np.argmin(np.max(composite_cost_arr, axis=1))

        # self.action_index = 4
        selected_traj = self.path_list[self.action_index]
        selected_traj.header.stamp = self.get_clock().now().to_msg()
        selected_traj.path.header.frame_id = "map" 

        self.path_publisher.publish(selected_traj.path)
        self.speed_publisher.publish(selected_traj.speed)

        self.get_logger().info(f"Published selected trajectory {self.action_index} at speed {selected_traj.speed.data} m/s")
    

profiler = cProfile.Profile()
profiler.enable()

def main(args=None):
    rclpy.init(args=args)
    node = TrajectorySelecter()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().warn("KeyboardInterrupt received, shutting down.")
    finally:
        node.destroy_node()
        rclpy.shutdown()

def save_profile():
    profiler.disable()
    profiler.dump_stats(PROFILE_PATH)
    if os.path.exists(PROFILE_PATH):
        logging.info(f"Profile successfully saved to {PROFILE_PATH}")
    else:
        logging.error(f"Profile not saved. Expected at {PROFILE_PATH}")

atexit.register(save_profile)

if __name__ == '__main__':
    main()