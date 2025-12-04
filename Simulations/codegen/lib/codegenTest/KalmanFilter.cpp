//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: KalmanFilter.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 22:04:03
//

// Include Files
#include "KalmanFilter.h"
#include "rt_nonfinite.h"
#include "trackingKF.h"
#include <cstring>

// Function Definitions
//
// Arguments    : coder::trackingKF *in1
//                const float in2_data[]
//                const float in3[3]
//                const float in4_data[]
//                const int in4_size[2]
// Return Type  : void
//
void binary_expand_op(coder::trackingKF *in1, const float in2_data[],
                      const float in3[3], const float in4_data[],
                      const int in4_size[2])
{
  float b_in4_data[3];
  float in3_idx_0;
  float in3_idx_1;
  float in3_idx_2;
  int b_in4_size;
  b_in4_size = in4_size[0];
  if (b_in4_size - 1 >= 0) {
    std::memset(&b_in4_data[0], 0,
                static_cast<unsigned int>(b_in4_size) * sizeof(float));
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
// Arguments    : float in1_data[]
//                int in1_size[2]
//                const float in2_data[]
//                const int in2_size[2]
//                const coder::trackingKF *in3
//                const float in4_data[]
//                const int in4_size[2]
// Return Type  : void
//
void binary_expand_op_1(float in1_data[], int in1_size[2],
                        const float in2_data[], const int in2_size[2],
                        const coder::trackingKF *in3, const float in4_data[],
                        const int in4_size[2])
{
  float b_in2_data[27];
  float c_in2_data[9];
  float d_in2_data[9];
  float f;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int in2_data_tmp;
  int in2_size_idx_0;
  int in2_size_idx_1;
  int loop_ub;
  int stride_0_0;
  int stride_1_1;
  in2_size_idx_0 = in2_size[0];
  for (int i{0}; i < 9; i++) {
    for (int i1{0}; i1 < in2_size_idx_0; i1++) {
      b_in2_data[i1 + in2_size_idx_0 * i] = 0.0F;
    }
    for (int i1{0}; i1 < 9; i1++) {
      f = in3->pStateCovariance[i1 + 9 * i];
      for (int i2{0}; i2 < in2_size_idx_0; i2++) {
        in2_data_tmp = i2 + in2_size_idx_0 * i;
        b_in2_data[in2_data_tmp] += in2_data[i2 + in2_size[0] * i1] * f;
      }
    }
  }
  in2_size_idx_1 = in4_size[0];
  for (int i{0}; i < in2_size_idx_1; i++) {
    for (int i1{0}; i1 < in2_size_idx_0; i1++) {
      c_in2_data[i1 + in2_size_idx_0 * i] = 0.0F;
    }
    for (int i1{0}; i1 < 9; i1++) {
      f = in4_data[i + in4_size[0] * i1];
      for (int i2{0}; i2 < in2_size_idx_0; i2++) {
        in2_data_tmp = i2 + in2_size_idx_0 * i;
        c_in2_data[in2_data_tmp] += b_in2_data[i2 + in2_size_idx_0 * i1] * f;
      }
    }
  }
  if (in1_size[0] == 1) {
    loop_ub = in2_size_idx_0;
  } else {
    loop_ub = in1_size[0];
  }
  if (in1_size[1] == 1) {
    b_loop_ub = in2_size_idx_1;
  } else {
    b_loop_ub = in1_size[1];
  }
  stride_0_0 = (in2_size_idx_0 != 1);
  in2_data_tmp = (in2_size_idx_1 != 1);
  in2_size_idx_1 = (in1_size[0] != 1);
  stride_1_1 = (in1_size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i1{0}; i1 < b_loop_ub; i1++) {
    for (int i2{0}; i2 < loop_ub; i2++) {
      d_in2_data[i2 + loop_ub * i1] =
          c_in2_data[i2 * stride_0_0 + in2_size_idx_0 * aux_0_1] +
          in1_data[i2 * in2_size_idx_1 + in1_size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += in2_data_tmp;
  }
  in1_size[0] = loop_ub;
  in1_size[1] = b_loop_ub;
  for (int i1{0}; i1 < b_loop_ub; i1++) {
    for (int i2{0}; i2 < loop_ub; i2++) {
      in2_data_tmp = loop_ub * i1;
      in1_data[i2 + in2_data_tmp] = d_in2_data[i2 + in2_data_tmp];
    }
  }
}

//
// File trailer for KalmanFilter.cpp
//
// [EOF]
//
