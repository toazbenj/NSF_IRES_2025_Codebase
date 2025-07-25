from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # Get package directory
    pkg_dir = get_package_share_directory('pure_pursuit')
    
    # Define paths
    group_launch_file = os.path.join(pkg_dir, 'launch', 'multi_pure_pursuit_launch.py')
    config_dir = os.path.join(pkg_dir, 'config')
    ego_config_path = os.path.join(config_dir, 'sim_config_ego.yaml')
    opp_config_path = os.path.join(config_dir, 'sim_config_opp.yaml')
    
    # Check if config files exist
    if not os.path.exists(ego_config_path):
        print(f"Warning: Config file not found: {ego_config_path}")
    if not os.path.exists(opp_config_path):
        print(f"Warning: Config file not found: {opp_config_path}")
    
    # Launch ego racecar
    ego_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(group_launch_file),
        launch_arguments={
            'namespace': 'ego_racecar',  # Remove leading slash
            'config': ego_config_path
        }.items()
    )
    
    # Launch opponent racecar
    opp_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(group_launch_file),
        launch_arguments={
            'namespace': 'opp_racecar',  # Remove leading slash
            'config': opp_config_path
        }.items()
    )
    
    return LaunchDescription([
        ego_launch,
        opp_launch
    ])