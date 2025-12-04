//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: KalmanFilter.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 22:04:03
//

#ifndef KALMANFILTER_H
#define KALMANFILTER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class trackingKF;

}

// Function Declarations
void binary_expand_op(coder::trackingKF *in1, const float in2_data[],
                      const float in3[3], const float in4_data[],
                      const int in4_size[2]);

void binary_expand_op_1(float in1_data[], int in1_size[2],
                        const float in2_data[], const int in2_size[2],
                        const coder::trackingKF *in3, const float in4_data[],
                        const int in4_size[2]);

#endif
//
// File trailer for KalmanFilter.h
//
// [EOF]
//
