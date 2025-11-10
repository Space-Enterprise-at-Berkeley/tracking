//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzunormqr.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef XZUNORMQR_H
#define XZUNORMQR_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace reflapack {
void applyJthHouseHolder(const double A_data[], const int A_size[2],
                         double B_data[], const int B_size[2], double tau,
                         int j);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xzunormqr.h
//
// [EOF]
//
