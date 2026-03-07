// Custom KF skeleton interface matching codegen_KF/CombinedTracker.h.
#pragma once
// Include Files
#include "trackingKF.h"
#include <cstddef>
#include <cstdlib>
#include <memory>

// Type Definitions
namespace kalman_filter {
class CombinedTracker {
public:
  CombinedTracker *init();
  void setNoises(const float ProcessNoise[9], const float b_GPSNoise[9],
                 const float b_AccelNoise[9]);
  void GPSUpdate(float b_time, const float b_value[3]);
  void accelUpdate(float b_time, const float b_value[3]);
  void extrapolate(float b_time, float state[9]) const;
  float Time;
  float State[9];
  std::unique_ptr<trackingKF> Filter;
  float GPSModel[27];
  float GPSNoise[9];
  float AccelModel[27];
  float AccelNoise[9];
};
} // namespace kalman_filter

