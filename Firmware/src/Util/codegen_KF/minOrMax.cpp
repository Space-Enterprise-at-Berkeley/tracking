//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: minOrMax.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 20:32:31
//

// Include Files
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const float x[3]
// Return Type  : float
//
namespace coder {
namespace internal {
float maximum(const float x[3])
{
  float ex;
  int idx;
  if (!std::isnan(x[0])) {
    idx = 1;
  } else {
    int k;
    bool exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 4)) {
      if (!std::isnan(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    ex = x[0];
  } else {
    ex = x[idx - 1];
    idx++;
    for (int b_k{idx}; b_k < 4; b_k++) {
      float f;
      f = x[b_k - 1];
      if (ex < f) {
        ex = f;
      }
    }
  }
  return ex;
}

} // namespace internal
} // namespace coder

//
// File trailer for minOrMax.cpp
//
// [EOF]
//
