//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: lusolve.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "lusolve.h"
#include "rt_nonfinite.h"
#include "xgetrf.h"
#include "xtrsm.h"
#include <algorithm>

// Function Definitions
//
// Arguments    : const double A_data[]
//                const int A_size[2]
//                const double B_data[]
//                const int B_size[2]
//                double X_data[]
//                int X_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
void lusolve(const double A_data[], const int A_size[2], const double B_data[],
             const int B_size[2], double X_data[], int X_size[2])
{
  double b_A_data[9];
  int ipiv_data[3];
  int ipiv_size[2];
  int loop_ub;
  loop_ub = A_size[0] * A_size[1];
  if (loop_ub - 1 >= 0) {
    std::copy(&A_data[0], &A_data[loop_ub], &b_A_data[0]);
  }
  lapack::xgetrf(A_size[1], A_size[1], b_A_data, A_size, A_size[1], ipiv_data,
                 ipiv_size);
  X_size[0] = 9;
  X_size[1] = B_size[1];
  loop_ub = 9 * B_size[1];
  if (loop_ub - 1 >= 0) {
    std::copy(&B_data[0], &B_data[loop_ub], &X_data[0]);
  }
  blas::xtrsm(A_size[1], b_A_data, A_size[1], X_data, X_size);
  blas::b_xtrsm(A_size[1], b_A_data, A_size[1], X_data, X_size);
  loop_ub = A_size[1] - 1;
  for (int j{loop_ub}; j >= 1; j--) {
    int i;
    i = ipiv_data[j - 1];
    if (i != j) {
      for (int b_i{0}; b_i < 9; b_i++) {
        double temp;
        int X_data_tmp;
        int temp_tmp;
        temp_tmp = b_i + 9 * (j - 1);
        temp = X_data[temp_tmp];
        X_data_tmp = b_i + 9 * (i - 1);
        X_data[temp_tmp] = X_data[X_data_tmp];
        X_data[X_data_tmp] = temp;
      }
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for lusolve.cpp
//
// [EOF]
//
