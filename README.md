# National Science Foundation International Research Experiences for Students - 2025 Codebase

![image](ROSDemoPolished.gif)

## Overview

This repository contains the custom ROS architecture for behavioral planning of autonomous vehicles in competitive scenarios. It builds on the efforts of several other F1 10th car contributors, especially the [University of Waterloo](https://github.com/CL2-UWaterloo/f1tenth_ws). Notable upgrades include game theoretic reasoning that takes the most likely actions of the opponent car into account when executing passes in a race.  

## Setup

The operations are identical to the steps described in the original University of Waterloo repo, but with some modified settings. The useful scripts are all in the f1tenth_experimental_ws folder. The controls folder is mostly for high level control experiments using Carla. The major differences between this repo and the original are settings within the pure pursuit package, including modified trajectory tracking and new lidar scan maps and waypoints. 

The physical branch holds code specifically modified to operate without the simulation interface on the actual F1 10th car. It has different topic names that are linked specifically to the hardware nodes on the car. The simulation repo is only for running with the f1tenth gym environment.

Modified Source:
```bash
git clone https://github.com/toazbenj/NSF_IRES_2025_Codebase.git
```

In addition, I modified the gym_bridge.rviz file in the f1tenth_gym_ros repo to load more visuals related to the decision making of two vehicles at once.

Modified Simulation:
```bash
git clone https://github.com/toazbenj/f1tenth_sim_ws.git
```

## ROS 2 F1 10th Simulation

### 2 Cars

Terminal 1: Simulation Environment
```bash
cd f1tenth_sim_ws
colcon build
source install/setup.bash
ros2 launch f1tenth_gym_ros gym_bridge_launch.py
```

Terminal 2: High Level Control (New)
```bash
cd NSF_IRES_2025_Codebase/f1tenth_experimental_ws/
colon build
source install/setup.bash
ros2 launch local_planner multicar_launch.py
```

Terminal 3: Low Level Control
```bash
cd NSF_IRES_2025_Codebase/f1tenth_experimental_ws/
colcon build
source install/setup.bash
ros2 launch pure_pursuit multicar_launch.py 
```

Note that at times you may have to stop the local planner node in terminal two and rerun it. This is when the threading of the nodes causes one of them to miss a topic and error out, preventing it from meshing with the low level control nodes. Don't panic, just stop the node and rerun. I estimate this happens about 1/3 of the time. In order to fix it, you will have to change the composition of how different nodes subscribe to each other, or the order in which they run.

### 1 Car
Terminal 1: Simulation Environment
```bash
cd f1tenth_sim_ws
source install/setup.bash
ros2 launch f1tenth_gym_ros gym_bridge_launch.py
```

Terminal 2: High Level Control (New)
```bash
cd NSF_IRES_2025_Codebase/f1tenth_experimental_ws/
source install/setup.bash
ros2 launch local_planner local_planner_launch.py
```

Terminal 3: Low Level Control
```bash
cd NSF_IRES_2025_Codebase/f1tenth_experimental_ws/
source install/setup.bash
ros2 launch pure_pursuit sim_pure_pursuit_launch.py 
