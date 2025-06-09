import rclpy
from rclpy.node import Node
from nav_msgs.msg import Path
from traj_planning_msg.msg import PathList
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Header
import carla

class TrajectoryVisualizer(Node):
    def __init__(self):
        super().__init__('trajectory_visualizer')

        self.subscription = self.create_subscription(
            PathList,
            '/carla/hero/traj_list',
            self.path_list_callback,
            10
        )

        self.path_publishers = []
        self.map_publisher = self.create_publisher(Path, '/carla/road_centerline', 1)

        # Initialize CARLA client and map
        self.client = carla.Client('localhost', 2000)
        self.client.set_timeout(2.0)
        self.world = self.client.get_world()
        self.carla_map = self.world.get_map()

        self.publish_map_centerline()

    def path_list_callback(self, msg: PathList):
        while len(self.path_publishers) < len(msg.paths):
            topic_name = f'/carla/hero/trajectory_{len(self.path_publishers)}'
            pub = self.create_publisher(Path, topic_name, 10)
            self.path_publishers.append(pub)
            self.get_logger().info(f'Created publisher for {topic_name}')

        for i, path in enumerate(msg.paths):
            if i < len(self.path_publishers):
                self.path_publishers[i].publish(path)

    def publish_map_centerline(self):
        header = Header()
        header.stamp = self.get_clock().now().to_msg()
        header.frame_id = "map"

        path = Path()
        path.header = header

        topology = self.carla_map.get_topology()

        for start_wp, end_wp in topology:
            wps = [start_wp]
            current = start_wp

            while current.transform.location.distance(end_wp.transform.location) > 1.0:
                next_wps = current.next(1.0)
                if not next_wps:
                    break
                current = next_wps[0]
                wps.append(current)

            for wp in wps:
                loc = wp.transform.location
                pose_stamped = PoseStamped()
                pose_stamped.header = header
                pose_stamped.pose.position.x = loc.x
                pose_stamped.pose.position.y = loc.y
                pose_stamped.pose.position.z = loc.z
                pose_stamped.pose.orientation.w = 1.0  # identity quaternion
                path.poses.append(pose_stamped)

        self.map_publisher.publish(path)
        self.get_logger().info(f"Published CARLA centerline with {len(path.poses)} points.")



def main(args=None):
    rclpy.init(args=args)
    node = TrajectoryVisualizer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
