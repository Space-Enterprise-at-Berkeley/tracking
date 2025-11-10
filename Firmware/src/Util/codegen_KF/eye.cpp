//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eye.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "eye.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions
//
// Arguments    : const double varargin_1[2]
//                double I_data[]
//                int I_size[2]
// Return Type  : void
//
namespace coder {
void eye(const double varargin_1[2], double I_data[], int I_size[2])
{
  int d;
  int m;
  int n;
  if (varargin_1[0] < 0.0) {
    m = 0;
  } else {
    m = static_cast<int>(varargin_1[0]);
  }
  if (varargin_1[1] < 0.0) {
    n = 0;
  } else {
    n = static_cast<int>(varargin_1[1]);
  }
  if (m <= n) {
    d = m;
  } else {
    d = n;
  }
  I_size[0] = m;
  I_size[1] = n;
  n *= m;
  if (n - 1 >= 0) {
    std::memset(&I_data[0], 0, static_cast<unsigned int>(n) * sizeof(double));
  }
  if (d > 0) {
    n = static_cast<unsigned char>(d);
    for (int k{0}; k < n; k++) {
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
