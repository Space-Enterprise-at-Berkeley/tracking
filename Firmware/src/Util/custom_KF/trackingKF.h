// Custom KF skeleton interface matching codegen_KF/trackingKF.h.

#ifndef CUSTOM_KF_TRACKINGKF_H
#define CUSTOM_KF_TRACKINGKF_H

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
  bool pIsDistributionsSetup;
  bool pIsInitialized;
  bool pIsSmootherStateSizeInitialized;

protected:
  float ProcessNoiseModel[27];
  float pN;
  float pV;
  float pProcessNoise[9];
  float pMeasurementNoise[9];
  bool IsLastJacobianInitialized;

private:
  bool pIsStateTransitionLocked;
};

} // namespace kalman_filter

#endif
