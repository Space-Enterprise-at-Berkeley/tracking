//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CombinedTracker.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 20:32:31
//

// Include Files
#include "CombinedTracker.h"
#include "codegenTest_data.h"
#include "constacc.h"
#include "rt_nonfinite.h"
#include "trackingKF.h"

// Function Definitions
//
// Arguments    : float b_time
//                const float b_value[3]
// Return Type  : void
//
void CombinedTracker::GPSUpdate(float b_time, const float b_value[3])
{
  coder::trackingKF *obj;
  float MeasurementModelMatrix[27];
  float c_value[9];
  obj = Filter;
  for (int i{0}; i < 27; i++) {
    MeasurementModelMatrix[i] = GPSModel[i];
  }
  for (int i{0}; i < 27; i++) {
    obj->pMeasurementModel[i] = MeasurementModelMatrix[i];
  }
  float out;
  Filter->set_MeasurementNoise(GPSNoise);
  out = Time;
  Filter->predict(b_time - out);
  Filter->correct(b_value);
  Time = b_time;
  obj = Filter;
  for (int i{0}; i < 9; i++) {
    c_value[i] = obj->pState[i];
  }
  for (int i{0}; i < 9; i++) {
    State[i] = c_value[i];
  }
}

//
// Arguments    : float b_time
//                float b_value
// Return Type  : void
//
void CombinedTracker::accelUpdate(float b_time, float b_value)
{
  coder::trackingKF *obj;
  float c_value[9];
  float out;
  Filter->set_MeasurementModel(AccelModel);
  Filter->set_MeasurementNoise(AccelNoise);
  out = Time;
  Filter->predict(b_time - out);
  Filter->correct(b_value);
  Time = b_time;
  obj = Filter;
  for (int i{0}; i < 9; i++) {
    c_value[i] = obj->pState[i];
  }
  for (int i{0}; i < 9; i++) {
    State[i] = c_value[i];
  }
}

//
// Arguments    : float b_time
//                float state[9]
// Return Type  : void
//
void CombinedTracker::extrapolate(float b_time, float state[9]) const
{
  for (int i{0}; i < 9; i++) {
    state[i] = State[i];
  }
  coder::constacc(state, b_time - Time);
}

//
// Arguments    : void
// Return Type  : CombinedTracker *
//
CombinedTracker *CombinedTracker::init()
{
  static const signed char b_iv[9]{5, 0, 0, 0, 5, 0, 0, 0, 5};
  static const signed char b_iv1[9]{0, 0, 0, 0, 0, 0, 0, 0, 1};
  CombinedTracker *obj;
  coder::trackingKF *fcnOutput;
  obj = this;
  obj->Time = 0.0F;
  for (int i{0}; i < 9; i++) {
    obj->State[i] = 0.0F;
  }
  for (int i{0}; i < 27; i++) {
    obj->GPSModel[i] = iv[i];
  }
  for (int i{0}; i < 9; i++) {
    obj->GPSNoise[i] = b_iv[i];
  }
  for (int i{0}; i < 9; i++) {
    obj->AccelModel[i] = b_iv1[i];
  }
  obj->AccelNoise = 5.0F;
  fcnOutput = obj->coder_buffer_pobj0.init(obj->State);
  obj->Filter = fcnOutput;
  return obj;
}

//
// Arguments    : const float ProcessNoise[9]
//                const float b_GPSNoise[9]
//                float b_AccelNoise
// Return Type  : void
//
void CombinedTracker::setNoises(const float ProcessNoise[9],
                                const float b_GPSNoise[9], float b_AccelNoise)
{
  Filter->set_ProcessNoise(ProcessNoise);
  for (int i{0}; i < 9; i++) {
    GPSNoise[i] = b_GPSNoise[i];
  }
  AccelNoise = b_AccelNoise;
}

//
// File trailer for CombinedTracker.cpp
//
// [EOF]
//
