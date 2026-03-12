import numpy as np
import matplotlib.pyplot as plt

# 1. Load the data using genfromtxt
# skip_header=1 handles the title row
# delimiter=',' for CSV
# usecols=(1, 18) for the 2nd and 19th columns
# dtype=str allows us to capture "undefined" without crashing
raw_data = np.genfromtxt('/Users/georgexu/Desktop/Berkeley Academics/prospect_flight_gps.csv', delimiter=',', skip_header=1, 
                         usecols=(0,1,2,3,4))

# 2. Extract columns/
time_raw = raw_data[:, 0]
lat_raw = raw_data[:, 1]
lon_raw = raw_data[:, 2]
alt_raw = raw_data[:, 3]
sv_raw = raw_data[:, 4]
print(time_raw)
print(alt_raw)

# 3. Handle "undefined" values
# Create a mask for rows that are NOT "undefined" (or whatever your error string is)
# This also filters out empty strings
mask = (alt_raw != 'undefined') & (alt_raw != '')

# Apply the mask to both columns

# 6. Plot
plt.figure(figsize=(10, 5))
plt.plot(time_raw[340:],alt_raw[340:], color='blue', linewidth=1, label='Altitude')
#plt.plot(time_raw,lon_raw, color='green', linewidth=1, label='Longitude')
#plt.plot(time_raw, lat_raw, color='orange', linewidth=1, label='Latitude')
#plt.plot(time_vals, sv_raw, color='tab:red', linewidth=1, label='SV Count')

plt.title("Altitude over Time (NumPy optimized)")
plt.xlabel("Time")
plt.ylabel("Altitude")
plt.grid(True)

plt.tight_layout()
plt.show()