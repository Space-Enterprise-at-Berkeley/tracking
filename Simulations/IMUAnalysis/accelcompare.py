import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

columns_read_aim = ['time', 'acceleration']
columns_read_flight = ['Time Reference(seconds)','fc1LowImuValuesAccelX.distinct']
columns_read_flight_high = ['Time Reference','fc1HighImuValuesAccelX.value']
data_aim = pd.read_csv('prospect_flight.csv', usecols=columns_read_aim, na_values =['undefined'])
data_flight = pd.read_csv('rotatordatanew.csv', usecols=columns_read_flight, na_values =['undefined'])
data_high = pd.read_csv('IMU-data-new.csv', usecols=columns_read_flight_high, na_values =['undefined'])
data_aim = data_aim.dropna()
data_flight = data_flight.dropna()
data_high = data_high.dropna()

Start_time = -10
End_time = 40
data_flight = data_flight[(data_flight['Time Reference(seconds)'] >= Start_time) & (data_flight['Time Reference(seconds)'] <= End_time)]
data_high = data_high[(data_high['Time Reference'] >= Start_time) & (data_high['Time Reference'] <= End_time)]

accel_aim = data_aim['acceleration'].values
time_aim = data_aim['time'].values -650.578
accel_flight_low = data_flight['fc1LowImuValuesAccelX.distinct'].values
accel_flight_high = data_high['fc1HighImuValuesAccelX.value'].values
time_flight = data_flight['Time Reference(seconds)'].values
time_high = data_high['Time Reference'].values




plt.figure(figsize=(12, 6))
plt.plot(time_aim, accel_aim, label='AIM Acceleration', color='blue')
plt.plot(time_flight, accel_flight_low, label='Low IMU Acceleration', color='orange', linestyle='--')
plt.plot(time_high, accel_flight_high, label='High IMU Acceleration', color='green',linestyle ='--')
plt.xlabel('Time (seconds)')
plt.xlim(-10, 30)
plt.ylim(-5, 10)
plt.ylabel('Acceleration (m/s²)')
plt.title('Acceleration Comparison Between AIM and Flight Data')
plt.legend()
plt.grid()
plt.show()
