//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CombinedTracker.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 22:04:03
//

#ifndef COMBINEDTRACKER_H
#define COMBINEDTRACKER_H

// Include Files
#include "rtwtypes.h"
#include "trackingKF.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
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
  coder::trackingKF *Filter;
  float GPSModel[27];
  float GPSNoise[9];
  float AccelModel[27];
  float AccelNoise[9];
  coder::trackingKF coder_buffer_pobj0;
};

#endif
//
// File trailer for CombinedTracker.h
//
// [EOF]
//
