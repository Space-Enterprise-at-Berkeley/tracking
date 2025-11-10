//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xtrsm.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xtrsm.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : int n
//                const double A_data[]
//                int lda
//                double B_data[]
//                const int B_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void b_xtrsm(int n, const double A_data[], int lda, double B_data[],
             const int B_size[2])
{
  if ((n != 0) && (B_size[1] != 0)) {
    for (int j{n}; j >= 1; j--) {
      int i;
      int jAcol;
      int jBcol;
      jBcol = 9 * (j - 1) - 1;
      jAcol = lda * (j - 1) - 1;
      i = j + 1;
      for (int k{i}; k <= n; k++) {
        double d;
        int kBcol;
        kBcol = 9 * (k - 1);
        d = A_data[k + jAcol];
        if (d != 0.0) {
          for (int b_i{0}; b_i < 9; b_i++) {
            int i1;
            i1 = (b_i + jBcol) + 1;
            B_data[i1] -= d * B_data[b_i + kBcol];
          }
        }
      }
    }
  }
}

//
// Arguments    : int n
//                const double A_data[]
//                int lda
//                double B_data[]
//                const int B_size[2]
// Return Type  : void
//
void xtrsm(int n, const double A_data[], int lda, double B_data[],
           const int B_size[2])
{
  if ((n != 0) && (B_size[1] != 0)) {
    int i;
    i = static_cast<unsigned char>(n);
    for (int j{0}; j < i; j++) {
      double temp;
      int jAcol;
      int jBcol;
      jBcol = 9 * j - 1;
      jAcol = lda * j;
      for (int k{0}; k < j; k++) {
        int kBcol;
        kBcol = 9 * k;
        temp = A_data[k + jAcol];
        if (temp != 0.0) {
          for (int b_i{0}; b_i < 9; b_i++) {
            int i1;
            i1 = (b_i + jBcol) + 1;
            B_data[i1] -= temp * B_data[b_i + kBcol];
          }
        }
      }
      temp = 1.0 / A_data[j + jAcol];
      for (int k{0}; k < 9; k++) {
        jAcol = (k + jBcol) + 1;
        B_data[jAcol] *= temp;
      }
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for xtrsm.cpp
//
// [EOF]
//
