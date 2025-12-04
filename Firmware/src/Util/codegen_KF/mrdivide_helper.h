//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mrdivide_helper.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 20:32:31
//

#ifndef MRDIVIDE_HELPER_H
#define MRDIVIDE_HELPER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class trackingKF;

}

// Function Declarations
void binary_expand_op_1(float in1_data[], int in1_size[2],
                        const float in2_data[], const int in2_size[2],
                        const coder::trackingKF *in3, const float in4_data[],
                        const int in4_size[2], const float in5_data[],
                        const int in5_size[2]);

namespace coder {
namespace internal {
void mrdiv(float A_data[], int A_size[2], const float B_data[],
           const int B_size[2]);

}
} // namespace coder

#endif
//
// File trailer for mrdivide_helper.h
//
// [EOF]
//
