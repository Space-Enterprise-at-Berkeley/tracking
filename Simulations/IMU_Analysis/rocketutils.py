# rocket_utils.py
import numpy as np
from scipy.signal import butter, filtfilt

class MadgwickAHRS:
    def __init__(self, sample_rate=100.0, beta=0.1):
        self.dt = 1.0 / sample_rate
        self.beta = beta
        self.q = np.array([1.0, 0.0, 0.0, 0.0])

    def update_imu(self, gyr, acc):
        w, x, y, z = self.q
        gx, gy, gz = gyr
        ax, ay, az = acc

        norm = np.sqrt(ax**2 + ay**2 + az**2)
        if norm == 0: return self.q
        ax, ay, az = ax/norm, ay/norm, az/norm

        f1 = 2.0 * (x * z - w * y) - ax
        f2 = 2.0 * (w * x + y * z) - ay
        f3 = 1.0 - 2.0 * (x**2 + y**2) - az
        
        j = np.array([
            [-2.0*y,  2.0*z, -2.0*w, 2.0*x],
            [ 2.0*x,  2.0*w,  2.0*z, 2.0*y],
            [ 0.0,   -4.0*x, -4.0*y, 0.0  ]
        ])
        
        step = j.T @ np.array([f1, f2, f3])
        step /= np.linalg.norm(step)

        q_dot_w = 0.5 * (-x * gx - y * gy - z * gz)
        q_dot_x = 0.5 * ( w * gx + y * gz - z * gy)
        q_dot_y = 0.5 * ( w * gy - x * gz + z * gx)
        q_dot_z = 0.5 * ( w * gz + x * gy - y * gx)

        self.q[0] += (q_dot_w - self.beta * step[0]) * self.dt
        self.q[1] += (q_dot_x - self.beta * step[1]) * self.dt
        self.q[2] += (q_dot_y - self.beta * step[2]) * self.dt
        self.q[3] += (q_dot_z - self.beta * step[3]) * self.dt

        self.q /= np.linalg.norm(self.q)
        return self.q

def apply_lowpass(data, cutoff_freq, fs, order=4):
    """
    Applies a Butterworth low-pass filter with an internal Nyquist safety check.
    """
    nyquist = 0.5 * fs
    
    # Safety Check: The cutoff must be strictly less than the Nyquist frequency
    if cutoff_freq >= nyquist:
        # We cap it at 99% of Nyquist to avoid the ValueError
        safe_cutoff = nyquist * 0.99
        print(f"DEBUG: Cutoff {cutoff_freq}Hz is too high for fs {fs}Hz. Adjusting to {safe_cutoff:.2f}Hz")
        cutoff_freq = safe_cutoff
    elif cutoff_freq <= 0:
        # Cutoff must be positive
        cutoff_freq = 0.001 

    # Normalizing the frequency (this value must be between 0 and 1)
    # Wn = cutoff / Nyquist
    Wn = cutoff_freq / nyquist
    
    b, a = butter(order, Wn, btype='low', analog=False)
    return filtfilt(b, a, data)
def calculate_orientation(gyro_x, gyro_y, gyro_z, time_stamps, q_start):
    q = q_start
    q_list = [q]

    for i in range(1, len(time_stamps)):
        dt = time_stamps[i] - time_stamps[i-1]

        wx = gyro_x[i]
        wy = gyro_y[i]
        wz = gyro_z[i]

        omega_mag = np.sqrt(wx**2 + wy**2 + wz**2)

        if omega_mag > 0:
            theta = omega_mag * dt
            axis = np.array([wx, wy, wz]) / omega_mag

            dq = np.zeros(4)
            dq[0] = np.cos(theta/2)
            dq[1:] = axis * np.sin(theta/2)
        else:
            dq = np.array([1, 0, 0, 0])

        q = quaternion_multiplication(q, dq)
        q = q / np.linalg.norm(q)

        q_list.append(q)

    return np.array(q_list)
def quaternion_multiplication(q1, q2):
    w1, x1, y1, z1 = q1
    w2, x2, y2, z2 = q2
    w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2
    x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2
    y = w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2
    z = w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2
    return np.array([w, x, y, z])