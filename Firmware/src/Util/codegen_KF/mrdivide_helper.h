//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mrdivide_helper.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
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
void binary_expand_op_1(double in1_data[], const coder::trackingKF *in2,
                        const double in3_data[], const int in3_size[2],
                        const double in4_data[], const int in4_size[2],
                        const double in5_data[], const int in5_size[2],
                        const double in6_data[], const int in6_size[2],
                        int in1_size[2]);

namespace coder {
namespace internal {
void mrdiv(const double A_data[], const int A_size[2], const double B_data[],
           const int B_size[2], double Y_data[], int Y_size[2]);

}
} // namespace coder

#endif
//
// File trailer for mrdivide_helper.h
//
// [EOF]
//
