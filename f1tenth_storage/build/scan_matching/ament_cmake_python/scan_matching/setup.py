from setuptools import find_packages
from setuptools import setup

setup(
    name='scan_matching',
    version='0.0.0',
    packages=find_packages(
        include=('scan_matching', 'scan_matching.*')),
)
