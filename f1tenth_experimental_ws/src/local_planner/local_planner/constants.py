from math import radians
import numpy as np

# Most of these arent used yet

ATTACKER_SPEED = 22.5
DEFENDER_SPEED = 15

# Bicycle
# Time step
DT = 0.25
# Control limits, amount of control effort per choice
STEERING_INCREMENT = radians(35)
ACCELERATION_INCREMENT = 0.25

VELOCITY_LIMIT = 1.0 #m/s
ACTION_INTERVAL = 0.25 # seconds
RECEDING_HORIZON = 1.5 # seconds

MPC_HORIZON = 1
PROGRESS_RESET_RATIO = 0.75

# Control inputs (acceleration, steering)
# ACTION_LST = [(-1, -1), (-1, 0), (-1, 1), 
#               (0, -1), (0, 0), (0, 1), 
#               (1, -1), (1, 0), (1, 1)]

# ACTION_LST = [(-1, -1), (-1, 0), (-1, 1), 
#               (1, -1), (1, 0), (1, 1)]

# good for scalar cost in hallway and e7floor5 square
ACTION_LST = [(-1, -1), (-1, 0), (-1, 1), 
              (0, -1), (0, 0), (0, 1), 
              (1, -1), (1, 0), (1, 1),
              (1, -0.5), (1, 0.5)]

# size for calculations, radial (width) and frontal (length) axes
LR = 1
LF = 1
# how close bike center points are in pixels to count as collision
COLLISION_RADIUS = 5

# Trajectory
# relative cost weights
prox_weight = 1
bounds_weight = 100
progress_weight = 1

PROXIMITY_SPREAD = 0.25
BOUNDS_SPREAD = 5

PROXIMITY_WEIGHT_1 = prox_weight
BOUNDS_WEIGHT_1 = bounds_weight
RELATIVE_PROGRESS_WEIGHT_1 = progress_weight

PROXIMITY_WEIGHT_2 = prox_weight
BOUNDS_WEIGHT_2 = bounds_weight
RELATIVE_PROGRESS_WEIGHT_2 = progress_weight
