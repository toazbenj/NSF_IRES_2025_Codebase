#!/usr/bin/env python3
import os
from launch import LaunchDescription
from launch.actions import ExecuteProcess, IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
    # Paths
    carla_root = os.path.expanduser('~/CARLA_PROJECT/CARLA_0.9.15')
    ros_bridge_ws = os.path.expanduser('~/CARLA_PROJECT/ros2_bridge_ws/ros-bridge/install')
    carla_ros2_ws = os.path.expanduser('~/CARLA_PROJECT/carla_ros2_ws/install')
    control_ws = os.path.expanduser('~/CARLA_PROJECT/NSF_IRES_2025_Codebase/control/install')

    # Set environment variables
    set_carla_root = SetEnvironmentVariable('CARLA_ROOT', carla_root)
    set_pythonpath = SetEnvironmentVariable('PYTHONPATH', 
        os.path.join(carla_root,'PythonAPI','carla') + ':' + os.environ.get('PYTHONPATH',''))

    # 1. Start Carla simulator
    start_carla = ExecuteProcess(
        cmd=[os.path.join(carla_root, 'CarlaUE4.sh'),
             '-prefernvidia', '-quality-level=Low', '-RenderOffScreen'],
        cwd=carla_root,
        output='screen'
    )

    # 2. Launch ROS bridge example ego vehicle
    source_bridge = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(ros_bridge_ws, 'share', 'carla_ros_bridge', 'launch', 
                         'carla_ros_bridge_with_example_ego_vehicle.launch.py')
        ),
        launch_arguments={}
    )

    # 3. Launch Carla waypoint publisher
    source_wayp = Node(
        package='carla_waypoint_publisher',
        executable='carla_waypoint_publisher',
        name='carla_waypoint_publisher',
        output='screen',
        env={
            'CARLA_ROOT': carla_root,
            'PYTHONPATH': os.path.join(carla_root,'PythonAPI','carla') + ':' + os.environ.get('PYTHONPATH','')
        }
    )

    # 4. Launch navigation HMI
    nav_hmi = Node(
        package='navigation',
        executable='navigation_hmi',
        name='navigation_hmi',
        output='screen',
        prefix=f"bash -lc \"source {ros_bridge_ws}/setup.bash && source {carla_ros2_ws}/setup.bash && exec\""
    )

    # 5–9: Trajectory planners & visualizer
    traj_local = Node(
        package='traj_planning',
        executable='local_planner',
        name='local_planner',
        output='screen',
        prefix=f"bash -lc \"source {ros_bridge_ws}/setup.bash && source {control_ws}/setup.bash && exec\""
    )
    traj_server = Node(
        package='traj_planning',
        executable='traj_server',
        name='traj_server',
        output='screen',
        prefix=f"bash -lc \"source {ros_bridge_ws}/setup.bash && source {control_ws}/setup.bash && exec\""
    )
    traj_selector = Node(
        package='traj_planning',
        executable='traj_selecter',
        name='traj_selecter',
        output='screen',
        prefix=f"bash -lc \"source {ros_bridge_ws}/setup.bash && source {control_ws}/setup.bash && exec\""
    )
    traj_visualizer = Node(
        package='traj_planning',
        executable='visualizer',
        name='traj_visualizer',
        output='screen',
        prefix=f"bash -lc \"source {ros_bridge_ws}/setup.bash && source {control_ws}/setup.bash && exec\""
    )

    # 10. RViz2
    rviz = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen'
    )

    # 11. rqt_graph
    rqt_graph = ExecuteProcess(cmd=['rqt_graph'], output='screen')

    return LaunchDescription([
        set_carla_root,
        set_pythonpath,
        start_carla,
        source_bridge,
        source_wayp,
        nav_hmi,
        traj_local,
        traj_server,
        traj_selector,
        traj_visualizer,
        rviz,
        rqt_graph
    ])

