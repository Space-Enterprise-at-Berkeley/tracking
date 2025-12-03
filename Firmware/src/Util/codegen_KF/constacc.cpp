//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constacc.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 02-Dec-2025 17:03:31
//

// Include Files
#include "constacc.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : float state[9]
//                float varargin_1
// Return Type  : void
//
namespace coder {
void constacc(float state[9], float varargin_1)
{
  if (varargin_1 < 0.0F) {
    float f;
    float f1;
    float f2;
    f = state[1];
    f1 = state[2];
    f2 = varargin_1 * varargin_1 / 2.0F;
    state[0] = (state[0] + f * varargin_1) + f1 * f2;
    f += f1 * varargin_1;
    state[1] = f;
    f = state[4];
    f1 = state[5];
    state[3] = (state[3] + f * varargin_1) + f1 * f2;
    f += f1 * varargin_1;
    state[4] = f;
    f = state[7];
    f1 = state[8];
    state[6] = (state[6] + f * varargin_1) + f1 * f2;
    f += f1 * varargin_1;
    state[7] = f;
  } else {
    float f;
    float f1;
    float f2;
    float f3;
    float f4;
    f = state[1];
    f1 = state[2];
    f2 = varargin_1 * varargin_1 / 2.0F;
    f3 = 0.0F * f2;
    state[0] = ((state[0] + f * varargin_1) + f1 * f2) + f3;
    f4 = 0.0F * varargin_1;
    f = (f + f1 * varargin_1) + f4;
    state[1] = f;
    f = state[4];
    f1 = state[5];
    state[3] = ((state[3] + f * varargin_1) + f1 * f2) + f3;
    f = (f + f1 * varargin_1) + f4;
    state[4] = f;
    f = state[7];
    f1 = state[8];
    state[6] = ((state[6] + f * varargin_1) + f1 * f2) + f3;
    f = (f + f1 * varargin_1) + f4;
    state[7] = f;
  }
}

} // namespace coder

//
// File trailer for constacc.cpp
//
// [EOF]
//
