//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ixamax.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "ixamax.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : int n
//                const double x_data[]
//                int ix0
// Return Type  : int
//
namespace coder {
namespace internal {
namespace blas {
int ixamax(int n, const double x_data[], int ix0)
{
  int idxmax;
  if (n < 1) {
    idxmax = 0;
  } else {
    idxmax = 1;
    if (n > 1) {
      double smax;
      smax = std::abs(x_data[ix0 - 1]);
      for (int k{2}; k <= n; k++) {
        double s;
        s = std::abs(x_data[(ix0 + k) - 2]);
        if (s > smax) {
          idxmax = k;
          smax = s;
        }
      }
    }
  }
  return idxmax;
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for ixamax.cpp
//
// [EOF]
//
