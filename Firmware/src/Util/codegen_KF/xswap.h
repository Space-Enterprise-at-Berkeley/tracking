//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xswap.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef XSWAP_H
#define XSWAP_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void xswap(int n, double x_data[], int ix0, int iy0);

void xswap(int n, double x_data[], int ix0, int incx, int iy0, int incy);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xswap.h
//
// [EOF]
//
