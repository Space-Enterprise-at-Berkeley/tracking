//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xunormqr.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef XUNORMQR_H
#define XUNORMQR_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace lapack {
void xunormqr(const double Q_data[], const int Q_size[2], double C_data[],
              const int C_size[2], const double tau_data[]);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xunormqr.h
//
// [EOF]
//
