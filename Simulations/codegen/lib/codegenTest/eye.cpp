//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eye.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 20:32:31
//

// Include Files
#include "eye.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions
//
// Arguments    : const float varargin_1[2]
//                double I_data[]
//                int I_size[2]
// Return Type  : void
//
namespace coder {
void eye(const float varargin_1[2], double I_data[], int I_size[2])
{
  float t;
  int d;
  int loop_ub;
  int m;
  if (varargin_1[0] < 0.0F) {
    m = 0;
  } else {
    m = static_cast<int>(varargin_1[0]);
  }
  if (varargin_1[1] < 0.0F) {
    t = 0.0F;
  } else {
    t = varargin_1[1];
  }
  d = static_cast<int>(t);
  if (m <= d) {
    d = m;
  }
  I_size[0] = m;
  I_size[1] = static_cast<int>(t);
  loop_ub = m * static_cast<int>(t);
  if (loop_ub - 1 >= 0) {
    std::memset(&I_data[0], 0,
                static_cast<unsigned int>(loop_ub) * sizeof(double));
  }
  if (d > 0) {
    d = static_cast<unsigned char>(d);
    for (int k{0}; k < d; k++) {
      I_data[k + m * k] = 1.0;
    }
  }
}

} // namespace coder

//
// File trailer for eye.cpp
//
// [EOF]
//
