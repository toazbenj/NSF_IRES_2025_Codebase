import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/bentoaz/NSF_IRES_2025_Codebase/control/install/traj_planning'
