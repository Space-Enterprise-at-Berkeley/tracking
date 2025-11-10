//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: kron.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "kron.h"
#include "codegenTest_data.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const double B[3]
//                double K[27]
// Return Type  : void
//
namespace coder {
void b_kron(const double B[3], double K[27])
{
  double d;
  double d1;
  double d2;
  int kidx;
  kidx = -1;
  d = B[0];
  d1 = B[1];
  d2 = B[2];
  for (int b_j1{0}; b_j1 < 3; b_j1++) {
    for (int i1{0}; i1 < 3; i1++) {
      int K_tmp;
      K_tmp = iv1[i1 + 3 * b_j1];
      K[kidx + 1] = static_cast<double>(K_tmp) * d;
      K[kidx + 2] = static_cast<double>(K_tmp) * d1;
      K[kidx + 3] = static_cast<double>(K_tmp) * d2;
      kidx += 3;
    }
  }
}

//
// Arguments    : const double B[9]
//                double K[81]
// Return Type  : void
//
void kron(const double B[9], double K[81])
{
  int kidx;
  kidx = -1;
  for (int b_j1{0}; b_j1 < 3; b_j1++) {
    for (int j2{0}; j2 < 3; j2++) {
      double d;
      double d1;
      double d2;
      d = B[3 * j2];
      d1 = B[3 * j2 + 1];
      d2 = B[3 * j2 + 2];
      for (int i1{0}; i1 < 3; i1++) {
        int K_tmp;
        K_tmp = iv1[i1 + 3 * b_j1];
        K[kidx + 1] = static_cast<double>(K_tmp) * d;
        K[kidx + 2] = static_cast<double>(K_tmp) * d1;
        K[kidx + 3] = static_cast<double>(K_tmp) * d2;
        kidx += 3;
      }
    }
  }
}

} // namespace coder

//
// File trailer for kron.cpp
//
// [EOF]
//
