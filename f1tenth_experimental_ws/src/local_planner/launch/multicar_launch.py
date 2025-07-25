from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    planner_dir = get_package_share_directory('local_planner')
    group_launch_file = os.path.join(planner_dir, 'launch', 'local_planner_launch.py')
    config_dir = os.path.join(planner_dir, 'config')

    ego_config_path = os.path.join(config_dir, 'ego_config.yaml')
    opp_config_path = os.path.join(config_dir, 'opp_config.yaml')

    ego_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(group_launch_file),
        launch_arguments={
            'namespace': '/ego_racecar',
            'config': ego_config_path
        }.items()
    )

    opp_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(group_launch_file),
        launch_arguments={
            'namespace': '/opp_racecar',
            'config': opp_config_path
        }.items()
    )

    return LaunchDescription([
        ego_launch,
        opp_launch
    ])
