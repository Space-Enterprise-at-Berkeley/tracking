//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: KalmanFilter.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "KalmanFilter.h"
#include "rt_nonfinite.h"
#include "trackingKF.h"
#include <cstring>

// Function Definitions
//
// Arguments    : coder::trackingKF *in1
//                const double in2_data[]
//                const double in3[3]
//                const double in4_data[]
//                const int in4_size[2]
// Return Type  : void
//
void binary_expand_op(coder::trackingKF *in1, const double in2_data[],
                      const double in3[3], const double in4_data[],
                      const int in4_size[2])
{
  double b_in4_data[3];
  double in3_idx_0;
  double in3_idx_1;
  double in3_idx_2;
  int b_in4_size;
  b_in4_size = in4_size[0];
  if (b_in4_size - 1 >= 0) {
    std::memset(&b_in4_data[0], 0,
                static_cast<unsigned int>(b_in4_size) * sizeof(double));
  }
  for (int i{0}; i < 9; i++) {
    in3_idx_0 = in1->pState[i];
    for (int i1{0}; i1 < b_in4_size; i1++) {
      b_in4_data[i1] += in4_data[i1 + in4_size[0] * i] * in3_idx_0;
    }
  }
  b_in4_size = (b_in4_size != 1);
  in3_idx_0 = in3[0] - b_in4_data[0];
  in3_idx_1 = in3[1] - b_in4_data[b_in4_size];
  in3_idx_2 = in3[2] - b_in4_data[b_in4_size << 1];
  for (int i{0}; i < 9; i++) {
    in1->pState[i] += (in2_data[i] * in3_idx_0 + in2_data[i + 9] * in3_idx_1) +
                      in2_data[i + 18] * in3_idx_2;
  }
}

//
// File trailer for KalmanFilter.cpp
//
// [EOF]
//
