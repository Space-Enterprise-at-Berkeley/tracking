//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: qrsolve.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "xunormqr.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const double A_data[]
//                const int A_size[2]
//                const double tau_data[]
//                const int jpvt_data[]
//                double B_data[]
//                const int B_size[2]
//                int rankA
//                double Y_data[]
//                int Y_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
void LSQFromQR(const double A_data[], const int A_size[2],
               const double tau_data[], const int jpvt_data[], double B_data[],
               const int B_size[2], int rankA, double Y_data[], int Y_size[2])
{
  int i;
  int loop_ub;
  Y_size[0] = A_size[1];
  Y_size[1] = 9;
  loop_ub = A_size[1] * 9;
  if (loop_ub - 1 >= 0) {
    std::memset(&Y_data[0], 0,
                static_cast<unsigned int>(loop_ub) * sizeof(double));
  }
  lapack::xunormqr(A_data, A_size, B_data, B_size, tau_data);
  i = static_cast<unsigned char>(rankA);
  for (int k{0}; k < 9; k++) {
    for (int b_i{0}; b_i < i; b_i++) {
      Y_data[(jpvt_data[b_i] + Y_size[0] * k) - 1] =
          B_data[b_i + B_size[0] * k];
    }
    for (int b_i{rankA}; b_i >= 1; b_i--) {
      int Y_data_tmp;
      int b_Y_data_tmp;
      int i1;
      loop_ub = Y_size[0] * k;
      Y_data_tmp = (jpvt_data[b_i - 1] + loop_ub) - 1;
      b_Y_data_tmp = A_size[0] * (b_i - 1);
      Y_data[Y_data_tmp] /= A_data[(b_i + b_Y_data_tmp) - 1];
      i1 = static_cast<unsigned char>(b_i - 1);
      for (int c_i{0}; c_i < i1; c_i++) {
        int c_Y_data_tmp;
        c_Y_data_tmp = (jpvt_data[c_i] + loop_ub) - 1;
        Y_data[c_Y_data_tmp] -= Y_data[Y_data_tmp] * A_data[c_i + b_Y_data_tmp];
      }
    }
  }
}

//
// Arguments    : const double A_data[]
//                const int A_size[2]
// Return Type  : int
//
int rankFromQR(const double A_data[], const int A_size[2])
{
  int maxmn;
  int minmn;
  int r;
  r = 0;
  if (A_size[0] < A_size[1]) {
    minmn = A_size[0];
    maxmn = A_size[1];
  } else {
    minmn = A_size[1];
    maxmn = A_size[0];
  }
  if (minmn > 0) {
    double tol;
    tol = 2.2204460492503131E-15 * static_cast<double>(maxmn) *
          std::abs(A_data[0]);
    while ((r < minmn) && (!(std::abs(A_data[r + A_size[0] * r]) <= tol))) {
      r++;
    }
  }
  return r;
}

} // namespace internal
} // namespace coder

//
// File trailer for qrsolve.cpp
//
// [EOF]
//
