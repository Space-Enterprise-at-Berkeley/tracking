import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial.transform import Rotation as R
from scipy.integrate import cumulative_trapezoid
from scipy.signal import butter, filtfilt
from rocketutils import MadgwickAHRS, apply_lowpass, calculate_orientation, quaternion_multiplication
import pandas as pd


columns_read_0 = ['Time ']
columns_read_1 = ['Time Reference(seconds)','fc1LowImuValuesAccelX.distinct', 'fc1LowImuValuesAccelY.distinct', 'fc1LowImuValuesAccelZ.distinct', 'fc1LowImuValuesGyroX.distinct', 'fc1LowImuValuesGyroY.distinct', 'fc1LowImuValuesGyroZ.distinct', 'fc1BaroValuesAltitude.distinct']
#data_high_imu = pd.read_csv('IMU-data.csv', usecols=columns_read_1, na_values =['undefined'])
data = pd.read_csv('rotatordatanew.csv', usecols=columns_read_1, na_values =['undefined'])
data = data.dropna()

start_time = -1

end_time = 40


high_imu_time = 30
data = data[(data['Time Reference(seconds)'] >= start_time) & (data['Time Reference(seconds)'] <= end_time)]

static_mask = data['Time Reference(seconds)'] < 0
gyro_bias_x = data.loc[static_mask, 'fc1LowImuValuesGyroX.distinct'].mean()
gyro_bias_y = data.loc[static_mask, 'fc1LowImuValuesGyroY.distinct'].mean()
gyro_bias_z = data.loc[static_mask, 'fc1LowImuValuesGyroZ.distinct'].mean()
barometer_bias = data['fc1BaroValuesAltitude.distinct'].iloc[:-start_time].mean()

time_stamps = data['Time Reference(seconds)'].values

gyro_x = (data['fc1LowImuValuesGyroX.distinct'].values - gyro_bias_x) * (np.pi / 180)  # Convert to radians per second
gyro_y = (data['fc1LowImuValuesGyroY.distinct'].values - gyro_bias_y) * (np.pi / 180)
gyro_z = (data['fc1LowImuValuesGyroZ.distinct'].values - gyro_bias_z) * (np.pi / 180)

a_body_x = data['fc1LowImuValuesAccelX.distinct'].values * 9.81 # Convert to m/s²
para_a = 4
para_b = 8.0
#a_body_x[(a_body_x >= para_a) & (a_body_x <= para_b)] += 9.81
a_body_y = data['fc1LowImuValuesAccelY.distinct'].values * 9.81
a_body_z = data['fc1LowImuValuesAccelZ.distinct'].values * 9.81

dt_mean = np.mean(np.diff(time_stamps))
sampling_rate = 1.0 / dt_mean

# 2. Filter each axis   
a_body_x_filt = apply_lowpass(a_body_x, cutoff_freq=1.73, fs=sampling_rate)
a_body_y_filt = apply_lowpass(a_body_y, cutoff_freq=1.73, fs=sampling_rate)
a_body_z_filt = apply_lowpass(a_body_z, cutoff_freq=1.73, fs=sampling_rate)

baro_altitude = data['fc1BaroValuesAltitude.distinct'].values - barometer_bias
baro_altitude -= baro_altitude[0]
q_start = np.array([1.0,0.0,0.0,0.0])  # Identity quaternion (w, x, y, z)

q = calculate_orientation(gyro_x, gyro_y, gyro_z, time_stamps, q_start)
q_scipy = np.column_stack((q[:, 1], q[:, 2], q[:, 3], q[:, 0]))  # Convert to (x, y, z, w) format for scipy
rotations = R.from_quat(q_scipy)
accel_body = np.column_stack((a_body_x_filt, a_body_y_filt, a_body_z_filt))
accel_world = rotations.apply(accel_body)

