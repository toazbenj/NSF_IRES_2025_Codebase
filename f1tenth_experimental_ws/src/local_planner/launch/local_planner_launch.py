from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument


def generate_launch_description():
    ld = LaunchDescription()

    ld.add_action(DeclareLaunchArgument('namespace', default_value='/ego_racecar'))
    ld.add_action(DeclareLaunchArgument('config', 
                                        default_value='/home/bentoaz/NSF_IRES_2025_Codebase/f1tenth_experimental_ws/src/local_planner/config/ego_config.yaml'))

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

    # ld = LaunchDescription()

    ld.add_action(visualizer)
    ld.add_action(traj_server)
    ld.add_action(traj_selecter)

    return ld