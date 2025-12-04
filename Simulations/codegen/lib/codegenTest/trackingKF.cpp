//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: trackingKF.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 20:32:31
//

// Include Files
#include "trackingKF.h"
#include "KalmanFilter.h"
#include "codegenTest_data.h"
#include "eye.h"
#include "minOrMax.h"
#include "mrdivide_helper.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Variable Definitions
static const signed char iv1[9]{1, 0, 0, 0, 1, 0, 0, 0, 1};

// Function Definitions
//
// Arguments    : float value_data[]
//                int value_size[2]
// Return Type  : void
//
namespace coder {
void trackingKF::get_MeasurementNoise(float value_data[],
                                      int value_size[2]) const
{
  if (pV < 3.0F) {
    float f;
    int loop_ub;
    f = pV;
    if (f < 1.0F) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(f);
    }
    value_size[0] = loop_ub;
    value_size[1] = loop_ub;
    for (int i{0}; i < loop_ub; i++) {
      for (int i1{0}; i1 < loop_ub; i1++) {
        value_data[i1 + loop_ub * i] = pMeasurementNoise[i1 + 3 * i];
      }
    }
  } else {
    value_size[0] = 3;
    value_size[1] = 3;
    for (int i{0}; i < 9; i++) {
      value_data[i] = pMeasurementNoise[i];
    }
  }
}

