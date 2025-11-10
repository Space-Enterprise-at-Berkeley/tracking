//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgetrf.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef XGETRF_H
#define XGETRF_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace lapack {
int xgetrf(int m, int n, double A_data[], const int A_size[2], int lda,
           int ipiv_data[], int ipiv_size[2]);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xgetrf.h
//
// [EOF]
//
