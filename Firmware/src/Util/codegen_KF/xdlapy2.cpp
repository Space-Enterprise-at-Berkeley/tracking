//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xdlapy2.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xdlapy2.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double x1
//                double x2
// Return Type  : double
//
namespace coder {
namespace internal {
double xdlapy2(double x1, double x2)
{
  double b;
  double y;
  y = std::abs(x1);
  b = std::abs(x2);
  if (y < b) {
    y /= b;
    y = b * std::sqrt(y * y + 1.0);
  } else if (y > b) {
    b /= y;
    y *= std::sqrt(b * b + 1.0);
  } else if (std::isnan(b)) {
    y = rtNaN;
  } else {
    y *= 1.4142135623730951;
  }
  return y;
}

} // namespace internal
} // namespace coder

//
// File trailer for xdlapy2.cpp
//
// [EOF]
//