//
// Arguments    : const float z[3]
// Return Type  : void
//
void trackingKF::correct(const float z[3])
{
  float P_corr[81];
  float gain[81];
  float a_data[27];
  float b_data[27];
  float gain_data[27];
  float tmp_data[27];
  float b_tmp_data[9];
  float f;
  int a_size[2];
  int b_tmp_size[2];
  int gain_size[2];
  int tmp_size[2];
  int b_loop_ub;
  int c_loop_ub;
  int loop_ub;
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(f);
    }
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < loop_ub; i1++) {
        b_data[i1 + loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    loop_ub = 3;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &b_data[0]);
  }
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      b_loop_ub = 0;
    } else {
      b_loop_ub = static_cast<int>(f);
    }
    tmp_size[0] = b_loop_ub;
    tmp_size[1] = 9;
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < b_loop_ub; i1++) {
        tmp_data[i1 + b_loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    tmp_size[0] = 3;
    tmp_size[1] = 9;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &tmp_data[0]);
  }
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      b_loop_ub = 0;
    } else {
      b_loop_ub = static_cast<int>(f);
    }
    a_size[0] = b_loop_ub;
    a_size[1] = 9;
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < b_loop_ub; i1++) {
        a_data[i1 + b_loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    a_size[0] = 3;
    a_size[1] = 9;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &a_data[0]);
  }
  get_MeasurementNoise(b_tmp_data, b_tmp_size);
  gain_size[0] = 9;
  gain_size[1] = loop_ub;
  for (int i2{0}; i2 < loop_ub; i2++) {
    for (int i{0}; i < 9; i++) {
      gain_data[i + 9 * i2] = 0.0F;
    }
    for (int i{0}; i < 9; i++) {
      f = b_data[i2 + loop_ub * i];
      for (int i1{0}; i1 < 9; i1++) {
        b_loop_ub = i1 + 9 * i2;
        gain_data[b_loop_ub] += pStateCovariance[i1 + 9 * i] * f;
      }
    }
  }
  if ((a_size[0] == b_tmp_size[0]) && (tmp_size[0] == b_tmp_size[1])) {
    float b_a_data[9];
    c_loop_ub = a_size[0];
    loop_ub = a_size[0];
    for (int i2{0}; i2 < 9; i2++) {
      for (int i{0}; i < c_loop_ub; i++) {
        b_data[i + loop_ub * i2] = 0.0F;
      }
      for (int i{0}; i < 9; i++) {
        f = pStateCovariance[i + 9 * i2];
        for (int i1{0}; i1 < c_loop_ub; i1++) {
          b_loop_ub = i1 + loop_ub * i2;
          b_data[b_loop_ub] += a_data[i1 + a_size[0] * i] * f;
        }
      }
    }
    b_loop_ub = tmp_size[0];
    a_size[1] = tmp_size[0];
    for (int i{0}; i < c_loop_ub; i++) {
      for (int i1{0}; i1 < b_loop_ub; i1++) {
        f = 0.0F;
        for (int i2{0}; i2 < 9; i2++) {
          f += b_data[i + loop_ub * i2] * tmp_data[i1 + tmp_size[0] * i2];
        }
        b_a_data[i + a_size[0] * i1] = f + b_tmp_data[i + b_tmp_size[0] * i1];
      }
    }
    internal::mrdiv(gain_data, gain_size, b_a_data, a_size);
  } else {
    binary_expand_op_1(gain_data, gain_size, a_data, a_size, this, tmp_data,
                       tmp_size, b_tmp_data, b_tmp_size);
  }
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      b_loop_ub = 0;
    } else {
      b_loop_ub = static_cast<int>(f);
    }
    a_size[0] = b_loop_ub;
    a_size[1] = 9;
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < b_loop_ub; i1++) {
        a_data[i1 + b_loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    a_size[0] = 3;
    a_size[1] = 9;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &a_data[0]);
  }
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(f);
    }
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < loop_ub; i1++) {
        b_data[i1 + loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    loop_ub = 3;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &b_data[0]);
  }
  b_loop_ub = gain_size[1];
  std::memset(&gain[0], 0, 81U * sizeof(float));
  for (int i{0}; i < 9; i++) {
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      f = b_data[i1 + loop_ub * i];
      for (int i2{0}; i2 < 9; i2++) {
        c_loop_ub = i2 + 9 * i;
        gain[c_loop_ub] += gain_data[i2 + 9 * i1] * f;
      }
    }
  }
  for (int i1{0}; i1 < 9; i1++) {
    for (int i2{0}; i2 < 9; i2++) {
      f = 0.0F;
      for (int i{0}; i < 9; i++) {
        f += gain[i1 + 9 * i] * pStateCovariance[i + 9 * i2];
      }
      b_loop_ub = i1 + 9 * i2;
      P_corr[b_loop_ub] = pStateCovariance[b_loop_ub] - f;
    }
  }
  if (a_size[0] == 3) {
    float b_z[3];
    float f1;
    float f2;
    for (int i{0}; i < 3; i++) {
      f = 0.0F;
      for (int i1{0}; i1 < 9; i1++) {
        f += a_data[i + 3 * i1] * pState[i1];
      }
      b_z[i] = z[i] - f;
    }
    f = b_z[0];
    f1 = b_z[1];
    f2 = b_z[2];
    for (int i{0}; i < 9; i++) {
      pState[i] +=
          (gain_data[i] * f + gain_data[i + 9] * f1) + gain_data[i + 18] * f2;
    }
  } else {
    binary_expand_op(this, gain_data, z, a_data, a_size);
  }
  for (int i{0}; i < 9; i++) {
    for (int i1{0}; i1 < 9; i1++) {
      b_loop_ub = i1 + 9 * i;
      pStateCovariance[b_loop_ub] =
          (P_corr[b_loop_ub] + P_corr[i + 9 * i1]) * 0.5F;
    }
  }
  if (!pIsInitialized) {
    pIsDistributionsSetup = true;
  }
}

