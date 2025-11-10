//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constAccelerationModel.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "constAccelerationModel.h"
#include "kron.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else {
    double d;
    y = std::abs(u0);
    d = std::abs(u1);
    if (std::isinf(u1)) {
      if (y == 1.0) {
        y = 1.0;
      } else if (y > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d == 0.0) {
      y = 1.0;
    } else if (d == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }
  return y;
}

//
// Arguments    : double dt
//                double A[81]
//                double Q[81]
//                double G[27]
// Return Type  : void
//
namespace coder {
namespace matlabshared {
namespace tracking {
namespace internal {
namespace fusion {
void constAccelerationModel(double dt, double A[81], double Q[81], double G[27])
{
  double dv[9];
  double b_dt[3];
  double d;
  double d1;
  double d2;
  dv[0] = 1.0;
  dv[3] = dt;
  d = dt * dt;
  d1 = d / 2.0;
  dv[6] = d1;
  dv[1] = 0.0;
  dv[4] = 1.0;
  dv[7] = dt;
  dv[2] = 0.0;
  dv[5] = 0.0;
  dv[8] = 1.0;
  kron(dv, A);
  dv[0] = rt_powd_snf(dt, 4.0) / 4.0;
  d2 = rt_powd_snf(dt, 3.0) / 2.0;
  dv[3] = d2;
  dv[6] = d1;
  dv[1] = d2;
  dv[4] = d;
  dv[7] = dt;
  dv[2] = d1;
  dv[5] = dt;
  dv[8] = 1.0;
  kron(dv, Q);
  b_dt[0] = d1;
  b_dt[1] = dt;
  b_dt[2] = 1.0;
  b_kron(b_dt, G);
}

} // namespace fusion
} // namespace internal
} // namespace tracking
} // namespace matlabshared
} // namespace coder

//
// File trailer for constAccelerationModel.cpp
//
// [EOF]
//
