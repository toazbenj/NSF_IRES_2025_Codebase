# from launch import LaunchDescription
# from launch_ros.actions import Node
# from launch.substitutions import LaunchConfiguration
# from ament_index_python.packages import get_package_share_directory


# def generate_launch_description():
#     namespace = LaunchConfiguration('namespace')
#     config_file = LaunchConfiguration('config')

#     pure_pursuit = Node(
#         package='pure_pursuit',
#         executable='pure_pursuit',
#         namespace=namespace,
#         name='pure_pursuit',
#         parameters=[config_file]
#     )

#     waypoint_visualizer_node = Node(
#         package='pure_pursuit',
#         executable='waypoint_visualizer',
#         namespace=namespace,
#         name='waypoint_visualizer_node',
#         parameters=[config_file]
#     )

#     ld = LaunchDescription()
#     ld.add_action(pure_pursuit)
#     ld.add_action(waypoint_visualizer_node)
#     return ld


from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    # Declare launch arguments
    namespace_arg = DeclareLaunchArgument(
        'namespace',
        default_value='',
        description='Namespace for the node'
    )
    
    config_arg = DeclareLaunchArgument(
        'config',
        default_value='',
        description='Path to the config file'
    )
    
    # Get launch configurations
    namespace = LaunchConfiguration('namespace')
    config_file = LaunchConfiguration('config')
    
    # Create the pure pursuit node
    pure_pursuit_node = Node(
        package='pure_pursuit',
        executable='pure_pursuit',  # Make sure this matches your executable name
        namespace=namespace,
        parameters=[config_file],  # Load parameters from the config file
        output='screen',
        emulate_tty=True,
    )

    waypoint_visualizer_node = Node(
        package='pure_pursuit',
        executable='waypoint_visualizer',
        namespace=namespace,
        parameters=[config_file],  # Load parameters from the config file
        output='screen',
        emulate_tty=True,
    )

    
    return LaunchDescription([
        namespace_arg,
        config_arg,
        pure_pursuit_node,
        waypoint_visualizer_node,
    ])