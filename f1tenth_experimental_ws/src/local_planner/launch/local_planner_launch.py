from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    ld = LaunchDescription()
    config = os.path.join(
        get_package_share_directory('local_planner')
    )

    visualizer = Node(
        package='local_planner',
        executable='visualizer',
        name='visualizer',
        parameters=[]
    )

    traj_server = Node(
        package='local_planner',
        executable='traj_server',
        name='traj_server',
        parameters=[]
    )

    traj_selecter = Node(
        package='local_planner',
        executable='traj_selecter',
        name='traj_selecter',
        parameters=[]
    )

    pause = Node(
        package='local_planner',
        executable='pause',
        name='pause',
        parameters=[]
    )

    # finalize
    ld.add_action(visualizer)
    ld.add_action(traj_server)
    ld.add_action(traj_selecter)
    # ld.add_action(pause)

    return ld
