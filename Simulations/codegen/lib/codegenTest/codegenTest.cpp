//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: codegenTest.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 22:04:03
//

// Include Files
#include "codegenTest.h"
#include "CombinedTracker.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const float testGPS[3]
//                float testGPStime
//                const float testAccel[3]
//                float testAcceltime
//                float testExtrapolate
//                const float testProcessNoise[9]
//                const float testGPSNoise[9]
//                const float testAccelNoise[9]
//                float state[9]
// Return Type  : void
//
void codegenTest(const float testGPS[3], float testGPStime,
                 const float testAccel[3], float testAcceltime,
                 float testExtrapolate, const float testProcessNoise[9],
                 const float testGPSNoise[9], const float testAccelNoise[9],
                 float state[9])
{
  CombinedTracker testTracker;
  testTracker.init();
  testTracker.setNoises(testProcessNoise, testGPSNoise, testAccelNoise);
  testTracker.GPSUpdate(testGPStime, testGPS);
  testTracker.accelUpdate(testAcceltime, testAccel);
  testTracker.extrapolate(testExtrapolate, state);
}

//
// File trailer for codegenTest.cpp
//
// [EOF]
//
