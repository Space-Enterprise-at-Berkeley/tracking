//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzlarf.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xzlarf.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "xgerc.h"

// Function Declarations
namespace coder {
namespace internal {
namespace reflapack {
static int ilazlc(int m, int n, const double A_data[], int ia0, int lda);

}
} // namespace internal
} // namespace coder

// Function Definitions
//
// Arguments    : int m
//                int n
//                const double A_data[]
//                int ia0
//                int lda
// Return Type  : int
//
namespace coder {
namespace internal {
namespace reflapack {
static int ilazlc(int m, int n, const double A_data[], int ia0, int lda)
{
  int j;
  bool exitg2;
  j = n;
  exitg2 = false;
  while ((!exitg2) && (j > 0)) {
    int coltop;
    int exitg1;
    int ia;
    coltop = ia0 + (j - 1) * lda;
    ia = coltop;
    do {
      exitg1 = 0;
      if (ia <= (coltop + m) - 1) {
        if (A_data[ia - 1] != 0.0) {
          exitg1 = 1;
        } else {
          ia++;
        }
      } else {
        j--;
        exitg1 = 2;
      }
    } while (exitg1 == 0);
    if (exitg1 == 1) {
      exitg2 = true;
    }
  }
  return j;
}

//
// Arguments    : int m
//                int n
//                int iv0
//                double tau
//                double C_data[]
//                int ic0
//                int ldc
//                double work_data[]
// Return Type  : void
//
void xzlarf(int m, int n, int iv0, double tau, double C_data[], int ic0,
            int ldc, double work_data[])
{
  int i;
  int lastv;
  if (tau != 0.0) {
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && (C_data[i - 2] == 0.0)) {
      lastv--;
      i--;
    }
    i = ilazlc(lastv, n, C_data, ic0, ldc);
  } else {
    lastv = 0;
    i = 0;
  }
  if (lastv > 0) {
    blas::xgemv(lastv, i, C_data, ic0, ldc, C_data, iv0, work_data);
    blas::xgerc(lastv, i, -tau, iv0, work_data, C_data, ic0, ldc);
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzlarf.cpp
//
// [EOF]
//
