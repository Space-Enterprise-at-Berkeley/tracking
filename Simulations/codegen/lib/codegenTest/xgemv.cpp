//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgemv.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xgemv.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions
//
// Arguments    : int m
//                int n
//                const double A_data[]
//                int ia0
//                int lda
//                const double x_data[]
//                int ix0
//                double y_data[]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void xgemv(int m, int n, const double A_data[], int ia0, int lda,
           const double x_data[], int ix0, double y_data[])
{
  if (n != 0) {
    int i;
    int iy;
    if (n - 1 >= 0) {
      std::memset(&y_data[0], 0, static_cast<unsigned int>(n) * sizeof(double));
    }
    iy = 0;
    i = ia0 + lda * (n - 1);
    for (int iac{ia0}; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      double c;
      int i1;
      c = 0.0;
      i1 = iac + m;
      for (int ia{iac}; ia < i1; ia++) {
        c += A_data[ia - 1] * x_data[((ix0 + ia) - iac) - 1];
      }
      y_data[iy] += c;
      iy++;
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for xgemv.cpp
//
// [EOF]
//
