//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: lusolve.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef LUSOLVE_H
#define LUSOLVE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void lusolve(const double A_data[], const int A_size[2], const double B_data[],
             const int B_size[2], double X_data[], int X_size[2]);

}
} // namespace coder

#endif
//
// File trailer for lusolve.h
//
// [EOF]
//
