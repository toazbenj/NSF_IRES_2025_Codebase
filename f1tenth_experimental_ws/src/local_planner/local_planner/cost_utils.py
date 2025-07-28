from local_planner.constants import *
from geometry_msgs.msg import Point
from nav_msgs.msg import Path
import numpy as np


def evaluate_static_path(path: Path, reference_path, bounds_spread):
    progress_cost = calc_progress_costs(path, reference_path)
    bounds_cost = calc_bounds_costs(path, reference_path, bounds_spread)
    return progress_cost, bounds_cost

def project_point_to_reference_trajectory(point, reference_path):
    min_dist = float('inf')
    closest_ref_pt = None
    idx = 0
    for i, ref_pose in enumerate(reference_path.poses):
        rp = ref_pose.pose.position
        ref_point = np.array([rp.x, rp.y, rp.z])
        # p = point.position
        point_arr = np.array([point.x, point.y, point.z])
        dist = np.linalg.norm(point_arr - ref_point)

        if dist < min_dist:
            min_dist = dist
            closest_ref_pt = ref_point
            idx = i

    return min_dist, closest_ref_pt, idx

def calc_progress_costs(path: Path, reference_path: Path):
    end_pose = path.poses[-1].pose.position
    _, end_ref_pt, _ = project_point_to_reference_trajectory(end_pose, reference_path)

    start_pose = path.poses[0].pose.position
    _, start_ref_pt, _ = project_point_to_reference_trajectory(start_pose, reference_path)

    dist = np.linalg.norm(start_ref_pt - end_ref_pt)

    # incentive is negative cost   
    # suspicious float conversion 
    return float(-dist)

def calc_bounds_costs(path: Path, reference_path: Path, bounds_spread):
    total_deviation = 0.0
    max_dist = 0.0

    for pose_stamped in path.poses:
        p = pose_stamped.pose.position
        # point = np.array([p.x, p.y, p.z])
        dist, _, _ = project_point_to_reference_trajectory(p, reference_path)

        if dist > max_dist:
            max_dist = dist

    total_deviation +=  1 - np.exp(-(2/bounds_spread * max_dist) ** 2)
    
    return float(total_deviation)

def calc_proximity_costs(path: Path, opponent_path: Path):
    min_dist = 100000.0

    for pose_stamped in path.poses:
        p = pose_stamped.pose.position
        # point = np.array([p.x, p.y, p.z])
        dist, _, _ = project_point_to_reference_trajectory(p, opponent_path)

        if dist < min_dist:
            min_dist = dist

    cost =  np.exp(-(2 * 1 / PROXIMITY_SPREAD * min_dist))
    return float(cost)
