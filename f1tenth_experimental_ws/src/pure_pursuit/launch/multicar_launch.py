from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pure_pursuit_dir = get_package_share_directory('pure_pursuit')
    group_launch_file = os.path.join(pure_pursuit_dir, 'launch', 'sim_pure_pursuit_launch.py')
    config_dir = os.path.join(pure_pursuit_dir, 'config')

    ego_config_path = os.path.join(config_dir, 'sim_config_ego.yaml')
    opp_config_path = os.path.join(config_dir, 'sim_config_opp.yaml')

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
