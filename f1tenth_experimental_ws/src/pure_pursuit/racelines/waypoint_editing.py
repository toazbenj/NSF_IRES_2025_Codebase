import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.image import imread
from scipy.interpolate import splprep, splev
import yaml
import os

class SmoothedPathEditorWithImage:
    def __init__(self, waypoint_file, map_yaml_file, smooth_factor=2.0, num_points=100):
        self.df = pd.read_csv(waypoint_file)
        self.x_raw = self.df['x'].values
        self.y_raw = self.df['y'].values
        self.smooth_factor = smooth_factor
        self.num_points = num_points

        # Load map
        self.image, self.extent, self.resolution = self.load_map_and_extent(map_yaml_file)
        self.waypoint_offset = [0.0, 0.0]  # Changed from image_offset to waypoint_offset
        self.dragging_point = None
        self.dragging_waypoints = False  # Changed from dragging_image to dragging_waypoints
        self.last_mouse_pos = None

        # Smoothing
        self.x_smooth, self.y_smooth = self.generate_smoothed_path()

        # Plot setup
        self.fig, self.ax = plt.subplots()
        self.image_plot = self.ax.imshow(self.image, cmap='gray', origin='lower', extent=self.extent, alpha=0.6)

        self.raw_plot = self.ax.plot(self.x_raw + self.waypoint_offset[0], self.y_raw + self.waypoint_offset[1], 'bo-', alpha=0.5, label='Raw Waypoints')[0]
        self.scatter = self.ax.scatter(self.x_smooth + self.waypoint_offset[0], self.y_smooth + self.waypoint_offset[1], color='red', label='Smoothed Path', picker=True)
        self.line = self.ax.plot(self.x_smooth + self.waypoint_offset[0], self.y_smooth + self.waypoint_offset[1], '-', color='red')[0]

        # Events
        self.fig.canvas.mpl_connect('button_press_event', self.on_press)
        self.fig.canvas.mpl_connect('button_release_event', self.on_release)
        self.fig.canvas.mpl_connect('motion_notify_event', self.on_motion)
        self.fig.canvas.mpl_connect('close_event', self.on_close)
        self.fig.canvas.mpl_connect('key_press_event', self.on_key_press)

        self.ax.set_title("Smoothed Path Editor with Background Map\n(Arrow keys: move, Right-click: drag, R/E: rotate ±5°, +/-: scale)")
        self.ax.set_xlabel("X")
        self.ax.set_ylabel("Y")
        self.ax.grid(True)
        self.ax.legend()
        plt.show()

    def load_map_and_extent(self, yaml_file):
        with open(yaml_file, 'r') as f:
            config = yaml.safe_load(f)

        pgm_path = os.path.join(os.path.dirname(yaml_file), config['image'])
        image = imread(pgm_path)
        resolution = config['resolution']
        origin_x, origin_y = config['origin'][0], config['origin'][1]
        height, width = image.shape[:2]

        # Map size
        map_width = width * resolution
        map_height = height * resolution

        # Map and waypoint centers
        map_center_x = origin_x + map_width / 2
        map_center_y = origin_y + map_height / 2
        waypoint_center_x = (self.x_raw.min() + self.x_raw.max()) / 2
        waypoint_center_y = (self.y_raw.min() + self.y_raw.max()) / 2

        # Offset image to center under waypoints
        # offset_x = waypoint_center_x - map_center_x
        # offset_y = waypoint_center_y - map_center_y

        extent = [
            origin_x,
            origin_x + map_width,
            origin_y,
            origin_y + map_height
        ]

        return image, extent, resolution

    def update_waypoint_position(self):
        # Update raw waypoints display
        self.raw_plot.set_data(self.x_raw + self.waypoint_offset[0], self.y_raw + self.waypoint_offset[1])
        
        # Update smoothed path display
        self.scatter.set_offsets(np.c_[self.x_smooth + self.waypoint_offset[0], self.y_smooth + self.waypoint_offset[1]])
        self.line.set_data(self.x_smooth + self.waypoint_offset[0], self.y_smooth + self.waypoint_offset[1])
        
        self.fig.canvas.draw_idle()

    def generate_smoothed_path(self):
        MIN_OUTPUT_POINTS = 300
        target_points = max(self.num_points, MIN_OUTPUT_POINTS)

        if len(self.x_raw) < 2:
            raise ValueError("Not enough input points for smoothing.")

        tck, _ = splprep([self.x_raw, self.y_raw], s=self.smooth_factor)
        unew = np.linspace(0, 1.0, target_points)
        x_smooth, y_smooth = splev(unew, tck)

        if len(x_smooth) < MIN_OUTPUT_POINTS:
            raise ValueError(f"Smoothing produced only {len(x_smooth)} points — need at least {MIN_OUTPUT_POINTS}.")

        return np.array(x_smooth), np.array(y_smooth)

    def update_display(self):
        self.scatter.set_offsets(np.c_[self.x_smooth + self.waypoint_offset[0], self.y_smooth + self.waypoint_offset[1]])
        self.line.set_data(self.x_smooth + self.waypoint_offset[0], self.y_smooth + self.waypoint_offset[1])
        self.fig.canvas.draw_idle()

    def on_press(self, event):
        if event.inaxes != self.ax:
            return
        if event.button == 3:  # Right-click to drag the waypoints
            self.dragging_waypoints = True
            self.last_mouse_pos = (event.xdata, event.ydata)
        else:
            # Check for individual point dragging (adjusted for waypoint offset)
            x_display = self.x_smooth + self.waypoint_offset[0]
            y_display = self.y_smooth + self.waypoint_offset[1]
            dist = np.hypot(x_display - event.xdata, y_display - event.ydata)
            if dist.min() < 0.1:
                self.dragging_point = dist.argmin()

    def on_motion(self, event):
        if event.inaxes != self.ax:
            return
        if self.dragging_waypoints and self.last_mouse_pos is not None:
            dx = event.xdata - self.last_mouse_pos[0]
            dy = event.ydata - self.last_mouse_pos[1]
            self.waypoint_offset[0] += dx
            self.waypoint_offset[1] += dy
            self.last_mouse_pos = (event.xdata, event.ydata)
            self.update_waypoint_position()
        elif self.dragging_point is not None:
            # Adjust individual point (accounting for waypoint offset)
            self.x_smooth[self.dragging_point] = event.xdata - self.waypoint_offset[0]
            self.y_smooth[self.dragging_point] = event.ydata - self.waypoint_offset[1]
            self.update_display()

    def on_release(self, event):
        self.dragging_point = None
        self.dragging_waypoints = False
        self.last_mouse_pos = None

    def scale_waypoints(self, scale_factor):
        # Calculate center of raw waypoints
        center_x = np.mean(self.x_raw)
        center_y = np.mean(self.y_raw)
        
        # Scale waypoints relative to their center
        x_centered = self.x_raw - center_x
        y_centered = self.y_raw - center_y
        
        # Apply scaling
        x_scaled = x_centered * scale_factor
        y_scaled = y_centered * scale_factor
        
        self.x_raw = x_scaled + center_x
        self.y_raw = y_scaled + center_y
        
        # Regenerate smoothed path with scaled waypoints
        self.x_smooth, self.y_smooth = self.generate_smoothed_path()
        
        # Update display
        self.update_waypoint_position()

    def rotate_waypoints(self, degrees):
        # Calculate center of raw waypoints
        center_x = np.mean(self.x_raw)
        center_y = np.mean(self.y_raw)
        
        # Convert degrees to radians
        angle = np.radians(degrees)
        
        # Rotate raw waypoints around their center
        x_centered = self.x_raw - center_x
        y_centered = self.y_raw - center_y
        
        # Apply rotation matrix: [cos(θ) -sin(θ); sin(θ) cos(θ)]
        x_rotated = x_centered * np.cos(angle) - y_centered * np.sin(angle)
        y_rotated = x_centered * np.sin(angle) + y_centered * np.cos(angle)
        
        self.x_raw = x_rotated + center_x
        self.y_raw = y_rotated + center_y
        
        # Regenerate smoothed path with rotated waypoints
        self.x_smooth, self.y_smooth = self.generate_smoothed_path()
        
        # Update display
        self.update_waypoint_position()

    def on_key_press(self, event):
        step = 0.1  # Adjust as needed for faster/slower movement
        scale_step = 0.1  # Scale increment/decrement
        rotation_step = 5.0  # Rotation in degrees
        
        if event.key == 'left':
            self.waypoint_offset[0] -= step
        elif event.key == 'right':
            self.waypoint_offset[0] += step
        elif event.key == 'up':
            self.waypoint_offset[1] += step
        elif event.key == 'down':
            self.waypoint_offset[1] -= step
        elif event.key == 'r':  # Press 'r' to rotate waypoints counterclockwise
            self.rotate_waypoints(rotation_step)
            return  # Don't call update_waypoint_position again
        elif event.key == 'e':  # Press 'e' to rotate waypoints clockwise
            self.rotate_waypoints(-rotation_step)
            return  # Don't call update_waypoint_position again
        elif event.key == '+' or event.key == '=':  # Press '+' to expand scale
            self.scale_waypoints(1.0 + scale_step)
            return  # Don't call update_waypoint_position again
        elif event.key == '-':  # Press '-' to contract scale
            self.scale_waypoints(1.0 - scale_step)
            return  # Don't call update_waypoint_position again
        else:
            return
        self.update_waypoint_position()

    def on_close(self, event):
        output_file = 'src/pure_pursuit/racelines/output.csv'
        # Apply the offset to the final coordinates
        df_final = pd.DataFrame({
            'x': self.x_smooth + self.waypoint_offset[0], 
            'y': self.y_smooth + self.waypoint_offset[1]
        })
        df_final.to_csv(output_file, index=False)
        print(f"Saved adjusted smoothed path to {output_file}")
        print(f"Final waypoint offset: dx={self.waypoint_offset[0]:.2f}, dy={self.waypoint_offset[1]:.2f}")


SmoothedPathEditorWithImage(
    waypoint_file='src/pure_pursuit/racelines/adjusted_smoothed_path.csv',
    map_yaml_file='src/particle_filter/maps/hallway.yaml',
    smooth_factor=2.0
)