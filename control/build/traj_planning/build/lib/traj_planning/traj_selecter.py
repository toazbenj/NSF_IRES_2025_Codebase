import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from std_msgs.msg import Header
import math
from tf_transformations import euler_from_quaternion
from nav_msgs.msg import Path
from traj_planning_msg.msg import PathList
from scipy.spatial.transform import Rotation as R
from std_msgs.msg import Float64
from rclpy.qos import QoSProfile, QoSDurabilityPolicy

class TrajectorySelecter(Node):
    def __init__(self):
        super().__init__('trajectory_selecter')
        
        self.subscription = self.create_subscription(PathList, 
                                                     '/carla/hero/traj_list', 
                                                     self.path_callback,
                                                     10)
        
        # self.path_publisher = self.create_publisher(Path, '/carla/hero/waypoints', 10)
        # self.speed_publisher = self.create_publisher(Float64,'/carla/hero/speed_command', 10)

        qos = QoSProfile(depth=10)
        qos.durability = QoSDurabilityPolicy.TRANSIENT_LOCAL

        self.path_publisher = self.create_publisher(Path, '/carla/hero/waypoints', qos)
        self.speed_publisher = self.create_publisher(Float64, '/carla/hero/speed_command', qos)

        self.interval = 2.0  # meters between waypoints
        self.num_points = 10


    def path_callback(self, msg: PathList):
        
        path_list = msg.paths

        # policy selection, naive for now
        index = 1
        selected_traj = path_list[index]
        selected_traj.header.stamp = self.get_clock().now().to_msg()
        self.path_publisher.publish(selected_traj)

        speed = Float64()
        speed.data = 10.0
        self.speed_publisher.publish(speed)

        print(f"Published selected trajectory {index} at speed {speed}")


def main(args=None):
    print("Trajectory Selecter")
    rclpy.init(args=args)
    node = TrajectorySelecter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()