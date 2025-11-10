//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xunormqr.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xunormqr.h"
#include "rt_nonfinite.h"
#include "xzunormqr.h"

// Function Definitions
//
// Arguments    : const double Q_data[]
//                const int Q_size[2]
//                double C_data[]
//                const int C_size[2]
//                const double tau_data[]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace lapack {
void xunormqr(const double Q_data[], const int Q_size[2], double C_data[],
              const int C_size[2], const double tau_data[])
{
  int u0;
  int u1;
  u0 = Q_size[0];
  u1 = Q_size[1];
  if (u0 <= u1) {
    u1 = u0;
  }
  for (int j{0}; j < u1; j++) {
    reflapack::applyJthHouseHolder(Q_data, Q_size, C_data, C_size, tau_data[j],
                                   j + 1);
  }
}

} // namespace lapack
} // namespace internal
} // namespace coder

//
// File trailer for xunormqr.cpp
//
// [EOF]
//
