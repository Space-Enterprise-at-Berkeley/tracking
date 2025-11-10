//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgetrf.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xgetrf.h"
#include "colon.h"
#include "ixamax.h"
#include "rt_nonfinite.h"
#include "xgeru.h"
#include "xswap.h"

// Function Definitions
//
// Arguments    : int m
//                int n
//                double A_data[]
//                const int A_size[2]
//                int lda
//                int ipiv_data[]
//                int ipiv_size[2]
// Return Type  : int
//
namespace coder {
namespace internal {
namespace lapack {
int xgetrf(int m, int n, double A_data[], const int A_size[2], int lda,
           int ipiv_data[], int ipiv_size[2])
{
  int info;
  int y;
  if (m <= n) {
    y = m;
  } else {
    y = n;
  }
  eml_integer_colon_dispatcher(y, ipiv_data, ipiv_size);
  info = 0;
  if ((m >= 1) && (n >= 1)) {
    int i;
    y = m - 1;
    if (y > n) {
      y = n;
    }
    i = static_cast<unsigned char>(y);
    for (int j{0}; j < i; j++) {
      int b_tmp;
      int jp1j;
      int jpiv_offset;
      int mmj;
      mmj = m - j;
      b_tmp = j * (lda + 1);
      jp1j = b_tmp + 2;
      y = blas::ixamax(mmj, A_data, b_tmp + 1);
      jpiv_offset = blas::ixamax(mmj, A_data, b_tmp + 1) - 1;
      if (A_data[b_tmp + jpiv_offset] != 0.0) {
        if (y - 1 != 0) {
          ipiv_data[j] = j + y;
          blas::xswap(n, A_data, j + 1, lda, (j + jpiv_offset) + 1, lda);
        }
        y = b_tmp + mmj;
        for (int b_i{jp1j}; b_i <= y; b_i++) {
          A_data[b_i - 1] /= A_data[b_tmp];
        }
      } else {
        info = j + 1;
      }
      y = b_tmp + lda;
      blas::xgeru(mmj - 1, (n - j) - 1, b_tmp + 2, y + 1, lda, A_data, y + 2,
                  lda);
    }
    if ((info == 0) && (m <= n) &&
        (!(A_data[(m + A_size[0] * (m - 1)) - 1] != 0.0))) {
      info = m;
    }
  }
  return info;
}

} // namespace lapack
} // namespace internal
} // namespace coder

//
// File trailer for xgetrf.cpp
//
// [EOF]
//