//
// Arguments    : float z
// Return Type  : void
//
void trackingKF::correct(float z)
{
  float P_corr[81];
  float gain[81];
  float a_data[27];
  float b_data[27];
  float gain_data[27];
  float tmp_data[27];
  float b_tmp_data[9];
  float z_data[3];
  float f;
  int a_size[2];
  int b_tmp_size[2];
  int gain_size[2];
  int tmp_size[2];
  int b_loop_ub;
  int c_loop_ub;
  int loop_ub;
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(f);
    }
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < loop_ub; i1++) {
        b_data[i1 + loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    loop_ub = 3;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &b_data[0]);
  }
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      b_loop_ub = 0;
    } else {
      b_loop_ub = static_cast<int>(f);
    }
    tmp_size[0] = b_loop_ub;
    tmp_size[1] = 9;
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < b_loop_ub; i1++) {
        tmp_data[i1 + b_loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    tmp_size[0] = 3;
    tmp_size[1] = 9;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &tmp_data[0]);
  }
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      b_loop_ub = 0;
    } else {
      b_loop_ub = static_cast<int>(f);
    }
    a_size[0] = b_loop_ub;
    a_size[1] = 9;
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < b_loop_ub; i1++) {
        a_data[i1 + b_loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    a_size[0] = 3;
    a_size[1] = 9;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &a_data[0]);
  }
  get_MeasurementNoise(b_tmp_data, b_tmp_size);
  gain_size[0] = 9;
  gain_size[1] = loop_ub;
  for (int i2{0}; i2 < loop_ub; i2++) {
    for (int i{0}; i < 9; i++) {
      gain_data[i + 9 * i2] = 0.0F;
    }
    for (int i{0}; i < 9; i++) {
      f = b_data[i2 + loop_ub * i];
      for (int i1{0}; i1 < 9; i1++) {
        b_loop_ub = i1 + 9 * i2;
        gain_data[b_loop_ub] += pStateCovariance[i1 + 9 * i] * f;
      }
    }
  }
  if ((a_size[0] == b_tmp_size[0]) && (tmp_size[0] == b_tmp_size[1])) {
    float b_a_data[9];
    c_loop_ub = a_size[0];
    loop_ub = a_size[0];
    for (int i2{0}; i2 < 9; i2++) {
      for (int i{0}; i < c_loop_ub; i++) {
        b_data[i + loop_ub * i2] = 0.0F;
      }
      for (int i{0}; i < 9; i++) {
        f = pStateCovariance[i + 9 * i2];
        for (int i1{0}; i1 < c_loop_ub; i1++) {
          b_loop_ub = i1 + loop_ub * i2;
          b_data[b_loop_ub] += a_data[i1 + a_size[0] * i] * f;
        }
      }
    }
    b_loop_ub = tmp_size[0];
    a_size[1] = tmp_size[0];
    for (int i{0}; i < c_loop_ub; i++) {
      for (int i1{0}; i1 < b_loop_ub; i1++) {
        f = 0.0F;
        for (int i2{0}; i2 < 9; i2++) {
          f += b_data[i + loop_ub * i2] * tmp_data[i1 + tmp_size[0] * i2];
        }
        b_a_data[i + a_size[0] * i1] = f + b_tmp_data[i + b_tmp_size[0] * i1];
      }
    }
    internal::mrdiv(gain_data, gain_size, b_a_data, a_size);
  } else {
    binary_expand_op_1(gain_data, gain_size, a_data, a_size, this, tmp_data,
                       tmp_size, b_tmp_data, b_tmp_size);
  }
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      b_loop_ub = 0;
    } else {
      b_loop_ub = static_cast<int>(f);
    }
    a_size[0] = b_loop_ub;
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < b_loop_ub; i1++) {
        a_data[i1 + b_loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    a_size[0] = 3;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &a_data[0]);
  }
  if (pN < 3.0F) {
    f = pN;
    if (f < 1.0F) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(f);
    }
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < loop_ub; i1++) {
        b_data[i1 + loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    loop_ub = 3;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &b_data[0]);
  }
  c_loop_ub = gain_size[1];
  std::memset(&gain[0], 0, 81U * sizeof(float));
  for (int i{0}; i < 9; i++) {
    for (int i1{0}; i1 < c_loop_ub; i1++) {
      f = b_data[i1 + loop_ub * i];
      for (int i2{0}; i2 < 9; i2++) {
        b_loop_ub = i2 + 9 * i;
        gain[b_loop_ub] += gain_data[i2 + 9 * i1] * f;
      }
    }
  }
  for (int i1{0}; i1 < 9; i1++) {
    for (int i2{0}; i2 < 9; i2++) {
      f = 0.0F;
      for (int i{0}; i < 9; i++) {
        f += gain[i1 + 9 * i] * pStateCovariance[i + 9 * i2];
      }
      b_loop_ub = i1 + 9 * i2;
      P_corr[b_loop_ub] = pStateCovariance[b_loop_ub] - f;
    }
  }
  b_loop_ub = a_size[0];
  for (int i{0}; i < b_loop_ub; i++) {
    f = 0.0F;
    for (int i1{0}; i1 < 9; i1++) {
      f += a_data[i + a_size[0] * i1] * pState[i1];
    }
    z_data[i] = z - f;
  }
  for (int i1{0}; i1 < 9; i1++) {
    f = 0.0F;
    for (int i{0}; i < c_loop_ub; i++) {
      f += gain_data[i1 + 9 * i] * z_data[i];
    }
    pState[i1] += f;
    for (int i{0}; i < 9; i++) {
      b_loop_ub = i + 9 * i1;
      pStateCovariance[b_loop_ub] =
          (P_corr[b_loop_ub] + P_corr[i1 + 9 * i]) * 0.5F;
    }
  }
  if (!pIsInitialized) {
    pIsDistributionsSetup = true;
  }
}

