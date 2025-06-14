from math import radians
import numpy as np

# Most of these arent used yet

# Main
IS_COST_DATA_CREATION_MODE = True

# Number of races to run
NUM_RACES = 100
RACE_DURATION = 1500  # Number of frames per race, base 1500
# Seed setting
SEED = 41
IS_RANDOM_START=True
FRAME_RATE = 60

# Opponent Cost Weights
NUM_THETA_INTERVALS = 10
PROGRESS_RANGE = np.linspace(1, 11, NUM_THETA_INTERVALS)
BOUNDS_RANGE = np.linspace(1, 11, NUM_THETA_INTERVALS)
COLLISION_RANGE = np.linspace(1, 11, NUM_THETA_INTERVALS)

# Course
# Data output path
RACE_DATA = "../data/stats_test.csv"
COST_DATA = "../data/gpr_data.csv"
ATTACKER_SPEED = 22.5
DEFENDER_SPEED = 15

# Whether costs are created via optimization of multiple objectives (vector)
# or weighted sum (scalar)
P1_IS_VECTOR_COST = False
P2_IS_VECTOR_COST = False

# Bicycle
# Time step
DT = 0.05
# Control limits, amount of control effort per choice
STEERING_INCREMENT = radians(10)
ACCELERATION_INCREMENT = 3
STEER_LIMIT = radians(45)
# best combos: interval = 70, horizon = 1;
# interval = 50, horizon = 2; interval = 40, mpc = 3
ACTION_INTERVAL = 20
MPC_HORIZON = 2
# Control inputs (acceleration, steering)
ACTION_LST = [(-1, -1), (-1, 0), (-1, 1), 
              (0, -1), (0, 0), (0, 1), 
              (1, -1), (1, 0), (1, 1)]

# how large the bike appears on screen
BIKE_SIZE = 20
# size for calculations, radial (width) and frontal (length) axes
LR = 1
LF = 1
# how close bike center points are in pixels to count as collision
COLLISION_RADIUS = 45
VELOCITY_LIMIT = 40

# Trajectory
# relative cost weights
prox_weight = 0.5
bounds_weight = 1
progress_weight = 1

PROXIMITY_SPREAD = 40
BOUNDS_SPREAD = 180

PROXIMITY_WEIGHT1 = prox_weight
BOUNDS_WEIGHT_1 = bounds_weight
RELATIVE_PROGRESS_WEIGHT_1 = progress_weight

PROXIMITY_WEIGHT_2 = prox_weight
BOUNDS_WEIGHT_2 = bounds_weight
RELATIVE_PROGRESS_WEIGHT_2 = progress_weight
