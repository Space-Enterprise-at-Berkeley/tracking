//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: trackingKF.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 02-Dec-2025 17:03:31
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
  float pSmootherStateSize;
  bool pIsSmootherStateSizeInitialized;
  bool pWasRetrodicted;

protected:
  float ProcessNoiseModel[27];
  float pN;
  float pV;
  float pProcessNoise[9];
  float pMeasurementNoise[9];
  bool pHasPrediction;
  float LastJacobian[81];
  bool IsLastJacobianInitialized;

private:
  bool pIsSmoothingLocked;
  bool pIsStateTransitionLocked;
};

} // namespace coder

#endif
//
// File trailer for trackingKF.h
//
// [EOF]
//
