//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: qrsolve.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef QRSOLVE_H
#define QRSOLVE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void LSQFromQR(const double A_data[], const int A_size[2],
               const double tau_data[], const int jpvt_data[], double B_data[],
               const int B_size[2], int rankA, double Y_data[], int Y_size[2]);

int rankFromQR(const double A_data[], const int A_size[2]);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for qrsolve.h
//
// [EOF]
//
