//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgeru.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xgeru.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : int m
//                int n
//                int ix0
//                int iy0
//                int incy
//                double A_data[]
//                int ia0
//                int lda
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void xgeru(int m, int n, int ix0, int iy0, int incy, double A_data[], int ia0,
           int lda)
{
  int jA;
  jA = ia0;
  for (int j{0}; j < n; j++) {
    double yjy;
    yjy = A_data[(iy0 + j * incy) - 1];
    if (yjy != 0.0) {
      int i;
      i = m + jA;
      for (int ijA{jA}; ijA < i; ijA++) {
        A_data[ijA - 1] += A_data[((ix0 + ijA) - jA) - 1] * -yjy;
      }
    }
    jA += lda;
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for xgeru.cpp
//
// [EOF]
//
