import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import splprep, splev
import pandas as pd

# Load waypoints from CSV
filename = 'test_waypoints.csv'
df = pd.read_csv(filename)

x = df['x'].values
y = df['y'].values

# Fit a B-spline to the waypoints
tck, u = splprep([x, y], s=2.0)  # Adjust s for more/less smoothing

# Evaluate the B-spline
unew = np.linspace(0, 1.0, num=100)
out = splev(unew, tck)

# Plot the original and smoothed path
plt.figure(figsize=(8, 5))
plt.plot(x, y, 'o-', label='Original Path')
plt.plot(out[0], out[1], 'r-', label='Smoothed Path')
plt.legend()
plt.title("Path Smoothing from CSV Waypoints")
plt.xlabel("X")
plt.ylabel("Y")
plt.grid(True)
plt.show()
