import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Header
import math
from tf_transformations import euler_from_quaternion
from nav_msgs.msg import Path
from geometry_msgs.msg import Pose, PoseStamped
from traj_planning_msg.msg import PathList


class TrajectorySampler(Node):
   def __init__(self):
       super().__init__('trajectory_sampler')
       self.subscription = self.create_subscription(
           Odometry,
           '/carla/hero/odometry',
           self.odom_callback,
           10
       )
       self.publisher = self.create_publisher(PathList, '/carla/hero/traj_list', 10)
       self.interval = 2.0  # meters between waypoints
       self.num_points = 10


   def odom_callback(self, msg: Odometry):
       pose = msg.pose.pose
       x = pose.position.x
       y = pose.position.y


       # Extract yaw from quaternion
       orientation_q = pose.orientation
       orientation_list = [
           orientation_q.x,
           orientation_q.y,
           orientation_q.z,
           orientation_q.w
       ]
       _, _, yaw = euler_from_quaternion(orientation_list)




       yaw_offsets = [-0.1, 0.0, 0.1]
       speed_set = [1.0]
       traj_list = []


       # Generate future waypoints
       for offset in yaw_offsets:
           for speed in speed_set:
               adjusted_yaw = yaw + offset
               spacing = speed * 0.2  # time step of 0.2s between points (tunable)


               header = Header()
               header.stamp = self.get_clock().now().to_msg()
               header.frame_id = "map"


               path = Path()
               path.header = header


               for i in range(self.num_points):
                   dx = i * spacing * math.cos(adjusted_yaw)
                   dy = i * spacing * math.sin(adjusted_yaw)
                   px = x + dx
                   py = y + dy


                   pose_stamped = PoseStamped()
                   pose_stamped.header = header
                   pose_stamped.pose.position.x = px
                   pose_stamped.pose.position.y = py
                   pose_stamped.pose.position.z = 0.0
                   pose_stamped.pose.orientation = orientation_q  + offset/len(self.num_points)

                   path.poses.append(pose_stamped)


           traj_list.append(path)


       path_list = PathList()
       path_list.path = traj_list
       self.publisher.publish(path_list)
       print(f"Published {len(yaw_offsets)*len(speed_set)} trajectories")


def main(args=None):
   print("Trajectory Server")
   rclpy.init(args=args)
   node = TrajectorySampler()
   rclpy.spin(node)
   node.destroy_node()
   rclpy.shutdown()


if __name__ == '__main__':
   main()