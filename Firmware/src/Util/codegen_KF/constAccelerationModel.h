//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constAccelerationModel.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef CONSTACCELERATIONMODEL_H
#define CONSTACCELERATIONMODEL_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace matlabshared {
namespace tracking {
namespace internal {
namespace fusion {
void constAccelerationModel(double dt, double A[81], double Q[81],
                            double G[27]);

}
} // namespace internal
} // namespace tracking
} // namespace matlabshared
} // namespace coder

#endif
//
// File trailer for constAccelerationModel.h
//
// [EOF]
//
