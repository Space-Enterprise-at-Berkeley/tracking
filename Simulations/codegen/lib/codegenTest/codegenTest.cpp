//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: codegenTest.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "codegenTest.h"
#include "CombinedTracker.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// function state = codegenTest(testGPS, testGPStime, testAccel, testAcceltime,
// testExtrapolate)
//
// Arguments    : const double testGPS[3]
//                double testGPStime
//                const double testAccel[3]
//                double testAcceltime
//                double testExtrapolate
//                double state[9]
// Return Type  : void
//
void codegenTest(const double testGPS[3], double testGPStime,
                 const double testAccel[3], double testAcceltime,
                 double testExtrapolate, double state[9])
{
  CombinedTracker testTracker;
  // 'codegenTest:2' testTracker = CombinedTracker();
  testTracker.init();
  // 'codegenTest:3' GPSUpdate(testTracker, testGPStime, testGPS);
  testTracker.GPSUpdate(testGPStime, testGPS);
  // 'codegenTest:4' accelUpdate(testTracker, testAcceltime, testAccel);
  testTracker.accelUpdate(testAcceltime, testAccel);
  // 'codegenTest:5' state = extrapolate(testTracker, testExtrapolate);
  testTracker.extrapolate(testExtrapolate, state);
}

//
// File trailer for codegenTest.cpp
//
// [EOF]
//
