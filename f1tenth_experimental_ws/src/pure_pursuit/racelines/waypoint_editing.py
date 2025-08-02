import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.image import imread
from scipy.interpolate import splprep, splev
import yaml
import os
from matplotlib.transforms import Affine2D

class SmoothedPathEditorWithImage:
    def __init__(self, waypoint_file, map_yaml_file, smooth_factor=2.0, num_points=300):
        self.df = pd.read_csv(waypoint_file)
        self.x_raw = self.df['x'].values
        self.y_raw = self.df['y'].values
        self.smooth_factor = smooth_factor
        self.num_points = max(num_points, 300)

        self.image, self.extent, self.resolution = self.load_map_and_extent(map_yaml_file)
        self.image_offset = [0.0, 0.0]
        self.image_rotation = 0.0  # degrees

        self.x_smooth, self.y_smooth = self.generate_smoothed_path()

        self.fig, self.ax = plt.subplots()
        self.image_plot = self.ax.imshow(self.image, cmap='gray', origin='lower', extent=self.extent, alpha=0.6)

        self.ax.plot(self.x_raw, self.y_raw, 'bo-', alpha=0.5, label='Raw Waypoints')
        self.scatter = self.ax.scatter(self.x_smooth, self.y_smooth, color='red', label='Smoothed Path', picker=True)
        self.line = self.ax.plot(self.x_smooth, self.y_smooth, '-', color='red')[0]

        self.fig.canvas.mpl_connect('key_press_event', self.on_key_press)
        self.fig.canvas.mpl_connect('close_event', self.on_close)

        self.selected_point_idx = None  # Add this
        self.selected_marker = self.ax.scatter([], [], color='yellow', s=100, label='Selected')  # For selection
        self.dragging_point = None

        self.fig.canvas.mpl_connect('button_press_event', self.on_press)
        self.fig.canvas.mpl_connect('motion_notify_event', self.on_motion)
        self.fig.canvas.mpl_connect('button_release_event', self.on_release)



        self.ax.set_title("Move/Rotate Map: Arrow Keys + R/E")
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
        extent = [origin_x, origin_x + width * resolution, origin_y, origin_y + height * resolution]
        return image, extent, resolution

    def generate_smoothed_path(self):
        tck, _ = splprep([self.x_raw, self.y_raw], s=self.smooth_factor)
        unew = np.linspace(0, 1.0, self.num_points)
        x_smooth, y_smooth = splev(unew, tck)
        return np.array(x_smooth), np.array(y_smooth)

    def update_image_transform(self):
        transform = Affine2D().translate(*self.image_offset).rotate_deg_around(
            (self.extent[0] + self.extent[1]) / 2,
            (self.extent[2] + self.extent[3]) / 2,
            self.image_rotation
        )
        self.image_plot.set_transform(transform + self.ax.transData)
        self.fig.canvas.draw_idle()

    def on_key_press(self, event):
        step = 0.1
        rot_step = 5.0
        if event.key == 'left':
            self.image_offset[0] -= step
        elif event.key == 'right':
            self.image_offset[0] += step
        elif event.key == 'up':
            self.image_offset[1] += step
        elif event.key == 'down':
            self.image_offset[1] -= step
        elif event.key == 'r':
            self.image_rotation += rot_step
        elif event.key == 'e':
            self.image_rotation -= rot_step
        elif event.key in ('delete', 'backspace'):
            self.delete_selected_point()
        self.update_image_transform()

    def on_press(self, event):
        if event.inaxes != self.ax:
            return
        dist = np.hypot(self.x_smooth - event.xdata, self.y_smooth - event.ydata)
        if dist.min() < 0.2:
            self.selected_point_idx = dist.argmin()
            self.dragging_point = self.selected_point_idx
            self.update_selected_marker()
        else:
            self.selected_point_idx = None
            self.dragging_point = None
            self.update_selected_marker()

    def on_motion(self, event):
        if event.inaxes != self.ax or self.dragging_point is None:
            return
        self.x_smooth[self.dragging_point] = event.xdata
        self.y_smooth[self.dragging_point] = event.ydata
        self.update_display()
        self.update_selected_marker()

    def on_release(self, event):
        self.dragging_point = None


    def update_selected_marker(self):
        if self.selected_point_idx is not None:
            self.selected_marker.set_offsets([[self.x_smooth[self.selected_point_idx], self.y_smooth[self.selected_point_idx]]])
        else:
            self.selected_marker.set_offsets([])
        self.fig.canvas.draw_idle()

    def delete_selected_point(self):
        if self.selected_point_idx is not None and len(self.x_smooth) > 2:
            # Remove point from smoothed arrays
            self.x_smooth = np.delete(self.x_smooth, self.selected_point_idx)
            self.y_smooth = np.delete(self.y_smooth, self.selected_point_idx)

            # Clear selection
            self.selected_point_idx = None

            # Update red path display
            self.scatter.set_offsets(np.c_[self.x_smooth, self.y_smooth])
            self.line.set_data(self.x_smooth, self.y_smooth)
            self.update_selected_marker()
            self.fig.canvas.draw_idle()

    def update_display(self):
        self.scatter.set_offsets(np.c_[self.x_smooth, self.y_smooth])
        self.line.set_data(self.x_smooth, self.y_smooth)
        self.fig.canvas.draw_idle()

    def on_close(self, event):
        df_final = pd.DataFrame({'x': self.x_smooth, 'y': self.y_smooth})
        df_final.to_csv(
            '/home/bentoaz/NSF_IRES_2025_Codebase/f1tenth_experimental_ws/src/pure_pursuit/racelines/hallway_adjusted_2.csv',
              index=False)
        print("Saved adjusted smoothed path")

SmoothedPathEditorWithImage(
    waypoint_file='src/pure_pursuit/racelines/hallway.csv',
    map_yaml_file='src/particle_filter/maps/hallway.yaml',
    smooth_factor=2.0
)
