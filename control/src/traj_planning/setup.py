from setuptools import find_packages, setup

package_name = 'traj_planning'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', ['launch/carla_ros.launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='bentoaz',
    maintainer_email='bentoaz@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'traj_server = traj_planning.traj_server:main',
            'traj_selecter = traj_planning.traj_selecter:main',
            'visualizer = traj_planning.visualizer:main',
            'local_planner = traj_planning.local_planner:main',
        ],
    },
)
