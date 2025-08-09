from local_planner.constants import *
from geometry_msgs.msg import Point
from nav_msgs.msg import Path
import numpy as np

from scipy.spatial import cKDTree

def build_kdtree(reference_path):
    ref_points = np.array([[p.pose.position.x, p.pose.position.y, p.pose.position.z]
                           for p in reference_path.poses])
    return cKDTree(ref_points), ref_points

def nearest_point(point, kdtree, ref_points):
    point_arr = np.array([point.x, point.y, point.z])
    dist, idx = kdtree.query(point_arr)
    return dist, ref_points[idx], idx

def evaluate_static_path(path: Path, kdtree, ref_points, bounds_spread):
    progress_cost = calc_progress_costs(path, kdtree, ref_points)
    bounds_cost = calc_bounds_costs(path, kdtree, ref_points, bounds_spread)
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

def calc_progress_costs(path: Path, kdtree, ref_points):
    end_pose = path.poses[-1].pose.position
    _, end_ref_pt, _ = nearest_point(end_pose, kdtree, ref_points)

    start_pose = path.poses[0].pose.position
    _, start_ref_pt, _ = nearest_point(start_pose, kdtree, ref_points)

    dist = np.linalg.norm(start_ref_pt - end_ref_pt)

    # incentive is negative cost   
    return float(-dist)

def calc_bounds_costs(path: Path, kdtree, ref_points, bounds_spread):
    max_dist = 0.0

    for pose_stamped in path.poses:
        p = pose_stamped.pose.position
        dist, _, _ = nearest_point(p, kdtree, ref_points)
        if dist > max_dist:
            max_dist = dist

    deviation = 1 - np.exp(-(2 / bounds_spread * max_dist) ** 2)
    return float(deviation)

def calc_proximity_costs(path: Path, opponent_path: Path, proximity_spread):
    kdtree, ref_points = build_kdtree(opponent_path)
    min_dist = 100000.0

    for pose_stamped in path.poses:
        p = pose_stamped.pose.position
        dist, _, _ = nearest_point(p, kdtree, ref_points)

        if dist < min_dist:
            min_dist = dist

    cost =  np.exp(-(2 * 1 / proximity_spread * min_dist))
    return float(cost)
