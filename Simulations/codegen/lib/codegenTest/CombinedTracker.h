//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CombinedTracker.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
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
  void GPSUpdate(double b_time, const double b_value[3]);
  void accelUpdate(double b_time, const double b_value[3]);
  void extrapolate(double b_time, double state[9]) const;
  double Time;
  double State[9];
  coder::trackingKF Filter;
  double GPSModel[27];
  double GPSNoise[9];
  double AccelModel[27];
  double AccelNoise[9];
};

#endif
//
// File trailer for CombinedTracker.h
//
// [EOF]
//