actual_gravity = 9.81
accel_world_x = accel_world[:, 0] - actual_gravity  # Subtract gravity from the x-axis (assuming x is vertical)
accel_world_y = accel_world[:, 1]
accel_world_z = accel_world[:, 2]
print(f"DEBUG: Max accel_world_x = {np.max(accel_world_x):.2f} m/s², Min accel_world_x = {np.min(accel_world_x):.2f} m/s²")
# Calculate velocity by integrating acceleration
velocity_x = cumulative_trapezoid(accel_world_x, time_stamps, initial=0)
velocity_x -= velocity_x[static_mask][-1]  # Subtract the last velocity value during the static period to correct for drift
velocity_y = cumulative_trapezoid(accel_world_y, time_stamps, initial=0)
velocity_z = cumulative_trapezoid(accel_world_z, time_stamps, initial=0)


velocity_before_correction_x = cumulative_trapezoid(a_body_x - 9.81, time_stamps, initial=0)
velocity_before_correction_y = cumulative_trapezoid(a_body_y, time_stamps, initial=0)
velocity_before_correction_z = cumulative_trapezoid(a_body_z, time_stamps, initial=0)
# Calculate displacement by integrating velocity
displacement_x = cumulative_trapezoid(velocity_x, time_stamps, initial=0)
displacement_y = cumulative_trapezoid(velocity_y, time_stamps, initial=0)
displacement_z = cumulative_trapezoid(velocity_z, time_stamps, initial=0)

displacement_x_before_correction = cumulative_trapezoid(velocity_before_correction_x, time_stamps, initial=0)
displacement_y_before_correction = cumulative_trapezoid(velocity_before_correction_y, time_stamps, initial=0)
displacement_z_before_correction = cumulative_trapezoid(velocity_before_correction_z, time_stamps, initial=0)

alpha = 0.01
displacement_x_fused = alpha * displacement_x + (1 - alpha) * baro_altitude


# Plotting
plt.figure(figsize=(12, 8))
plt.subplot(4, 1, 1)
plt.plot(time_stamps, accel_world_x, label='Accel X')
plt.plot(time_stamps, a_body_x, label='Accel X Before Correction', linestyle='--')
#plt.plot(time_stamps, a_body_x_filt, label='Accel X Filtered', linestyle=':')
#plt.plot(time_stamps, a_body_x, label='Accel X Before Correction', linestyle='--')
#plt.plot(time_stamps, accel_world_y, label='Accel Y')
#plt.plot(time_stamps, accel_world_z, label='Accel Z')
#plt.plot(time_stamps, np.sqrt(accel_world_x **2 + accel_world_y**2 + accel_world_z**2), label='Accel Magnitude', linestyle='--')
plt.title('Acceleration vs Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Acceleration (m/s²)')
plt.legend()
plt.subplot(4, 1, 2)
plt.plot(time_stamps, velocity_x, label='Velocity X')
#plt.plot(time_stamps, velocity_y, label='Velocity Y')
#plt.plot(time_stamps, velocity_z, label='Velocity Z')
plt.plot(time_stamps, velocity_before_correction_x, label='Velocity X Before Correction', linestyle='--')
plt.title('Velocity vs Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Velocity (m/s)')
plt.legend()
plt.subplot(4, 1, 3)
plt.plot(time_stamps, displacement_x, label='Displacement X')
plt.plot(time_stamps, displacement_x_before_correction, label='Displacement X Before Correction', linestyle='--')
plt.plot(time_stamps, baro_altitude, label='Barometric Altitude Change', linestyle=':')
#plt.plot(time_stamps, displacement_x_fused, label='Fused Displacement X', linestyle='-.')
#plt.plot(time_stamps, displacement_y, label='Displacement Y')
#plt.plot(time_stamps, displacement_z, label='Displacement Z')

plt.title('Displacement vs Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Displacement (m)')
plt.legend()
plt.subplot(4, 1, 4)
plt.plot(time_stamps, gyro_x, label='Gyro X')
plt.plot(time_stamps, gyro_y, label='Gyro Y')
plt.plot(time_stamps, gyro_z, label='Gyro Z')
plt.title('Gyro vs Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Gyro (rad/s)')

plt.legend()
plt.tight_layout()
plt.show()






