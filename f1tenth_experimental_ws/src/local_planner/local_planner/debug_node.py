import rclpy
from rclpy.node import Node
import pdb

class DebugNode(Node):
    def __init__(self):
        super().__init__('debug')
        pdb.set_trace()
        self.get_logger().warn("print something")
        self.timer = self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        self.get_logger().warn("print something else")

def main(args=None):
    rclpy.init(args=args)
    node = DebugNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
