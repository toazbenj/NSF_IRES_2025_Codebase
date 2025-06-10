# import rclpy
# from rclpy.node import Node
# from nav_msgs.msg import Path
# from traj_planning_msg.msg import PathList
# from geometry_msgs.msg import PoseStamped
# from std_msgs.msg import Header
# import carla

# class TrajectoryVisualizer(Node):
#     def __init__(self):
#         super().__init__('trajectory_visualizer')

#         self.subscription = self.create_subscription(
#             PathList,
#             '/carla/hero/traj_list',
#             self.path_list_callback,
#             10
#         )

#         self.path_publishers = []

#     def path_list_callback(self, msg: PathList):
#         while len(self.path_publishers) < len(msg.paths):
#             topic_name = f'/carla/hero/trajectory_{len(self.path_publishers)}'
#             pub = self.create_publisher(Path, topic_name, 10)
#             self.path_publishers.append(pub)
#             self.get_logger().info(f'Created publisher for {topic_name}')

#         for i, path in enumerate(msg.paths):
#             if i < len(self.path_publishers):
#                 self.path_publishers[i].publish(path)

# def main(args=None):
#     rclpy.init(args=args)
#     node = TrajectoryVisualizer()
#     rclpy.spin(node)
#     node.destroy_node()
#     rclpy.shutdown()


# if __name__ == '__main__':
#     main()

import rclpy
from rclpy.node import Node
from traj_planning_msg.msg import PathList
from geometry_msgs.msg import Point
from visualization_msgs.msg import Marker, MarkerArray
from std_msgs.msg import ColorRGBA

class TrajectoryVisualizer(Node):
    def __init__(self):
        super().__init__('trajectory_visualizer')

        self.subscription = self.create_subscription(
            PathList,
            '/carla/hero/traj_list',
            self.path_list_callback,
            10
        )

        self.marker_pub = self.create_publisher(MarkerArray, '/carla/hero/trajectories', 10)

    def path_list_callback(self, msg: PathList):
        marker_array = MarkerArray()

        for idx, path in enumerate(msg.paths):
            marker = Marker()
            marker.header = path.header
            marker.ns = 'trajectories'
            marker.id = idx
            marker.type = Marker.LINE_STRIP
            marker.action = Marker.ADD
            marker.scale.x = 0.1  # Line width
            marker.color = ColorRGBA(r=1.0, g=0.0, b=0.0, a=1.0)  # Red, opaque
            marker.points = [pose.pose.position for pose in path.poses]

            marker_array.markers.append(marker)

        self.marker_pub.publish(marker_array)

def main(args=None):
    rclpy.init(args=args)
    node = TrajectoryVisualizer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
