//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: trackingKF.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef TRACKINGKF_H
#define TRACKINGKF_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
class trackingKF {
public:
  trackingKF *init();
  void set_MeasurementNoise();
  void predict(double varargin_1);
  void setupInitialDistributions();
  void get_MeasurementModel(double value_data[], int value_size[2]) const;
  void predict(const double varargin_1[81], const double varargin_2[27]);
  void correct(const double z[3]);
  void KalmanFilter_correct(const double z[3]);
  void get_MeasurementNoise(double value_data[], int value_size[2]) const;

protected:
  void setMeasurementNoise(const double val_data[]);
  void ensureMethodDefinition();
  void ensureSmootherStateSizeIsDefined();

private:
  trackingKF *LinearizedSmoother_init();
  trackingKF *KalmanFilter_init();

public:
  double StateTransitionModel[81];
  double pState[9];
  double pStateCovariance[81];
  double pMeasurementModel[27];
  double pMeasurementNoise[9];
  bool pIsDistributionsSetup;
  bool pIsInitialized;
  bool pIsSmootherStateSizeInitialized;

protected:
  double ProcessNoiseModel[27];
  double pN;
  double pV;
  double pProcessNoise[9];
  bool IsLastJacobianInitialized;

private:
  bool pIsStateTransitionLocked;
};

} // namespace coder

#endif
//
// File trailer for trackingKF.h
//
// [EOF]
//
