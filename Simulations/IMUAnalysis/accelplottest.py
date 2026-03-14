import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial.transform import Rotation as R
from scipy.integrate import cumulative_trapezoid
import pandas as pd
import os

# --- 1. Robust Path Setup ---
# This ensures the script finds the CSVs even when moved to GitHub/different folders
base_dir = os.path.dirname(os.path.abspath(__file__))
gps_path = os.path.join(base_dir, 'prospect_flight_gps.csv')
flight_path = os.path.join(base_dir, 'rotatordatanew.csv')

# --- 2. Load and Clean Data ---
columns_read_aim = ['time', 'GPS MSL']
data_aim = pd.read_csv(gps_path, usecols=columns_read_aim, na_values=['undefined']).dropna()

columns_read_flight = [
    'Time Reference(seconds)', 'fc1LowImuValuesAccelX.distinct', 
    'fc1LowImuValuesAccelY.distinct', 'fc1LowImuValuesAccelZ.distinct', 
    'fc1LowImuValuesGyroX.distinct', 'fc1LowImuValuesGyroY.distinct', 
    'fc1LowImuValuesGyroZ.distinct', 'fc1BaroValuesAltitude.distinct'
]
data_flight = pd.read_csv(flight_path, usecols=columns_read_flight, na_values=['undefined']).dropna()

# --- 3. Synchronize Time (The "Launch" Zeroing) ---
# Shift AIM time so launch (650.578) becomes 0
data_aim['synced_time'] = data_aim['time'] - 650.578
# Flight data is already at 0, but we create a synced column for consistency
data_flight['synced_time'] = data_flight['Time Reference(seconds)']

# --- 4. Filter by Shared Window ---
start_time = -30
end_time = 30

df_flight = data_flight[(data_flight['synced_time'] >= start_time) & (data_flight['synced_time'] <= end_time)].copy()
df_aim = data_aim[(data_aim['synced_time'] >= start_time) & (data_aim['synced_time'] <= end_time)].copy()

# --- 5. Process Flight Data (High Freq) ---
# Re-extract values from the FILTERED dataframe to ensure matching dimensions
time_flight = df_flight['synced_time'].values

# Gyro and Accel math
static_mask = df_flight['synced_time'] < 0
gyro_bias = df_flight.loc[static_mask, ['fc1LowImuValuesGyroX.distinct', 'fc1LowImuValuesGyroY.distinct', 'fc1LowImuValuesGyroZ.distinct']].mean().values
baro_bias = df_flight.loc[static_mask, 'fc1BaroValuesAltitude.distinct'].mean()

gyro = (df_flight[['fc1LowImuValuesGyroX.distinct', 'fc1LowImuValuesGyroY.distinct', 'fc1LowImuValuesGyroZ.distinct']].values - gyro_bias) * (np.pi / 180)
accel_body = df_flight[['fc1LowImuValuesAccelX.distinct', 'fc1LowImuValuesAccelY.distinct', 'fc1LowImuValuesAccelZ.distinct']].values * 9.81


#gyro[time_flight < 20] = 0  # Zero out pre-launch gyro to prevent drift
# Orientation and World Accel
dt = np.diff(time_flight, prepend=time_flight[0])
delta_rotations = R.from_rotvec(gyro * dt[:, None])
current_rot = R.identity()
rot_list = []
for dr in delta_rotations:
    current_rot = current_rot * dr
    rot_list.append(current_rot)
rotations = R.concatenate(rot_list)

accel_world = rotations.apply(accel_body)
a_world_x = accel_world[:, 0] - 9.81 # Subtract gravity
a_world_x[time_flight < 0] = 0  # Zero out pre-launch accel to prevent drift
a_body_x = accel_body[:, 0] - 9.81
a_body_x[time_flight < 0] = 0  # Zero out pre
# Integration
vel_x = cumulative_trapezoid(a_world_x, time_flight, initial=0)
disp_x = cumulative_trapezoid(vel_x, time_flight, initial=0)

vel_x_before = cumulative_trapezoid(a_body_x, time_flight, initial=0)
disp_x_before = cumulative_trapezoid(vel_x_before, time_flight, initial=0)
# Barometer
baro_alt = df_flight['fc1BaroValuesAltitude.distinct'].values - baro_bias

# --- 6. Process AIM Data (Low Freq) ---
time_aim = df_aim['synced_time'].values
aim_alt = df_aim['GPS MSL'].values - 625.0

# --- 7. Plotting ---
plt.figure(figsize=(12, 8))

# Plotting with respective time arrays prevents "dimension mismatch"
plt.subplot(2, 1, 1)
#plt.plot(time_flight, disp_x, label='Displacement X (Accel + Gyro)', color='blue')
plt.plot(time_aim, aim_alt, label='AIM GPS Altitude', linestyle='-.', color='red')
plt.plot(time_flight, baro_alt, label='Barometer Altitude', linestyle=':', color='green')
plt.plot(time_flight, disp_x_before, label='Displacement X (Accel Only)', linestyle='--', color='cyan')
plt.plot(time_flight, disp_x, label='Displacement X (Accel + Gyro)', color='blue')
plt.axvline(0, color='black', linestyle='--', alpha=0.5, label='Launch T=0')
plt.axvline(23.5, color = 'purple', linestyle='--', alpha=0.5, label='Apogee ~23.5s')
plt.xlabel('Time since Launch (seconds)')
plt.ylabel('Altitude / Displacement (m)')
plt.title('Multi-Sensor Flight Path Synchronization')
plt.legend()
plt.grid(True, alpha=0.3)
plt.subplot(2, 1, 2)
plt.plot(time_flight, gyro[:, 0], label='Gyro X (World Frame)', color='blue')
plt.plot(time_flight, gyro[:, 1], label='Gyro Y (World Frame)', color='green')
plt.plot(time_flight, gyro[:, 2], label='Gyro Z (World Frame)', color='orange')
plt.xlabel('Time since Launch (seconds)')
plt.ylabel('Angular Velocity (rad/s)')
plt.title('Gyro Data Over Time')
plt.legend()
plt.grid(True, alpha=0.3)
plt.show()