//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgeqp3.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xgeqp3.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include <cstring>

// Function Definitions
//
// Arguments    : double A_data[]
//                const int A_size[2]
//                double tau_data[]
//                int jpvt_data[]
//                int jpvt_size[2]
// Return Type  : int
//
namespace coder {
namespace internal {
namespace lapack {
int xgeqp3(double A_data[], const int A_size[2], double tau_data[],
           int jpvt_data[], int jpvt_size[2])
{
  int tau_size;
  int u0;
  bool guard1;
  u0 = A_size[0];
  tau_size = A_size[1];
  if (u0 <= tau_size) {
    tau_size = u0;
  }
  if (tau_size - 1 >= 0) {
    std::memset(&tau_data[0], 0,
                static_cast<unsigned int>(tau_size) * sizeof(double));
  }
  guard1 = false;
  if ((A_size[0] == 0) || (A_size[1] == 0)) {
    guard1 = true;
  } else {
    int u1;
    u1 = A_size[1];
    if (u0 <= u1) {
      u1 = u0;
    }
    if (u1 < 1) {
      guard1 = true;
    } else {
      u0 = A_size[1];
      jpvt_size[0] = 1;
      jpvt_size[1] = u0;
      for (int j{0}; j < u0; j++) {
        jpvt_data[j] = j + 1;
      }
      reflapack::qrpf(A_data, A_size, A_size[0], A_size[1], tau_data,
                      jpvt_data);
    }
  }
  if (guard1) {
    u0 = A_size[1];
    jpvt_size[0] = 1;
    jpvt_size[1] = u0;
    for (int j{0}; j < u0; j++) {
      jpvt_data[j] = j + 1;
    }
  }
  return tau_size;
}

} // namespace lapack
} // namespace internal
} // namespace coder

//
// File trailer for xgeqp3.cpp
//
// [EOF]
//
