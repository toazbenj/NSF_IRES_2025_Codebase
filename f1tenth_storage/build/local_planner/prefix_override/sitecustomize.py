import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/bentoaz/f1tenth_experimental_ws/install/local_planner'
