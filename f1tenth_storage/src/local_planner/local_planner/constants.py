from math import radians
import numpy as np

# Most of these arent used yet

ATTACKER_SPEED = 22.5
DEFENDER_SPEED = 15

# Bicycle
# Time step
DT = 0.05
# Control limits, amount of control effort per choice
STEERING_INCREMENT = radians(10)
ACCELERATION_INCREMENT = 0.25
STEER_LIMIT = radians(45)
# best combos: interval = 70, horizon = 1;
# interval = 50, horizon = 2; interval = 40, mpc = 3
ACTION_INTERVAL = 25
MPC_HORIZON = 1
# Control inputs (acceleration, steering)
ACTION_LST = [(-1, -1), (-1, 0), (-1, 1), 
              (0, -1), (0, 0), (0, 1), 
              (1, -1), (1, 0), (1, 1)]

# size for calculations, radial (width) and frontal (length) axes
LR = 1
LF = 1
# how close bike center points are in pixels to count as collision
COLLISION_RADIUS = 45

# implemented as percentage of full speed
VELOCITY_LIMIT = 1.0

# Trajectory
# relative cost weights
prox_weight = 1
bounds_weight = 1
progress_weight = 1

PROXIMITY_SPREAD = 5
BOUNDS_SPREAD = 2

PROXIMITY_WEIGHT_1 = prox_weight
BOUNDS_WEIGHT_1 = bounds_weight
RELATIVE_PROGRESS_WEIGHT_1 = progress_weight

PROXIMITY_WEIGHT_2 = prox_weight
BOUNDS_WEIGHT_2 = bounds_weight
RELATIVE_PROGRESS_WEIGHT_2 = progress_weight
