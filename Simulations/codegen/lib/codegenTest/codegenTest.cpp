//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: codegenTest.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 20:32:31
//

// Include Files
#include "codegenTest.h"
#include "CombinedTracker.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const float testGPS[3]
//                float testGPStime
//                float testAccel
//                float testAcceltime
//                float testExtrapolate
//                const float testProcessNoise[9]
//                const float testGPSNoise[9]
//                float testAccelNoise
//                float state[9]
// Return Type  : void
//
void codegenTest(const float testGPS[3], float testGPStime, float testAccel,
                 float testAcceltime, float testExtrapolate,
                 const float testProcessNoise[9], const float testGPSNoise[9],
                 float testAccelNoise, float state[9])
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
