from setuptools import find_packages
from setuptools import setup

setup(
    name='local_planner_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('local_planner_msgs', 'local_planner_msgs.*')),
)
