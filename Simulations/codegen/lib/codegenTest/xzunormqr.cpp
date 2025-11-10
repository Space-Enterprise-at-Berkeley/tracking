//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzunormqr.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xzunormqr.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const double A_data[]
//                const int A_size[2]
//                double B_data[]
//                const int B_size[2]
//                double tau
//                int j
// Return Type  : void
//
namespace coder {
namespace internal {
namespace reflapack {
void applyJthHouseHolder(const double A_data[], const int A_size[2],
                         double B_data[], const int B_size[2], double tau,
                         int j)
{
  int m;
  m = A_size[0];
  if (tau != 0.0) {
    int i;
    i = j + 1;
    for (int k{0}; k < 9; k++) {
      double wj;
      double wj_tmp;
      int b_wj_tmp_tmp;
      int wj_tmp_tmp;
      wj_tmp_tmp = B_size[0] * k;
      b_wj_tmp_tmp = (j + wj_tmp_tmp) - 1;
      wj_tmp = B_data[b_wj_tmp_tmp];
      wj = wj_tmp;
      for (int b_i{i}; b_i <= m; b_i++) {
        wj += A_data[(b_i + A_size[0] * (j - 1)) - 1] *
              B_data[(b_i + wj_tmp_tmp) - 1];
      }
      wj *= tau;
      if (wj != 0.0) {
        B_data[b_wj_tmp_tmp] = wj_tmp - wj;
        b_wj_tmp_tmp = j + 1;
        for (int b_i{b_wj_tmp_tmp}; b_i <= m; b_i++) {
          int i1;
          i1 = (b_i + wj_tmp_tmp) - 1;
          B_data[i1] -= A_data[(b_i + A_size[0] * (j - 1)) - 1] * wj;
        }
      }
    }
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzunormqr.cpp
//
// [EOF]
//
