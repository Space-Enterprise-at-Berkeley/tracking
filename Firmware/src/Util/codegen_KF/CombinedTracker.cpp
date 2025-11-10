//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CombinedTracker.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "CombinedTracker.h"
#include "codegenTest_data.h"
#include "rt_nonfinite.h"
#include "trackingKF.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// function obj = GPSUpdate(obj, time, value)
//
// Arguments    : double b_time
//                const double b_value[3]
// Return Type  : void
//
void CombinedTracker::GPSUpdate(double b_time, const double b_value[3])
{
  // 'CombinedTracker:34' obj.Filter.MeasurementModel = obj.GPSModel;
  std::copy(&GPSModel[0], &GPSModel[27], &Filter.pMeasurementModel[0]);
  // 'CombinedTracker:35' obj.Filter.MeasurementNoise = obj.GPSNoise;
  for (int i{0}; i < 9; i++) {
    double d;
    d = GPSNoise[i];
    State[i] = d;
    Filter.pMeasurementNoise[i] = d;
  }
  // 'CombinedTracker:37' predict(obj.Filter, time-obj.Time);
  Filter.predict(b_time - Time);
  // 'CombinedTracker:38' correct(obj.Filter, value);
  Filter.correct(b_value);
  // 'CombinedTracker:40' obj.Time = time;
  Time = b_time;
  // 'CombinedTracker:41' obj.State = obj.Filter.State;
  std::copy(&Filter.pState[0], &Filter.pState[9], &State[0]);
}

//
// function obj = accelUpdate(obj, time, value)
//
// Arguments    : double b_time
//                const double b_value[3]
// Return Type  : void
//
void CombinedTracker::accelUpdate(double b_time, const double b_value[3])
{
  // 'CombinedTracker:44' obj.Filter.MeasurementModel = obj.AccelModel;
  std::copy(&AccelModel[0], &AccelModel[27], &Filter.pMeasurementModel[0]);
  // 'CombinedTracker:45' obj.Filter.MeasurementNoise = obj.AccelNoise;
  for (int i{0}; i < 9; i++) {
    double d;
    d = AccelNoise[i];
    State[i] = d;
    Filter.pMeasurementNoise[i] = d;
  }
  // 'CombinedTracker:47' predict(obj.Filter, time-obj.Time);
  Filter.predict(b_time - Time);
  // 'CombinedTracker:48' correct(obj.Filter, value);
  Filter.correct(b_value);
  // 'CombinedTracker:50' obj.Time = time;
  Time = b_time;
  // 'CombinedTracker:51' obj.State = obj.Filter.State;
  std::copy(&Filter.pState[0], &Filter.pState[9], &State[0]);
}