//
// Arguments    : const float varargin_4[9]
// Return Type  : trackingKF *
//
trackingKF *trackingKF::init(const float varargin_4[9])
{
  static const float fv[81]{
      1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.5F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.5F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.5F, 1.0F, 1.0F};
  static const float b_ProcessNoiseModel[27]{
      0.5F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.5F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.5F, 1.0F, 1.0F};
  static const signed char b_iv[81]{
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  trackingKF *KF;
  double tmp_data[9];
  float val_data[9];
  float dims[2];
  float n;
  int loop_ub;
  KF = this;
  KF->pIsStateTransitionLocked = false;
  KF->pIsSmootherStateSizeInitialized = false;
  KF->IsLastJacobianInitialized = false;
  KF->pIsDistributionsSetup = false;
  KF->pIsInitialized = false;
  for (int i{0}; i < 81; i++) {
    KF->StateTransitionModel[i] = fv[i];
  }
  for (int i{0}; i < 9; i++) {
    KF->pState[i] = varargin_4[i];
  }
  for (int i{0}; i < 81; i++) {
    KF->pStateCovariance[i] = b_iv[i];
  }
  for (int i{0}; i < 27; i++) {
    KF->ProcessNoiseModel[i] = b_ProcessNoiseModel[i];
  }
  KF->pN = 3.0F;
  KF->pV = KF->pN;
  for (int i{0}; i < 9; i++) {
    KF->pProcessNoise[i] = iv1[i];
    KF->pMeasurementNoise[i] = 0.0F;
  }
  for (int i{0}; i < 27; i++) {
    KF->pMeasurementModel[i] = iv[i];
  }
  n = KF->pV;
  dims[0] = n;
  dims[1] = n;
  if (n == 1.0F) {
    val_data[0] = 1.0F;
  } else {
    int tmp_size[2];
    eye(dims, tmp_data, tmp_size);
    loop_ub = tmp_size[0] * tmp_size[1];
    for (int i{0}; i < loop_ub; i++) {
      val_data[i] = static_cast<float>(tmp_data[i]);
    }
  }
  n = KF->pV;
  if (n < 1.0F) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n);
  }
  for (int i{0}; i < loop_ub; i++) {
    for (int b_i{0}; b_i < loop_ub; b_i++) {
      KF->pMeasurementNoise[b_i + 3 * i] = val_data[b_i + loop_ub * i];
    }
  }
  KF->pIsStateTransitionLocked = true;
  return KF;
}

