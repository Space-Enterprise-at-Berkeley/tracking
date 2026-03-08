import numpy as np
import matplotlib.pyplot as plt

from scipy.spatial.transform import Rotation as R
from scipy.spatial.transform import Slerp
from scipy.integrate import cumulative_trapezoid
from scipy.signal import butter, filtfilt
import pandas as pd

columns_read_q = ['time.Q',' QX',' QY', ' QZ', ' QW']
columns_read_ag = ['time.v','time.l','acceleration','lat. Y accel.','lat. X accel.']
aim_data_q = pd.read_csv('prospect_flight.csv',usecols = columns_read_q, na_values = 'undefined')
aim_data_q = aim_data_q.dropna()
aim_data_ag = pd.read_csv('Gyro_Accel_AIM.csv',usecols = columns_read_ag, na_values = 'undefined')
aim_data_ag = aim_data_ag.dropna()




start_time = 0
end_time = 50

t_q = aim_data_q['time.Q'].values
q_x = aim_data_q[' QX'].values
q_y = aim_data_q[' QY'].values
q_z = aim_data_q[' QZ'].values
q_w = aim_data_q[' QW'].values

aim_data_ag = aim_data_ag[(aim_data_ag['time.l'] >= 640) & (aim_data_ag['time.l'] <= 760)]

t_v = aim_data_ag['time.v'].values
a_v = aim_data_ag['acceleration'].values
t_l = aim_data_ag['time.l'].values
t_a = (t_v + t_l)/2 # data interpolation of t_vertical and t_latititude
a_y = aim_data_ag['lat. Y accel.'].values
a_x = aim_data_ag['lat. X accel.'].values

a_o = np.column_stack([a_x,a_y,a_v])
print('hi')

q_raw = np.column_stack([q_x,q_y,q_z,q_w])
q_uncal = R.from_quat(q_raw)
q_cal = q_uncal[100]
q = q_uncal * R.inv(q_cal)
slerp = Slerp(t_q, q)
q_slerp = slerp(t_a)
a_f = q_slerp.apply(a_o)

up_f = q_slerp.apply(np.array([0, 0, 1]))
#now, t_a a_0 and q_slerp are all synced

angles = np.rad2deg(np.acos(up_f[:, 2]))

a_xc = a_f[:,0]*9.81
bias_x = np.mean(a_xc[t_a<650])
a_xc -= bias_x
a_xc[t_a<640] = 0
a_yc = a_f[:,1]*9.81
bias_y = np.mean(a_yc[t_a<650])
a_yc -= bias_y
a_yc[t_a<640] = 0
a_zc = a_f[:,2]*9.81 - 9.81
bias_z = np.mean(a_zc[t_a<650])
a_zc -=bias_z
a_zc[t_a<640] = 0

v_x = cumulative_trapezoid(a_xc,t_a, initial = 0)
v_y = cumulative_trapezoid(a_yc,t_a,initial = 0)
v_z = cumulative_trapezoid(a_zc,t_a,initial = 0)

l_x = cumulative_trapezoid(v_x,t_a,initial = 0)
l_y = cumulative_trapezoid(v_y, t_a, initial = 0)
l_z = cumulative_trapezoid(v_z,t_a,initial = 0)
print(max(l_z))
fig, axes = plt.subplots(4,1,figsize = (12,8))

axes[0].plot(t_q,q_x, label = 'Quaternion X')
axes[0].plot(t_q,q_y, label = 'Quaternion Y')
axes[0].plot(t_q,q_z, label = 'Quaternion Z')
axes[0].plot(t_q,q_w, label = 'Quaternion W')
axes[0].legend()

axes[1].plot(t_v,a_v*9.81-9.81, label = 'Vertical Acceleration')
#axes[1].plot(t_l,a_x, label = 'X Acceleration')
#axes[1].plot(t_l,a_y, label = 'Y Acceleration')
#axes[1].plot(t_a,a_f[:,0], label = 'X Acceleration Corrected', linestyle = '--')
#axes[1].plot(t_a,a_f[:,1], label = 'Y Acceleration Corrected', linestyle = '--')
axes[1].plot(t_a, a_zc, label = 'Vertical Acceleration Corrected', linestyle = '--')
axes[1].legend()

axes[2].plot(t_a,l_z, label = 'Z Displacement')

axes[3].plot(t_a, angles)


plt.show()
