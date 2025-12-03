//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: trackingKF.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 02-Dec-2025 17:03:31
//

// Include Files
#include "trackingKF.h"
#include "KalmanFilter.h"
#include "codegenTest_data.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Variable Definitions
static const signed char iv1[9]{1, 0, 0, 0, 1, 0, 0, 0, 1};

// Function Definitions
//
// Arguments    : const float z[3]
// Return Type  : void
//
namespace coder {
void trackingKF::correct(const float z[3])
{
  float P_corr[81];
  float gain[81];
  float B_data[27];
  float Y_data[27];
  float a_data[27];
  float gain_data[27];
  float b_B_data[9];
  float c_B_data[9];
  float b_z[3];
  float s;
  float temp;
  int jpvt_data[3];
  int B_size[2];
  int a_size[2];
  int b_B_size[2];
  int b_loop_ub;
  int jA;
  int jAcol;
  int loop_ub;
  int yk;
  if (pN < 3.0F) {
    temp = pN;
    if (temp < 1.0F) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(temp);
    }
    for (int k{0}; k < 9; k++) {
      for (int ijA{0}; ijA < loop_ub; ijA++) {
        Y_data[ijA + loop_ub * k] = pMeasurementModel[ijA + 3 * k];
      }
    }
  } else {
    loop_ub = 3;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &Y_data[0]);
  }
  if (pN < 3.0F) {
    temp = pN;
    if (temp < 1.0F) {
      yk = 0;
    } else {
      yk = static_cast<int>(temp);
    }
    B_size[0] = yk;
    B_size[1] = 9;
    for (int k{0}; k < 9; k++) {
      for (int ijA{0}; ijA < yk; ijA++) {
        B_data[ijA + yk * k] = pMeasurementModel[ijA + 3 * k];
      }
    }
  } else {
    B_size[0] = 3;
    B_size[1] = 9;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &B_data[0]);
  }
  if (pN < 3.0F) {
    temp = pN;
    if (temp < 1.0F) {
      yk = 0;
    } else {
      yk = static_cast<int>(temp);
    }
    a_size[0] = yk;
    a_size[1] = 9;
    for (int k{0}; k < 9; k++) {
      for (int ijA{0}; ijA < yk; ijA++) {
        a_data[ijA + yk * k] = pMeasurementModel[ijA + 3 * k];
      }
    }
  } else {
    a_size[0] = 3;
    a_size[1] = 9;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &a_data[0]);
  }
  if (pV < 3.0F) {
    temp = pV;
    if (temp < 1.0F) {
      yk = 0;
    } else {
      yk = static_cast<int>(temp);
    }
    if (temp < 1.0F) {
      jA = 0;
    } else {
      jA = static_cast<int>(temp);
    }
    b_B_size[0] = yk;
    b_B_size[1] = jA;
    for (int ijA{0}; ijA < jA; ijA++) {
      for (int b_j{0}; b_j < yk; b_j++) {
        b_B_data[b_j + yk * ijA] = pMeasurementNoise[b_j + 3 * ijA];
      }
    }
  } else {
    b_B_size[0] = 3;
    b_B_size[1] = 3;
    for (int k{0}; k < 9; k++) {
      b_B_data[k] = pMeasurementNoise[k];
    }
  }
  b_loop_ub = loop_ub;
  for (int j{0}; j < loop_ub; j++) {
    for (int ijA{0}; ijA < 9; ijA++) {
      gain_data[ijA + 9 * j] = 0.0F;
    }
    for (int k{0}; k < 9; k++) {
      temp = Y_data[j + loop_ub * k];
      for (int b_j{0}; b_j < 9; b_j++) {
        yk = b_j + 9 * j;
        gain_data[yk] += pStateCovariance[b_j + 9 * k] * temp;
      }
    }
  }
  if ((a_size[0] == b_B_size[0]) && (B_size[0] == b_B_size[1])) {
    jAcol = a_size[0];
    loop_ub = a_size[0];
    for (int b_j{0}; b_j < 9; b_j++) {
      for (int ijA{0}; ijA < jAcol; ijA++) {
        Y_data[ijA + loop_ub * b_j] = 0.0F;
      }
      for (int k{0}; k < 9; k++) {
        temp = pStateCovariance[k + 9 * b_j];
        for (int ijA{0}; ijA < jAcol; ijA++) {
          yk = ijA + loop_ub * b_j;
          Y_data[yk] += a_data[ijA + a_size[0] * k] * temp;
        }
      }
    }
    jA = B_size[0];
    b_B_size[0] = a_size[0];
    b_B_size[1] = B_size[0];
    for (int ijA{0}; ijA < jAcol; ijA++) {
      for (int b_j{0}; b_j < jA; b_j++) {
        temp = 0.0F;
        for (int k{0}; k < 9; k++) {
          temp += Y_data[ijA + loop_ub * k] * B_data[b_j + B_size[0] * k];
        }
        yk = ijA + b_B_size[0] * b_j;
        b_B_data[yk] += temp;
      }
    }
  } else {
    binary_expand_op_1(b_B_data, b_B_size, a_data, a_size, this, B_data,
                       B_size);
  }
  if ((b_loop_ub == 0) || ((b_B_size[0] == 0) || (b_B_size[1] == 0))) {
    b_loop_ub = b_B_size[0];
    yk = 9 * b_B_size[0];
    if (yk - 1 >= 0) {
      std::memset(&gain_data[0], 0,
                  static_cast<unsigned int>(yk) * sizeof(float));
    }
  } else if (b_B_size[0] == b_B_size[1]) {
    int Y_data_tmp;
    int jp1j;
    int n;
    n = b_B_size[1];
    jpvt_data[0] = 1;
    yk = 1;
    for (int k{2}; k <= n; k++) {
      yk++;
      jpvt_data[k - 1] = yk;
    }
    if (b_B_size[1] - 1 <= b_B_size[1]) {
      Y_data_tmp = b_B_size[1];
    } else {
      Y_data_tmp = 2;
    }
    for (int j{0}; j <= Y_data_tmp - 2; j++) {
      int mmj;
      mmj = n - j;
      loop_ub = j * (n + 1);
      jp1j = loop_ub + 2;
      if (mmj - 1 < 0) {
        yk = -1;
      } else {
        yk = 0;
        if (mmj - 1 > 0) {
          temp = std::abs(b_B_data[loop_ub]);
          for (int k{2}; k <= mmj; k++) {
            s = std::abs(b_B_data[(loop_ub + k) - 1]);
            if (s > temp) {
              yk = k - 1;
              temp = s;
            }
          }
        }
      }
      if (b_B_data[loop_ub + yk] != 0.0F) {
        if (yk != 0) {
          jA = j + yk;
          jpvt_data[j] = jA + 1;
          for (int k{0}; k < n; k++) {
            yk = k * n;
            jAcol = j + yk;
            temp = b_B_data[jAcol];
            yk += jA;
            b_B_data[jAcol] = b_B_data[yk];
            b_B_data[yk] = temp;
          }
        }
        yk = loop_ub + mmj;
        for (int k{jp1j}; k <= yk; k++) {
          b_B_data[k - 1] /= b_B_data[loop_ub];
        }
      }
      yk = loop_ub + n;
      jA = yk;
      for (int k{0}; k <= mmj - 2; k++) {
        temp = b_B_data[yk + k * n];
        if (temp != 0.0F) {
          jAcol = jA + 2;
          jp1j = mmj + jA;
          for (int ijA{jAcol}; ijA <= jp1j; ijA++) {
            b_B_data[ijA - 1] += b_B_data[((loop_ub + ijA) - jA) - 1] * -temp;
          }
        }
        jA += n;
      }
    }
    for (int b_j{0}; b_j < n; b_j++) {
      jp1j = 9 * b_j - 1;
      yk = n * b_j;
      for (int k{0}; k < b_j; k++) {
        jA = 9 * k;
        temp = b_B_data[k + yk];
        if (temp != 0.0F) {
          for (int ijA{0}; ijA < 9; ijA++) {
            jAcol = (ijA + jp1j) + 1;
            gain_data[jAcol] -= temp * gain_data[ijA + jA];
          }
        }
      }
      temp = 1.0F / b_B_data[b_j + yk];
      for (int ijA{0}; ijA < 9; ijA++) {
        yk = (ijA + jp1j) + 1;
        gain_data[yk] *= temp;
      }
    }
    for (int k{n}; k >= 1; k--) {
      yk = 9 * (k - 1) - 1;
      jAcol = n * (k - 1) - 1;
      jp1j = k + 1;
      for (int b_j{jp1j}; b_j <= n; b_j++) {
        jA = 9 * (b_j - 1);
        temp = b_B_data[b_j + jAcol];
        if (temp != 0.0F) {
          for (int j{0}; j < 9; j++) {
            Y_data_tmp = (j + yk) + 1;
            gain_data[Y_data_tmp] -= temp * gain_data[j + jA];
          }
        }
      }
    }
    yk = b_B_size[1] - 1;
    for (int k{yk}; k >= 1; k--) {
      jA = jpvt_data[k - 1];
      if (jA != k) {
        for (int b_j{0}; b_j < 9; b_j++) {
          jAcol = b_j + 9 * (k - 1);
          temp = gain_data[jAcol];
          jp1j = b_j + 9 * (jA - 1);
          gain_data[jAcol] = gain_data[jp1j];
          gain_data[jp1j] = temp;
        }
      }
    }
  } else {
    int Y_data_tmp;
    int mmj;
    int n;
    for (int k{0}; k < 9; k++) {
      for (int ijA{0}; ijA < b_loop_ub; ijA++) {
        B_data[ijA + b_loop_ub * k] = gain_data[k + 9 * ijA];
      }
    }
    yk = b_B_size[1];
    jA = b_B_size[0];
    for (int k{0}; k < jA; k++) {
      for (int ijA{0}; ijA < yk; ijA++) {
        c_B_data[ijA + yk * k] = b_B_data[k + b_B_size[0] * ijA];
      }
    }
    b_B_size[0] = b_B_size[1];
    b_B_size[1] = jA;
    yk *= jA;
    std::copy(&c_B_data[0], &c_B_data[yk], &b_B_data[0]);
    internal::lapack::xgeqp3(b_B_data, b_B_size, b_z, jpvt_data, B_size);
    n = 0;
    if (b_B_size[0] < b_B_size[1]) {
      yk = b_B_size[0];
      jA = b_B_size[1];
    } else {
      yk = b_B_size[1];
      jA = b_B_size[0];
    }
    if (yk > 0) {
      temp = 1.1920929E-6F * static_cast<float>(jA) * std::abs(b_B_data[0]);
      while ((n < yk) && (!(std::abs(b_B_data[n + b_B_size[0] * n]) <= temp))) {
        n++;
      }
    }
    loop_ub = b_B_size[1];
    yk = b_B_size[1] * 9;
    if (yk - 1 >= 0) {
      std::memset(&Y_data[0], 0, static_cast<unsigned int>(yk) * sizeof(float));
    }
    yk = b_B_size[0];
    mmj = b_B_size[1];
    if (yk <= mmj) {
      mmj = yk;
    }
    for (int j{0}; j < mmj; j++) {
      int jp1j;
      jp1j = b_B_size[0];
      if (b_z[j] != 0.0F) {
        Y_data_tmp = j + 2;
        for (int b_j{0}; b_j < 9; b_j++) {
          jA = b_loop_ub * b_j;
          yk = j + jA;
          temp = B_data[yk];
          s = temp;
          for (int k{Y_data_tmp}; k <= jp1j; k++) {
            s += b_B_data[(k + b_B_size[0] * j) - 1] * B_data[(k + jA) - 1];
          }
          s *= b_z[j];
          if (s != 0.0F) {
            B_data[yk] = temp - s;
            yk = j + 2;
            for (int k{yk}; k <= jp1j; k++) {
              jAcol = (k + jA) - 1;
              B_data[jAcol] -= b_B_data[(k + b_B_size[0] * j) - 1] * s;
            }
          }
        }
      }
    }
    for (int j{0}; j < 9; j++) {
      for (int k{0}; k < n; k++) {
        Y_data[(jpvt_data[k] + loop_ub * j) - 1] = B_data[k + b_loop_ub * j];
      }
      for (int k{n}; k >= 1; k--) {
        yk = loop_ub * j;
        jA = (jpvt_data[k - 1] + yk) - 1;
        jAcol = b_B_size[0] * (k - 1);
        Y_data[jA] /= b_B_data[(k + jAcol) - 1];
        for (int ijA{0}; ijA <= k - 2; ijA++) {
          Y_data_tmp = (jpvt_data[ijA] + yk) - 1;
          Y_data[Y_data_tmp] -= Y_data[jA] * b_B_data[ijA + jAcol];
        }
      }
    }
    b_loop_ub = b_B_size[1];
    for (int ijA{0}; ijA < loop_ub; ijA++) {
      for (int k{0}; k < 9; k++) {
        gain_data[k + 9 * ijA] = Y_data[ijA + loop_ub * k];
      }
    }
  }
  if (pN < 3.0F) {
    temp = pN;
    if (temp < 1.0F) {
      yk = 0;
    } else {
      yk = static_cast<int>(temp);
    }
    a_size[0] = yk;
    a_size[1] = 9;
    for (int k{0}; k < 9; k++) {
      for (int ijA{0}; ijA < yk; ijA++) {
        a_data[ijA + yk * k] = pMeasurementModel[ijA + 3 * k];
      }
    }
  } else {
    a_size[0] = 3;
    a_size[1] = 9;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &a_data[0]);
  }
  if (pN < 3.0F) {
    temp = pN;
    if (temp < 1.0F) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(temp);
    }
    for (int k{0}; k < 9; k++) {
      for (int ijA{0}; ijA < loop_ub; ijA++) {
        Y_data[ijA + loop_ub * k] = pMeasurementModel[ijA + 3 * k];
      }
    }
  } else {
    loop_ub = 3;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &Y_data[0]);
  }
  std::memset(&gain[0], 0, 81U * sizeof(float));
  for (int ijA{0}; ijA < 9; ijA++) {
    for (int k{0}; k < b_loop_ub; k++) {
      temp = Y_data[k + loop_ub * ijA];
      for (int b_j{0}; b_j < 9; b_j++) {
        yk = b_j + 9 * ijA;
        gain[yk] += gain_data[b_j + 9 * k] * temp;
      }
    }
  }
  for (int ijA{0}; ijA < 9; ijA++) {
    for (int b_j{0}; b_j < 9; b_j++) {
      temp = 0.0F;
      for (int k{0}; k < 9; k++) {
        temp += gain[ijA + 9 * k] * pStateCovariance[k + 9 * b_j];
      }
      yk = ijA + 9 * b_j;
      P_corr[yk] = pStateCovariance[yk] - temp;
    }
  }
  if (a_size[0] == 3) {
    float f;
    for (int k{0}; k < 3; k++) {
      temp = 0.0F;
      for (int ijA{0}; ijA < 9; ijA++) {
        temp += a_data[k + 3 * ijA] * pState[ijA];
      }
      b_z[k] = z[k] - temp;
    }
    temp = b_z[0];
    s = b_z[1];
    f = b_z[2];
    for (int k{0}; k < 9; k++) {
      pState[k] +=
          (gain_data[k] * temp + gain_data[k + 9] * s) + gain_data[k + 18] * f;
    }
  } else {
    binary_expand_op(this, gain_data, z, a_data, a_size);
  }
  for (int k{0}; k < 9; k++) {
    for (int ijA{0}; ijA < 9; ijA++) {
      yk = ijA + 9 * k;
      pStateCovariance[yk] = (P_corr[yk] + P_corr[k + 9 * ijA]) * 0.5F;
    }
  }
  pHasPrediction = false;
  if (!pIsInitialized) {
    pIsSmoothingLocked = true;
    pIsDistributionsSetup = true;
  }
  pWasRetrodicted = false;
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
  float n;
  int loop_ub;
  signed char b_data[9];
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
  if (n == 1.0F) {
    b_data[0] = 1;
  } else {
    int d;
    if (n < 0.0F) {
      n = 0.0F;
    }
    loop_ub = static_cast<int>(n);
    d = static_cast<int>(n);
    if (loop_ub <= d) {
      d = loop_ub;
    }
    loop_ub = static_cast<int>(n) * static_cast<int>(n);
    if (loop_ub - 1 >= 0) {
      std::memset(&b_data[0], 0,
                  static_cast<unsigned int>(loop_ub) * sizeof(signed char));
    }
    if (d > 0) {
      for (int i{0}; i < d; i++) {
        b_data[i + static_cast<int>(n) * i] = 1;
      }
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
      KF->pMeasurementNoise[b_i + 3 * i] = b_data[b_i + loop_ub * i];
    }
  }
  KF->pHasPrediction = false;
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
    pSmootherStateSize = 9.0F;
    pIsSmootherStateSizeInitialized = true;
  }
  if (!IsLastJacobianInitialized) {
    IsLastJacobianInitialized = true;
  }
  if (!pIsDistributionsSetup) {
    pIsSmoothingLocked = true;
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
  pHasPrediction = true;
  pIsStateTransitionLocked = true;
  std::copy(&StateTransitionModel[0], &StateTransitionModel[81],
            &LastJacobian[0]);
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
