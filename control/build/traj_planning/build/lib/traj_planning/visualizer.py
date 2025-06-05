import rclpy
from rclpy.node import Node
from nav_msgs.msg import Path
from traj_planning_msg.msg import PathList
from std_msgs.msg import Header


class Visualizer(Node):
    def __init__(self):
        super().__init__('trajectory_visualizer')

        self.subscription = self.create_subscription(
            PathList,
            '/carla/hero/traj_list',
            self.path_list_callback,
            10
        )

        # dynamically create publishers for each trajectory path
        self.path_publishers = []

    def path_list_callback(self, msg: PathList):
        while len(self.path_publishers) < len(msg.paths):
            topic_name = f'/carla/hero/trajectory_{len(self.path_publishers)}'
            pub = self.create_publisher(Path, topic_name, 10)
            self.path_publishers.append(pub)
            self.get_logger().info(f'Created publisher for {topic_name}')

        for i, path in enumerate(msg.paths):
            if i < len(self.path_publishers):
                self.path_publishers[i].publish(path)


def main(args=None):
    rclpy.init(args=args)
    node = Visualizer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
