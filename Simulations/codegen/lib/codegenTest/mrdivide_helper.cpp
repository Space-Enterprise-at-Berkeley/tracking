//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mrdivide_helper.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 20:32:31
//

// Include Files
#include "mrdivide_helper.h"
#include "rt_nonfinite.h"
#include "trackingKF.h"
#include "xgeqp3.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : float in1_data[]
//                int in1_size[2]
//                const float in2_data[]
//                const int in2_size[2]
//                const coder::trackingKF *in3
//                const float in4_data[]
//                const int in4_size[2]
//                const float in5_data[]
//                const int in5_size[2]
// Return Type  : void
//
void binary_expand_op_1(float in1_data[], int in1_size[2],
                        const float in2_data[], const int in2_size[2],
                        const coder::trackingKF *in3, const float in4_data[],
                        const int in4_size[2], const float in5_data[],
                        const int in5_size[2])
{
  float b_in2_data[27];
  float c_in2_data[9];
  float d_in2_data[9];
  float f;
  int b_in2_size[2];
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int in2_data_tmp;
  int in2_size_idx_0;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
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
  stride_1_0 = in4_size[0];
  for (int i{0}; i < stride_1_0; i++) {
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
  if (in5_size[0] == 1) {
    loop_ub = in2_size_idx_0;
  } else {
    loop_ub = in5_size[0];
  }
  if (in5_size[1] == 1) {
    b_loop_ub = stride_1_0;
  } else {
    b_loop_ub = in5_size[1];
  }
  stride_0_0 = (in2_size_idx_0 != 1);
  in2_data_tmp = (stride_1_0 != 1);
  stride_1_0 = (in5_size[0] != 1);
  stride_1_1 = (in5_size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i1{0}; i1 < b_loop_ub; i1++) {
    for (int i2{0}; i2 < loop_ub; i2++) {
      d_in2_data[i2 + loop_ub * i1] =
          c_in2_data[i2 * stride_0_0 + in2_size_idx_0 * aux_0_1] +
          in5_data[i2 * stride_1_0 + in5_size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += in2_data_tmp;
  }
  b_in2_size[0] = loop_ub;
  b_in2_size[1] = b_loop_ub;
  for (int i1{0}; i1 < b_loop_ub; i1++) {
    for (int i2{0}; i2 < loop_ub; i2++) {
      in2_data_tmp = loop_ub * i1;
      c_in2_data[i2 + in2_data_tmp] = d_in2_data[i2 + in2_data_tmp];
    }
  }
  coder::internal::mrdiv(in1_data, in1_size, c_in2_data, b_in2_size);
}

//
// Arguments    : float A_data[]
//                int A_size[2]
//                const float B_data[]
//                const int B_size[2]
// Return Type  : void
//
namespace coder {
namespace internal {
void mrdiv(float A_data[], int A_size[2], const float B_data[],
           const int B_size[2])
{
  float Y_data[27];
  float b_A_data[9];
  float tau_data[3];
  int jpvt_data[3];
  if ((A_size[1] == 0) || ((B_size[0] == 0) || (B_size[1] == 0))) {
    int yk;
    A_size[0] = 9;
    yk = B_size[0];
    A_size[1] = B_size[0];
    for (int k{0}; k < yk; k++) {
      for (int ijA{0}; ijA < 9; ijA++) {
        A_data[ijA + 9 * k] = 0.0F;
      }
    }
  } else if (B_size[0] == B_size[1]) {
    float temp;
    int i;
    int jA;
    int jAcol;
    int jp1j;
    int n;
    int u1;
    int yk;
    n = B_size[1];
    yk = B_size[0] * B_size[1];
    std::copy(&B_data[0], &B_data[yk], &b_A_data[0]);
    jpvt_data[0] = 1;
    yk = 1;
    for (int k{2}; k <= n; k++) {
      yk++;
      jpvt_data[k - 1] = yk;
    }
    if (B_size[1] - 1 <= B_size[1]) {
      u1 = B_size[1];
    } else {
      u1 = 2;
    }
    for (int j{0}; j <= u1 - 2; j++) {
      int mmj;
      int rankA;
      mmj = n - j;
      rankA = j * (n + 1);
      jp1j = rankA + 2;
      if (mmj - 1 < 0) {
        yk = -1;
      } else {
        yk = 0;
        if (mmj - 1 > 0) {
          temp = std::abs(b_A_data[rankA]);
          for (int k{2}; k <= mmj; k++) {
            float s;
            s = std::abs(b_A_data[(rankA + k) - 1]);
            if (s > temp) {
              yk = k - 1;
              temp = s;
            }
          }
        }
      }
      if (b_A_data[rankA + yk] != 0.0F) {
        if (yk != 0) {
          jA = j + yk;
          jpvt_data[j] = jA + 1;
          for (int k{0}; k < n; k++) {
            yk = k * n;
            jAcol = j + yk;
            temp = b_A_data[jAcol];
            yk += jA;
            b_A_data[jAcol] = b_A_data[yk];
            b_A_data[yk] = temp;
          }
        }
        yk = rankA + mmj;
        for (int k{jp1j}; k <= yk; k++) {
          b_A_data[k - 1] /= b_A_data[rankA];
        }
      }
      yk = rankA + n;
      jA = yk;
      for (int k{0}; k <= mmj - 2; k++) {
        temp = b_A_data[yk + k * n];
        if (temp != 0.0F) {
          jAcol = jA + 2;
          i = mmj + jA;
          for (int ijA{jAcol}; ijA <= i; ijA++) {
            b_A_data[ijA - 1] += b_A_data[((rankA + ijA) - jA) - 1] * -temp;
          }
        }
        jA += n;
      }
    }
    if (A_size[1] != 0) {
      for (int j{0}; j < n; j++) {
        jp1j = 9 * j - 1;
        yk = n * j;
        for (int k{0}; k < j; k++) {
          jA = 9 * k;
          temp = b_A_data[k + yk];
          if (temp != 0.0F) {
            for (int ijA{0}; ijA < 9; ijA++) {
              jAcol = (ijA + jp1j) + 1;
              A_data[jAcol] -= temp * A_data[ijA + jA];
            }
          }
        }
        temp = 1.0F / b_A_data[j + yk];
        for (int ijA{0}; ijA < 9; ijA++) {
          yk = (ijA + jp1j) + 1;
          A_data[yk] *= temp;
        }
      }
    }
    if (A_size[1] != 0) {
      for (int k{n}; k >= 1; k--) {
        yk = 9 * (k - 1) - 1;
        jAcol = n * (k - 1) - 1;
        jp1j = k + 1;
        for (int ijA{jp1j}; ijA <= n; ijA++) {
          jA = 9 * (ijA - 1);
          temp = b_A_data[ijA + jAcol];
          if (temp != 0.0F) {
            for (int j{0}; j < 9; j++) {
              i = (j + yk) + 1;
              A_data[i] -= temp * A_data[j + jA];
            }
          }
        }
      }
    }
    yk = B_size[1] - 1;
    for (int k{yk}; k >= 1; k--) {
      jA = jpvt_data[k - 1];
      if (jA != k) {
        for (int ijA{0}; ijA < 9; ijA++) {
          jAcol = ijA + 9 * (k - 1);
          temp = A_data[jAcol];
          jp1j = ijA + 9 * (jA - 1);
          A_data[jAcol] = A_data[jp1j];
          A_data[jp1j] = temp;
        }
      }
    }
  } else {
    float b_B_data[27];
    float temp;
    int jA;
    int jAcol;
    int jp1j;
    int mmj;
    int n;
    int rankA;
    int u1;
    int yk;
    n = A_size[1];
    for (int ijA{0}; ijA < 9; ijA++) {
      for (int k{0}; k < n; k++) {
        b_B_data[k + n * ijA] = A_data[ijA + 9 * k];
      }
    }
    yk = B_size[1];
    jA = B_size[0];
    A_size[0] = B_size[1];
    A_size[1] = B_size[0];
    for (int k{0}; k < jA; k++) {
      for (int ijA{0}; ijA < yk; ijA++) {
        b_A_data[ijA + A_size[0] * k] = B_data[k + B_size[0] * ijA];
      }
    }
    int jpvt_size[2];
    lapack::xgeqp3(b_A_data, A_size, tau_data, jpvt_data, jpvt_size);
    rankA = 0;
    if (A_size[0] < A_size[1]) {
      yk = A_size[0];
      jA = A_size[1];
    } else {
      yk = A_size[1];
      jA = A_size[0];
    }
    if (yk > 0) {
      temp = 1.1920929E-6F * static_cast<float>(jA) * std::abs(b_A_data[0]);
      while ((rankA < yk) &&
             (!(std::abs(b_A_data[rankA + A_size[0] * rankA]) <= temp))) {
        rankA++;
      }
    }
    mmj = A_size[1];
    yk = A_size[1] * 9;
    if (yk - 1 >= 0) {
      std::memset(&Y_data[0], 0, static_cast<unsigned int>(yk) * sizeof(float));
    }
    yk = A_size[0];
    u1 = A_size[1];
    if (yk <= u1) {
      u1 = yk;
    }
    for (int j{0}; j < u1; j++) {
      jA = A_size[0];
      if (tau_data[j] != 0.0F) {
        int i;
        i = j + 2;
        for (int ijA{0}; ijA < 9; ijA++) {
          float s;
          jp1j = n * ijA;
          yk = j + jp1j;
          temp = b_B_data[yk];
          s = temp;
          for (int k{i}; k <= jA; k++) {
            s += b_A_data[(k + A_size[0] * j) - 1] * b_B_data[(k + jp1j) - 1];
          }
          s *= tau_data[j];
          if (s != 0.0F) {
            b_B_data[yk] = temp - s;
            yk = j + 2;
            for (int k{yk}; k <= jA; k++) {
              jAcol = (k + jp1j) - 1;
              b_B_data[jAcol] -= b_A_data[(k + A_size[0] * j) - 1] * s;
            }
          }
        }
      }
    }
    for (int ijA{0}; ijA < 9; ijA++) {
      for (int k{0}; k < rankA; k++) {
        Y_data[(jpvt_data[k] + mmj * ijA) - 1] = b_B_data[k + n * ijA];
      }
      for (int k{rankA}; k >= 1; k--) {
        yk = mmj * ijA;
        jAcol = (jpvt_data[k - 1] + yk) - 1;
        jp1j = A_size[0] * (k - 1);
        Y_data[jAcol] /= b_A_data[(k + jp1j) - 1];
        for (int j{0}; j <= k - 2; j++) {
          jA = (jpvt_data[j] + yk) - 1;
          Y_data[jA] -= Y_data[jAcol] * b_A_data[j + jp1j];
        }
      }
    }
    A_size[0] = 9;
    for (int ijA{0}; ijA < mmj; ijA++) {
      for (int k{0}; k < 9; k++) {
        A_data[k + 9 * ijA] = Y_data[ijA + mmj * k];
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
