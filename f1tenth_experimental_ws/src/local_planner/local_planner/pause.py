import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool

class PauseNode(Node):
    def __init__(self):
        super().__init__('pause_node')
        self.publisher_ = self.create_publisher(Bool, '/pause_state', 10)
        self.timer = self.create_timer(0.1, self.publish_state)
        self.paused = False

        self.get_logger().info("Press 'p' to toggle pause/resume.")
        import threading
        threading.Thread(target=self.listen_input, daemon=True).start()

    def listen_input(self):
        while True:
            key = input()
            if key.strip() == 'p':
                self.paused = not self.paused
                print(f"{'Paused' if self.paused else 'Resumed'}")

    def publish_state(self):
        msg = Bool()
        msg.data = self.paused
        self.publisher_.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = PauseNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
