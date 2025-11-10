//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzlarfg.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xzlarfg.h"
#include "rt_nonfinite.h"
#include "xdlapy2.h"
#include "xnrm2.h"
#include <cmath>

// Function Definitions
//
// Arguments    : int n
//                double &alpha1
//                double x_data[]
//                int ix0
// Return Type  : double
//
namespace coder {
namespace internal {
namespace reflapack {
double xzlarfg(int n, double &alpha1, double x_data[], int ix0)
{
  double tau;
  tau = 0.0;
  if (n > 0) {
    double xnorm;
    xnorm = blas::xnrm2(n - 1, x_data, ix0);
    if (xnorm != 0.0) {
      double beta1;
      beta1 = xdlapy2(alpha1, xnorm);
      if (alpha1 >= 0.0) {
        beta1 = -beta1;
      }
      if (std::abs(beta1) < 1.0020841800044864E-292) {
        int i;
        int knt;
        knt = 0;
        i = (ix0 + n) - 2;
        do {
          knt++;
          for (int k{ix0}; k <= i; k++) {
            x_data[k - 1] *= 9.9792015476736E+291;
          }
          beta1 *= 9.9792015476736E+291;
          alpha1 *= 9.9792015476736E+291;
        } while ((std::abs(beta1) < 1.0020841800044864E-292) && (knt < 20));
        beta1 = xdlapy2(alpha1, blas::xnrm2(n - 1, x_data, ix0));
        if (alpha1 >= 0.0) {
          beta1 = -beta1;
        }
        tau = (beta1 - alpha1) / beta1;
        xnorm = 1.0 / (alpha1 - beta1);
        for (int k{ix0}; k <= i; k++) {
          x_data[k - 1] *= xnorm;
        }
        for (int k{0}; k < knt; k++) {
          beta1 *= 1.0020841800044864E-292;
        }
        alpha1 = beta1;
      } else {
        int i;
        tau = (beta1 - alpha1) / beta1;
        xnorm = 1.0 / (alpha1 - beta1);
        i = (ix0 + n) - 2;
        for (int k{ix0}; k <= i; k++) {
          x_data[k - 1] *= xnorm;
        }
        alpha1 = beta1;
      }
    }
  }
  return tau;
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzlarfg.cpp
//
// [EOF]
//
