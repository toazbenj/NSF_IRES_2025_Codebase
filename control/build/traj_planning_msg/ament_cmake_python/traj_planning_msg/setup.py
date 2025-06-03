from setuptools import find_packages
from setuptools import setup

setup(
    name='traj_planning_msg',
    version='0.0.0',
    packages=find_packages(
        include=('traj_planning_msg', 'traj_planning_msg.*')),
)