//
// Arguments    : float varargin_1
// Return Type  : void
//
void trackingKF::predict(float varargin_1)
{
  float KF[81];
  float P[81];
  float b_KF[27];
  float A1dim[9];
  float G1dim[3];
  float A1dim_tmp;
  int b_kidx;
  int kidx;
  if (!pIsSmootherStateSizeInitialized) {
    pIsSmootherStateSizeInitialized = true;
  }
  if (!IsLastJacobianInitialized) {
    IsLastJacobianInitialized = true;
  }
  if (!pIsDistributionsSetup) {
    pIsDistributionsSetup = true;
  }
  A1dim[0] = 1.0F;
  A1dim[3] = varargin_1;
  A1dim_tmp = varargin_1 * varargin_1 / 2.0F;
  A1dim[6] = A1dim_tmp;
  A1dim[1] = 0.0F;
  A1dim[4] = 1.0F;
  A1dim[7] = varargin_1;
  A1dim[2] = 0.0F;
  A1dim[5] = 0.0F;
  A1dim[8] = 1.0F;
  G1dim[0] = A1dim_tmp;
  G1dim[1] = varargin_1;
  G1dim[2] = 1.0F;
  kidx = -1;
  b_kidx = -1;
  for (int b_j1{0}; b_j1 < 3; b_j1++) {
    for (int j2{0}; j2 < 3; j2++) {
      float f;
      float f1;
      A1dim_tmp = A1dim[3 * j2];
      f = A1dim[3 * j2 + 1];
      f1 = A1dim[3 * j2 + 2];
      for (int i1{0}; i1 < 3; i1++) {
        int P_tmp;
        P_tmp = iv1[i1 + 3 * b_j1];
        P[kidx + 1] = static_cast<float>(P_tmp) * A1dim_tmp;
        P[kidx + 2] = static_cast<float>(P_tmp) * f;
        P[kidx + 3] = static_cast<float>(P_tmp) * f1;
        kidx += 3;
        ProcessNoiseModel[(b_kidx + i1) + 1] =
            static_cast<float>(iv1[j2 + 3 * b_j1]) * G1dim[i1];
      }
      b_kidx += 3;
    }
  }
  std::copy(&P[0], &P[81], &StateTransitionModel[0]);
  std::memset(&KF[0], 0, 81U * sizeof(float));
  for (int b_j1{0}; b_j1 < 9; b_j1++) {
    for (int j2{0}; j2 < 9; j2++) {
      A1dim_tmp = pStateCovariance[j2 + 9 * b_j1];
      for (int i1{0}; i1 < 9; i1++) {
        kidx = i1 + 9 * b_j1;
        KF[kidx] += StateTransitionModel[i1 + 9 * j2] * A1dim_tmp;
      }
    }
  }
  std::memset(&b_KF[0], 0, 27U * sizeof(float));
  for (int b_j1{0}; b_j1 < 3; b_j1++) {
    for (int j2{0}; j2 < 3; j2++) {
      A1dim_tmp = pProcessNoise[j2 + 3 * b_j1];
      for (int i1{0}; i1 < 9; i1++) {
        kidx = i1 + 9 * b_j1;
        b_KF[kidx] += ProcessNoiseModel[i1 + 9 * j2] * A1dim_tmp;
      }
    }
  }
  std::memset(&P[0], 0, 81U * sizeof(float));
  for (int b_j1{0}; b_j1 < 9; b_j1++) {
    for (int j2{0}; j2 < 9; j2++) {
      A1dim_tmp = StateTransitionModel[b_j1 + 9 * j2];
      for (int i1{0}; i1 < 9; i1++) {
        kidx = i1 + 9 * b_j1;
        P[kidx] += KF[i1 + 9 * j2] * A1dim_tmp;
      }
    }
  }
  std::memset(&KF[0], 0, 81U * sizeof(float));
  for (int b_j1{0}; b_j1 < 9; b_j1++) {
    for (int j2{0}; j2 < 3; j2++) {
      A1dim_tmp = ProcessNoiseModel[b_j1 + 9 * j2];
      for (int i1{0}; i1 < 9; i1++) {
        kidx = i1 + 9 * b_j1;
        KF[kidx] += b_KF[i1 + 9 * j2] * A1dim_tmp;
      }
    }
  }
  for (int b_j1{0}; b_j1 < 81; b_j1++) {
    P[b_j1] += KF[b_j1];
  }
  std::memset(&A1dim[0], 0, 9U * sizeof(float));
  for (int b_j1{0}; b_j1 < 9; b_j1++) {
    A1dim_tmp = pState[b_j1];
    for (int j2{0}; j2 < 9; j2++) {
      A1dim[j2] += StateTransitionModel[j2 + 9 * b_j1] * A1dim_tmp;
    }
  }
  for (int b_j1{0}; b_j1 < 9; b_j1++) {
    pState[b_j1] = A1dim[b_j1];
    for (int j2{0}; j2 < 9; j2++) {
      kidx = j2 + 9 * b_j1;
      pStateCovariance[kidx] = (P[kidx] + P[b_j1 + 9 * j2]) * 0.5F;
    }
  }
  pIsStateTransitionLocked = true;
}

