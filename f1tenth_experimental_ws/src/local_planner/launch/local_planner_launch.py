from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument


def generate_launch_description():
    namespace = LaunchConfiguration('namespace')
    config_file = LaunchConfiguration('config')

    visualizer = Node(
        package='local_planner',
        executable='visualizer',
        namespace=namespace,
        name='visualizer',
        parameters=[config_file]
    )

    traj_server = Node(
        package='local_planner',
        executable='traj_server',
        namespace=namespace,
        name='traj_server',
        parameters=[config_file]
    )

    traj_selecter = Node(
        package='local_planner',
        executable='traj_selecter',
        namespace=namespace,
        name='traj_selecter',
        parameters=[config_file]
    )

    return LaunchDescription([
        DeclareLaunchArgument('namespace'),
        DeclareLaunchArgument('config'),
        visualizer,
        traj_server,
        traj_selecter
    ])
