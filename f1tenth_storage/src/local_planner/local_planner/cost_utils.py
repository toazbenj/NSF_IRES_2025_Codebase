from local_planner.constants import *
from geometry_msgs.msg import Point
from nav_msgs.msg import Path
import numpy as np


def evaluate_path(path: Path, reference_path: Path):
    progress_cost = progress_costs(path, reference_path)
    bounds_cost = bounds_costs(path, reference_path)
    cost = RELATIVE_PROGRESS_WEIGHT_1 * progress_cost + BOUNDS_WEIGHT_1 * bounds_cost
    return cost

def project_point_to_reference_trajectory(point, reference_path):
    min_dist = float('inf')
    closest_ref_pt = None
    for ref_pose in reference_path.poses:
        rp = ref_pose.pose.position
        ref_point = np.array([rp.x, rp.y, rp.z])
        dist = np.linalg.norm(point - ref_point)
        if dist < min_dist:
            min_dist = dist
            closest_ref_pt = ref_point

    return min_dist, closest_ref_pt

def progress_costs(path: Path, reference_path: Path):
    pose_stamped = path.poses[-1].pose.position
    traj_end_pt = np.array([pose_stamped.x, pose_stamped.y, pose_stamped.z])

    _, end_ref_pt = project_point_to_reference_trajectory(traj_end_pt, reference_path)

    pose_stamped = path.poses[0].pose.position
    traj_start_pt = np.array([pose_stamped.x, pose_stamped.y, pose_stamped.z])
    _, start_ref_pt = project_point_to_reference_trajectory(traj_start_pt, reference_path)

    dist = np.linalg.norm(start_ref_pt - end_ref_pt)

    # incentive is negative cost
    return -dist

def bounds_costs(path: Path, reference_path: Path):
    total_deviation = 0.0
    max_dist = 0.0

    for pose_stamped in path.poses:
        p = pose_stamped.pose.position
        point = np.array([p.x, p.y, p.z])
        dist, _ = project_point_to_reference_trajectory(point, reference_path)

        if dist > max_dist:
            max_dist = dist

    total_deviation +=  1 - np.exp(-(2/BOUNDS_SPREAD * max_dist) ** 2)
    
    return total_deviation