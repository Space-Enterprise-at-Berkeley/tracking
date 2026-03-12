import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial.transform import Rotation as R
from scipy.integrate import cumulative_trapezoid
from scipy.signal import butter, filtfilt
from rocketutils import MadgwickAHRS, apply_lowpass, calculate_orientation, quaternion_multiplication
import pandas as pd

columns_read_aim = ['time', 'GPS MSL']
columns_read_flight = ['Time Reference(seconds)','fc1LowImuValuesAccelX.distinct', 'fc1LowImuValuesAccelY.distinct', 'fc1LowImuValuesAccelZ.distinct', 'fc1LowImuValuesGyroX.distinct', 'fc1LowImuValuesGyroY.distinct', 'fc1LowImuValuesGyroZ.distinct', 'fc1BaroValuesAltitude.distinct']
data_aim = pd.read_csv('prospect_flight_gps.csv', usecols=columns_read_aim, na_values =['undefined'])
data_flight = pd.read_csv('rotatordatanew.csv', usecols=columns_read_flight, na_values =['undefined'])
data_aim = data_aim.dropna()
data_flight = data_flight.dropna()

start_time = -30
end_time = 50

data_aim['time_offset'] = data_aim['time'] - 650.578
data_aim['GPS_MSL_offset'] = data_aim['GPS MSL'] - 625.0
data_flight = data_flight[(data_flight['Time Reference(seconds)'] >= start_time) & (data_flight['Time Reference(seconds)'] <= end_time)]
data_aim = data_aim[(data_aim['time_offset'] >= start_time) & (data_aim['time_offset'] <= end_time)]

time_stamps_flight = data_flight['Time Reference(seconds)'].values
time_stamps_aim = data_aim['time_offset'].values # Use the filtered values
aim_gps_altitude = data_aim['GPS_MSL_offset'].values # Use the filtered values

static_mask = data_flight['Time Reference(seconds)'] < 0
gyro_bias_x = data_flight.loc[static_mask, 'fc1LowImuValuesGyroX.distinct'].mean()
gyro_bias_y = data_flight.loc[static_mask, 'fc1LowImuValuesGyroY.distinct'].mean()
gyro_bias_z = data_flight.loc[static_mask, 'fc1LowImuValuesGyroZ.distinct'].mean()
barometer_bias = data_flight['fc1BaroValuesAltitude.distinct'].iloc[:-start_time].mean()

time_stamps_flight = data_flight['Time Reference(seconds)'].values
time_stamps_aim = data_aim['time'].values

gyro_x = (data_flight['fc1LowImuValuesGyroX.distinct'].values - gyro_bias_x) * (np.pi / 180)  # Convert to radians per second
gyro_y = (data_flight['fc1LowImuValuesGyroY.distinct'].values - gyro_bias_y) * (np.pi / 180)
gyro_z = (data_flight['fc1LowImuValuesGyroZ.distinct'].values - gyro_bias_z) * (np.pi / 180)

a_body_x = data_flight['fc1LowImuValuesAccelX.distinct'].values * 9.81 
a_body_y = data_flight['fc1LowImuValuesAccelY.distinct'].values * 9.81
a_body_z = data_flight['fc1LowImuValuesAccelZ.distinct'].values * 9.81

barometer_altitude = data_flight['fc1BaroValuesAltitude.distinct'].values - barometer_bias
barometer_altitude -= barometer_altitude[0]

gyro = np.column_stack((gyro_x, gyro_y, gyro_z))
dt = np.diff(time_stamps_flight, prepend=time_stamps_flight[0])
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

velocity_x = cumulative_trapezoid(a_world_x, time_stamps_flight, initial=0)
velocity_y = cumulative_trapezoid(a_world_y, time_stamps_flight, initial=0)
velocity_z = cumulative_trapezoid(a_world_z, time_stamps_flight, initial=0)

velocity_x_before_correction = cumulative_trapezoid(a_body_x-9.81, time_stamps_flight, initial=0)

displacement_x = cumulative_trapezoid(velocity_x, time_stamps_flight, initial=0)
displacement_y = cumulative_trapezoid(velocity_y, time_stamps_flight, initial=0)
displacement_z = cumulative_trapezoid(velocity_z, time_stamps_flight, initial=0)

displacement_x_before_correction = cumulative_trapezoid(velocity_x_before_correction, time_stamps_flight, initial=0)

plt.figure(figsize=(12, 8))
plt.plot(time_stamps_flight,displacement_x, label = 'Displacement X from Accelerometer with Gyroscope')
plt.plot(time_stamps_flight,displacement_x_before_correction, label = 'Displacement X from Accelerometer without Gyroscope', linestyle = '--')
plt.plot(time_stamps_aim, aim_gps_altitude, label = ' AIM GPS Altitude', linestyle = '-.')
plt.plot(time_stamps_flight, barometer_altitude, label = 'Barometer Altitude',linestyle = ':')
plt.xlabel('Time (seconds)')
plt.ylabel('Displacement / Altitude (m)')
plt.title('Displacement and Altitude vs Time')
plt.legend()
plt.grid()
plt.show()