//
// Arguments    : const float MeasurementModelMatrix[9]
// Return Type  : void
//
void trackingKF::set_MeasurementModel(const float MeasurementModelMatrix[9])
{
  int n_tmp;
  n_tmp = static_cast<int>(pN);
  for (int i{0}; i < 9; i++) {
    for (int i1{0}; i1 < n_tmp; i1++) {
      pMeasurementModel[i1 + 3 * i] = MeasurementModelMatrix[i1 + n_tmp * i];
    }
  }
}

//
// Arguments    : const float b_value[9]
// Return Type  : void
//
void trackingKF::set_MeasurementNoise(const float b_value[9])
{
  float varargin_1[3];
  float absx;
  int exponent;
  varargin_1[0] = std::abs(b_value[0]);
  varargin_1[1] = std::abs(b_value[4]);
  varargin_1[2] = std::abs(b_value[8]);
  absx = std::abs(internal::maximum(varargin_1));
  if ((!std::isinf(absx)) && (!std::isnan(absx)) &&
      (!(absx < 2.3509887E-38F))) {
    std::frexp(absx, &exponent);
  }
  for (int i{0}; i < 9; i++) {
    pMeasurementNoise[i] = b_value[i];
  }
}

//
// Arguments    : float b_value
// Return Type  : void
//
void trackingKF::set_MeasurementNoise(float b_value)
{
  double tmp_data[9];
  float absx;
  int exponent;
  absx = std::abs(b_value);
  if ((!std::isinf(absx)) && (!std::isnan(absx)) &&
      (!(absx < 2.3509887E-38F))) {
    std::frexp(absx, &exponent);
  }
  if (b_value > 0.0F) {
    float val_data[9];
    float dims[2];
    absx = pV;
    dims[0] = absx;
    dims[1] = absx;
    if (absx == 1.0F) {
      val_data[0] = b_value;
    } else {
      int tmp_size[2];
      eye(dims, tmp_data, tmp_size);
      exponent = tmp_size[0] * tmp_size[1];
      for (int i{0}; i < exponent; i++) {
        val_data[i] = b_value * static_cast<float>(tmp_data[i]);
      }
    }
    if (absx < 1.0F) {
      exponent = 0;
    } else {
      exponent = static_cast<int>(absx);
    }
    for (int i{0}; i < exponent; i++) {
      for (int i1{0}; i1 < exponent; i1++) {
        pMeasurementNoise[i1 + 3 * i] = val_data[i1 + exponent * i];
      }
    }
  }
}

//
// Arguments    : const float b_value[9]
// Return Type  : void
//
void trackingKF::set_ProcessNoise(const float b_value[9])
{
  float varargin_1[3];
  float absx;
  int exponent;
  varargin_1[0] = std::abs(b_value[0]);
  varargin_1[1] = std::abs(b_value[4]);
  varargin_1[2] = std::abs(b_value[8]);
  absx = std::abs(internal::maximum(varargin_1));
  if ((!std::isinf(absx)) && (!std::isnan(absx)) &&
      (!(absx < 2.3509887E-38F))) {
    std::frexp(absx, &exponent);
  }
  for (int i{0}; i < 9; i++) {
    pProcessNoise[i] = b_value[i];
  }
}

} // namespace coder

//
// File trailer for trackingKF.cpp
//
// [EOF]
//
