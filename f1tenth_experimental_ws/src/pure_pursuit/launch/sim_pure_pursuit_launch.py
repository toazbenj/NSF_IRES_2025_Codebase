from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    ld = LaunchDescription()
    config = LaunchConfiguration('config')
    namespace = LaunchConfiguration('namespace')

    pure_pursuit = Node(
        package='pure_pursuit',
        executable='pure_pursuit',
        namespace=namespace,
        name='pure_pursuit',
        parameters=[config]
    )

    waypoint_visualizer_node = Node(
        package='pure_pursuit',
        executable='waypoint_visualizer',
        namespace=namespace,
        name='waypoint_visualizer_node',
        parameters=[config]
    )

    # finalize
    # ld.add_action(waypoint_visualizer_node)
    # ld.add_action(pure_pursuit)

    # return ld

    return LaunchDescription([
        DeclareLaunchArgument('namespace'),
        DeclareLaunchArgument('config'),
        pure_pursuit,
        waypoint_visualizer_node,
    ])