//
// function state = extrapolate(obj, time)
//
// Arguments    : double b_time
//                double state[9]
// Return Type  : void
//
void CombinedTracker::extrapolate(double b_time, double state[9]) const
{
  static const signed char b_iv[9]{0, 0, 1, 0, 0, 0, 0, 0, 0};
  static const signed char b_iv1[9]{0, 0, 0, 0, 0, 1, 0, 0, 0};
  static const signed char iv2[9]{0, 0, 0, 0, 0, 0, 0, 0, 1};
  double dv[81];
  double dt;
  double dt2;
  // 'CombinedTracker:20' dt = time - obj.Time;
  dt = b_time - Time;
  // 'CombinedTracker:21' dt2 = dt^2/2;
  dt2 = dt * dt / 2.0;
  // 'CombinedTracker:22' transition = [1 dt dt2 0 0  0   0 0  0;
  // 'CombinedTracker:23'                           0 1  dt  0 0  0   0 0  0  ;
  // 'CombinedTracker:24'                           0 0  1   0 0  0   0 0  0  ;
  // 'CombinedTracker:25'                           0 0  0   1 dt dt2 0 0  0  ;
  // 'CombinedTracker:26'                           0 0  0   0 1  dt  0 0  0  ;
  // 'CombinedTracker:27'                           0 0  0   0 0  1   0 0  0  ;
  // 'CombinedTracker:28'                           0 0  0   0 0  0   1 dt dt2;
  // 'CombinedTracker:29'                           0 0  0   0 0  0   0 1  dt ;
  // 'CombinedTracker:30'                           0 0  0   0 0  0   0 0  1  ];
  // 'CombinedTracker:31' state = transition * obj.State;
  dv[0] = 1.0;
  dv[9] = dt;
  dv[18] = dt2;
  dv[27] = 0.0;
  dv[36] = 0.0;
  dv[45] = 0.0;
  dv[54] = 0.0;
  dv[63] = 0.0;
  dv[72] = 0.0;
  dv[1] = 0.0;
  dv[10] = 1.0;
  dv[19] = dt;
  dv[28] = 0.0;
  dv[37] = 0.0;
  dv[46] = 0.0;
  dv[55] = 0.0;
  dv[64] = 0.0;
  dv[73] = 0.0;
  dv[3] = 0.0;
  dv[12] = 0.0;
  dv[21] = 0.0;
  dv[30] = 1.0;
  dv[39] = dt;
  dv[48] = dt2;
  dv[57] = 0.0;
  dv[66] = 0.0;
  dv[75] = 0.0;
  dv[4] = 0.0;
  dv[13] = 0.0;
  dv[22] = 0.0;
  dv[31] = 0.0;
  dv[40] = 1.0;
  dv[49] = dt;
  dv[58] = 0.0;
  dv[67] = 0.0;
  dv[76] = 0.0;
  dv[6] = 0.0;
  dv[15] = 0.0;
  dv[24] = 0.0;
  dv[33] = 0.0;
  dv[42] = 0.0;
  dv[51] = 0.0;
  dv[60] = 1.0;
  dv[69] = dt;
  dv[78] = dt2;
  dv[7] = 0.0;
  dv[16] = 0.0;
  dv[25] = 0.0;
  dv[34] = 0.0;
  dv[43] = 0.0;
  dv[52] = 0.0;
  dv[61] = 0.0;
  dv[70] = 1.0;
  dv[79] = dt;
  std::memset(&state[0], 0, 9U * sizeof(double));
  for (int i{0}; i < 9; i++) {
    dv[9 * i + 2] = b_iv[i];
    dv[9 * i + 5] = b_iv1[i];
    dv[9 * i + 8] = iv2[i];
    dt = State[i];
    for (int i1{0}; i1 < 9; i1++) {
      state[i1] += dv[i1 + 9 * i] * dt;
    }
  }
}

//
// function obj = CombinedTracker()
//
// Arguments    : void
// Return Type  : CombinedTracker *
//
CombinedTracker *CombinedTracker::init()
{
  static const signed char b_iv1[27]{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  static const signed char b_iv[9]{5, 0, 0, 0, 5, 0, 0, 0, 5};
  CombinedTracker *obj;
  obj = this;
  for (int i{0}; i < 27; i++) {
    obj->GPSModel[i] = iv[i];
  }
  for (int i{0}; i < 9; i++) {
    obj->GPSNoise[i] = b_iv[i];
  }
  for (int i{0}; i < 27; i++) {
    obj->AccelModel[i] = b_iv1[i];
  }
  // 'CombinedTracker:1' handle
  // 'CombinedTracker:15' obj.Time = 0;
  obj->Time = 0.0;
  // 'CombinedTracker:16' obj.State = [0;0;0;0;0;0;0;0;0];
  for (int i{0}; i < 9; i++) {
    obj->AccelNoise[i] = b_iv[i];
    obj->State[i] = 0.0;
  }
  // 'CombinedTracker:17' obj.Filter = trackingKF("MotionModel","3D Constant
  // Acceleration");
  obj->Filter.init();
  return obj;
}

//
// File trailer for CombinedTracker.cpp
//
// [EOF]
//
