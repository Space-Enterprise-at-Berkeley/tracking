//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xtrsm.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef XTRSM_H
#define XTRSM_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void b_xtrsm(int n, const double A_data[], int lda, double B_data[],
             const int B_size[2]);

void xtrsm(int n, const double A_data[], int lda, double B_data[],
           const int B_size[2]);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xtrsm.h
//
// [EOF]
//
