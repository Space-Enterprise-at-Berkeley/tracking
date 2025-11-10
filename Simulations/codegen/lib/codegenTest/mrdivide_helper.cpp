//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mrdivide_helper.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "mrdivide_helper.h"
#include "lusolve.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "trackingKF.h"
#include "xgeqp3.h"
#include <cstring>

// Function Definitions
//
// Arguments    : double in1_data[]
//                const coder::trackingKF *in2
//                const double in3_data[]
//                const int in3_size[2]
//                const double in4_data[]
//                const int in4_size[2]
//                const double in5_data[]
//                const int in5_size[2]
//                const double in6_data[]
//                const int in6_size[2]
//                int in1_size[2]
// Return Type  : void
//
void binary_expand_op_1(double in1_data[], const coder::trackingKF *in2,
                        const double in3_data[], const int in3_size[2],
                        const double in4_data[], const int in4_size[2],
                        const double in5_data[], const int in5_size[2],
                        const double in6_data[], const int in6_size[2],
                        int in1_size[2])
{
  double b_in4_data[27];
  double c_in4_data[9];
  double d_in4_data[9];
  double d;
  int b_in4_size[2];
  int in2_size[2];
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int in2_data_tmp;
  int in4_data_tmp;
  int in4_size_idx_0;
  int loop_ub;
  int stride_0_0;
  int stride_1_1;
  in4_size_idx_0 = in4_size[0];
  for (int i{0}; i < 9; i++) {
    for (int i1{0}; i1 < in4_size_idx_0; i1++) {
      b_in4_data[i1 + in4_size_idx_0 * i] = 0.0;
    }
    for (int i1{0}; i1 < 9; i1++) {
      d = in2->pStateCovariance[i1 + 9 * i];
      for (int i2{0}; i2 < in4_size_idx_0; i2++) {
        in4_data_tmp = i2 + in4_size_idx_0 * i;
        b_in4_data[in4_data_tmp] += in4_data[i2 + in4_size[0] * i1] * d;
      }
    }
  }
  stride_1_1 = in5_size[0];
  for (int i{0}; i < stride_1_1; i++) {
    for (int i1{0}; i1 < in4_size_idx_0; i1++) {
      c_in4_data[i1 + in4_size_idx_0 * i] = 0.0;
    }
    for (int i1{0}; i1 < 9; i1++) {
      d = in5_data[i + in5_size[0] * i1];
      for (int i2{0}; i2 < in4_size_idx_0; i2++) {
        in4_data_tmp = i2 + in4_size_idx_0 * i;
        c_in4_data[in4_data_tmp] += b_in4_data[i2 + in4_size_idx_0 * i1] * d;
      }
    }
  }
  in4_data_tmp = in3_size[0];
  in2_size[0] = 9;
  in2_size[1] = in4_data_tmp;
  for (int i1{0}; i1 < in4_data_tmp; i1++) {
    std::memset(&b_in4_data[i1 * 9], 0, 9U * sizeof(double));
    for (int i2{0}; i2 < 9; i2++) {
      d = in3_data[i1 + in3_size[0] * i2];
      for (int i{0}; i < 9; i++) {
        in2_data_tmp = i + 9 * i1;
        b_in4_data[in2_data_tmp] += in2->pStateCovariance[i + 9 * i2] * d;
      }
    }
  }
  if (in6_size[0] == 1) {
    loop_ub = in4_size_idx_0;
  } else {
    loop_ub = in6_size[0];
  }
  if (in6_size[1] == 1) {
    b_loop_ub = stride_1_1;
  } else {
    b_loop_ub = in6_size[1];
  }
  stride_0_0 = (in4_size_idx_0 != 1);
  in4_data_tmp = (stride_1_1 != 1);
  in2_data_tmp = (in6_size[0] != 1);
  stride_1_1 = (in6_size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i1{0}; i1 < b_loop_ub; i1++) {
    for (int i2{0}; i2 < loop_ub; i2++) {
      d_in4_data[i2 + loop_ub * i1] =
          c_in4_data[i2 * stride_0_0 + in4_size_idx_0 * aux_0_1] +
          in6_data[i2 * in2_data_tmp + in6_size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += in4_data_tmp;
  }
  b_in4_size[0] = loop_ub;
  b_in4_size[1] = b_loop_ub;
  for (int i1{0}; i1 < b_loop_ub; i1++) {
    for (int i2{0}; i2 < loop_ub; i2++) {
      in4_data_tmp = loop_ub * i1;
      c_in4_data[i2 + in4_data_tmp] = d_in4_data[i2 + in4_data_tmp];
    }
  }
  coder::internal::mrdiv(b_in4_data, in2_size, c_in4_data, b_in4_size, in1_data,
                         in1_size);
}

//
// Arguments    : const double A_data[]
//                const int A_size[2]
//                const double B_data[]
//                const int B_size[2]
//                double Y_data[]
//                int Y_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
void mrdiv(const double A_data[], const int A_size[2], const double B_data[],
           const int B_size[2], double Y_data[], int Y_size[2])
{
  double tmp_data[27];
  double tau_data[3];
  int jpvt_data[3];
  int b_A_size[2];
  if ((A_size[1] == 0) || ((B_size[0] == 0) || (B_size[1] == 0))) {
    int loop_ub;
    Y_size[0] = 9;
    Y_size[1] = B_size[0];
    loop_ub = 9 * B_size[0];
    if (loop_ub - 1 >= 0) {
      std::memset(&Y_data[0], 0,
                  static_cast<unsigned int>(loop_ub) * sizeof(double));
    }
  } else if (B_size[0] == B_size[1]) {
    lusolve(B_data, B_size, A_data, A_size, Y_data, Y_size);
  } else {
    double c_A_data[27];
    double b_A_data[9];
    int jpvt_size[2];
    int tmp_size[2];
    int b_loop_ub;
    int loop_ub;
    loop_ub = B_size[1];
    b_loop_ub = B_size[0];
    b_A_size[0] = B_size[1];
    b_A_size[1] = B_size[0];
    for (int i{0}; i < b_loop_ub; i++) {
      for (int i1{0}; i1 < loop_ub; i1++) {
        b_A_data[i1 + b_A_size[0] * i] = B_data[i + B_size[0] * i1];
      }
    }
    lapack::xgeqp3(b_A_data, b_A_size, tau_data, jpvt_data, jpvt_size);
    loop_ub = A_size[1];
    jpvt_size[0] = A_size[1];
    jpvt_size[1] = 9;
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < loop_ub; i1++) {
        c_A_data[i1 + jpvt_size[0] * i] = A_data[i + 9 * i1];
      }
    }
    LSQFromQR(b_A_data, b_A_size, tau_data, jpvt_data, c_A_data, jpvt_size,
              rankFromQR(b_A_data, b_A_size), tmp_data, tmp_size);
    loop_ub = tmp_size[0];
    Y_size[0] = 9;
    Y_size[1] = tmp_size[0];
    for (int i{0}; i < loop_ub; i++) {
      for (int i1{0}; i1 < 9; i1++) {
        Y_data[i1 + 9 * i] = tmp_data[i + tmp_size[0] * i1];
      }
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for mrdivide_helper.cpp
//
// [EOF]
//
