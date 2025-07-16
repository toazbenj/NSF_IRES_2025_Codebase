from setuptools import find_packages, setup
from glob import glob
import os

package_name = 'local_planner'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='bentoaz',
    maintainer_email='toazbenj@msu.edu',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'traj_server = local_planner.traj_server:main',
            'traj_selecter = local_planner.traj_selecter:main',
            'debug_node = local_planner.debug_node:main',
            'visualizer = local_planner.visualizer:main',
            'pause = local_planner.pause:main',
        ],
    },
)
