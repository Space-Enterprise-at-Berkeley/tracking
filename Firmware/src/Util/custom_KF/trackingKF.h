// Custom KF skeleton interface matching codegen_KF/trackingKF.h.
#pragma once
// Include Files
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace kalman_filter {
class trackingKF {
public:
  trackingKF *init(const float varargin_4[9]);
  void set_ProcessNoise(const float b_value[9]);
  void set_MeasurementNoise(const float b_value[9]);
  void predict(float varargin_1);
  void correct(const float z[3]);

  float StateTransitionModel[81];
  float pState[9];
  float pStateCovariance[81];
  float pMeasurementModel[27];

protected:
  float ProcessNoiseModel[27];
  float pN;
  float pV;
  float pProcessNoise[9];
  float pMeasurementNoise[9];
};

} // namespace kalman_filter

