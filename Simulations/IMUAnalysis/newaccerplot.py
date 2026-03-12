from scipy.spatial.transform import Rotation as R
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import cumulative_trapezoid
import pandas as pd 

columns_read_1 = ['Time Reference(seconds)','fc1LowImuValuesAccelX.distinct', 'fc1LowImuValuesAccelY.distinct', 'fc1LowImuValuesAccelZ.distinct', 'fc1LowImuValuesGyroX.distinct', 'fc1LowImuValuesGyroY.distinct', 'fc1LowImuValuesGyroZ.distinct', 'fc1BaroValuesAltitude.distinct']
data = pd.read_csv('rotatordatanew.csv', usecols=columns_read_1, na_values =['undefined'])
data = data.dropna()

start_time = -30
end_time = 50

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

a_body_x = data['fc1LowImuValuesAccelX.distinct'].values * 9.81 
a_body_y = data['fc1LowImuValuesAccelY.distinct'].values * 9.81
a_body_z = data['fc1LowImuValuesAccelZ.distinct'].values * 9.81

barometer_altitude = data['fc1BaroValuesAltitude.distinct'].values - barometer_bias
barometer_altitude -= barometer_altitude[0]

gyro = np.column_stack((gyro_x, gyro_y, gyro_z))
dt = np.diff(time_stamps, prepend=time_stamps[0])
rotations = R.from_rotvec(gyro * dt[:, None])
delta_rotations = R.from_rotvec(gyro * dt[:, None])
rotations = [delta_rotations[0]]
for i in range(1, len(delta_rotations)):
    rotations.append(rotations[-1] * delta_rotations[i])
rotations = R.concatenate(rotations)
accel_body = np.column_stack((a_body_x, a_body_y, a_body_z))
accel_world = rotations.apply(accel_body)

a_world_x = accel_world[:, 0] - 9.81
a_world_y = accel_world[:, 1]
a_world_z = accel_world[:, 2]

velocity_x = cumulative_trapezoid(a_world_x, time_stamps, initial=0)
velocity_y = cumulative_trapezoid(a_world_y, time_stamps, initial=0)
velocity_z = cumulative_trapezoid(a_world_z, time_stamps, initial=0)

displacement_x = cumulative_trapezoid(velocity_x, time_stamps, initial=0)
displacement_y = cumulative_trapezoid(velocity_y, time_stamps, initial=0)
displacement_z = cumulative_trapezoid(velocity_z, time_stamps, initial=0)

plt.figure(figsize=(12, 8))
plt.subplot(4, 1, 1)
plt.plot(time_stamps, a_world_x, label='Accel X')
plt.plot(time_stamps, a_body_x - 9.81, label='Accel X Before Correction', linestyle='--')
plt.title('Acceleration vs Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Acceleration (m/s²)')
plt.subplot(4, 1, 2)
plt.plot(time_stamps, velocity_x, label='Velocity X')
plt.plot(time_stamps, cumulative_trapezoid(a_body_x-9.81, time_stamps, initial=0), label='Velocity X Before Correction', linestyle='--')
plt.title('Velocity vs Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Velocity (m/s)')
plt.subplot(4, 1, 3)
plt.plot(time_stamps, displacement_x, label='Displacement X')
plt.plot(time_stamps, cumulative_trapezoid(cumulative_trapezoid(a_body_x-9.81, time_stamps, initial=0), time_stamps, initial=0), label='Displacement X Before Correction', linestyle='--')
plt.plot(time_stamps, data['fc1BaroValuesAltitude.distinct'].values - barometer_bias, label='Barometric Altitude Change', linestyle=':')
plt.title('Displacement vs Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Displacement (m)')
plt.legend()
plt.show()