//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: trackingKF.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "trackingKF.h"
#include "KalmanFilter.h"
#include "codegenTest_data.h"
#include "constAccelerationModel.h"
#include "eye.h"
#include "mrdivide_helper.h"
#include "rt_nonfinite.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : const double z[3]
// Return Type  : void
//
namespace coder {
void trackingKF::KalmanFilter_correct(const double z[3])
{
  double P_corr[81];
  double gain[81];
  double a_data[27];
  double b_data[27];
  double gain_data[27];
  double tmp_data[27];
  double b_tmp_data[9];
  double d;
  int a_size[2];
  int b_size[2];
  int b_tmp_size[2];
  int gain_size[2];
  int obj_size[2];
  int tmp_size[2];
  int a_data_tmp;
  int obj_data_tmp;
  get_MeasurementModel(b_data, b_size);
  get_MeasurementModel(tmp_data, tmp_size);
  get_MeasurementModel(a_data, a_size);
  get_MeasurementNoise(b_tmp_data, b_tmp_size);
  if ((a_size[0] == b_tmp_size[0]) && (tmp_size[0] == b_tmp_size[1])) {
    double b_a_data[9];
    int loop_ub;
    loop_ub = a_size[0];
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < loop_ub; i1++) {
        gain_data[i1 + loop_ub * i] = 0.0;
      }
      for (int i1{0}; i1 < 9; i1++) {
        d = pStateCovariance[i1 + 9 * i];
        for (int i2{0}; i2 < loop_ub; i2++) {
          a_data_tmp = i2 + loop_ub * i;
          gain_data[a_data_tmp] += a_data[i2 + a_size[0] * i1] * d;
        }
      }
    }
    a_data_tmp = b_size[0];
    obj_size[0] = 9;
    obj_size[1] = b_size[0];
    for (int i1{0}; i1 < a_data_tmp; i1++) {
      std::memset(&a_data[i1 * 9], 0, 9U * sizeof(double));
      for (int i2{0}; i2 < 9; i2++) {
        d = b_data[i1 + b_size[0] * i2];
        for (int i{0}; i < 9; i++) {
          obj_data_tmp = i + 9 * i1;
          a_data[obj_data_tmp] += pStateCovariance[i + 9 * i2] * d;
        }
      }
    }
    obj_data_tmp = tmp_size[0];
    a_size[1] = tmp_size[0];
    for (int i1{0}; i1 < loop_ub; i1++) {
      for (int i{0}; i < obj_data_tmp; i++) {
        d = 0.0;
        for (int i2{0}; i2 < 9; i2++) {
          d += gain_data[i1 + loop_ub * i2] * tmp_data[i + tmp_size[0] * i2];
        }
        b_a_data[i1 + a_size[0] * i] = d + b_tmp_data[i1 + b_tmp_size[0] * i];
      }
    }
    internal::mrdiv(a_data, obj_size, b_a_data, a_size, gain_data, gain_size);
  } else {
    binary_expand_op_1(gain_data, this, b_data, b_size, a_data, a_size,
                       tmp_data, tmp_size, b_tmp_data, b_tmp_size, gain_size);
  }
  get_MeasurementModel(a_data, a_size);
  get_MeasurementModel(b_data, b_size);
  a_data_tmp = gain_size[1];
  std::memset(&gain[0], 0, 81U * sizeof(double));
  for (int i2{0}; i2 < 9; i2++) {
    for (int i1{0}; i1 < a_data_tmp; i1++) {
      d = b_data[i1 + b_size[0] * i2];
      for (int i{0}; i < 9; i++) {
        obj_data_tmp = i + 9 * i2;
        gain[obj_data_tmp] += gain_data[i + 9 * i1] * d;
      }
    }
  }
  for (int i1{0}; i1 < 9; i1++) {
    for (int i{0}; i < 9; i++) {
      d = 0.0;
      for (int i2{0}; i2 < 9; i2++) {
        d += gain[i1 + 9 * i2] * pStateCovariance[i2 + 9 * i];
      }
      a_data_tmp = i1 + 9 * i;
      P_corr[a_data_tmp] = pStateCovariance[a_data_tmp] - d;
    }
  }
  if (a_size[0] == 3) {
    double b_z[3];
    double d1;
    double d2;
    for (int i2{0}; i2 < 3; i2++) {
      d = 0.0;
      for (int i1{0}; i1 < 9; i1++) {
        d += a_data[i2 + 3 * i1] * pState[i1];
      }
      b_z[i2] = z[i2] - d;
    }
    d = b_z[0];
    d1 = b_z[1];
    d2 = b_z[2];
    for (int i2{0}; i2 < 9; i2++) {
      pState[i2] += (gain_data[i2] * d + gain_data[i2 + 9] * d1) +
                    gain_data[i2 + 18] * d2;
    }
  } else {
    binary_expand_op(this, gain_data, z, a_data, a_size);
  }
  for (int i1{0}; i1 < 9; i1++) {
    for (int i2{0}; i2 < 9; i2++) {
      a_data_tmp = i2 + 9 * i1;
      pStateCovariance[a_data_tmp] =
          (P_corr[a_data_tmp] + P_corr[i1 + 9 * i2]) * 0.5;
    }
  }
}

//
// Arguments    : void
// Return Type  : trackingKF *
//
trackingKF *trackingKF::KalmanFilter_init()
{
  static const double dv[81]{
      1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
      1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0};
  static const double b_ProcessNoiseModel[27]{
      0.5, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0,
      1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0};
  static const signed char b_iv[81]{
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  trackingKF *obj;
  obj = this;
  for (int i{0}; i < 81; i++) {
    obj->StateTransitionModel[i] = dv[i];
  }
  for (int i{0}; i < 9; i++) {
    obj->pState[i] = 0.0;
  }
  for (int i{0}; i < 81; i++) {
    obj->pStateCovariance[i] = b_iv[i];
  }
  for (int i{0}; i < 27; i++) {
    obj->ProcessNoiseModel[i] = b_ProcessNoiseModel[i];
  }
  obj->pN = 3.0;
  obj->pV = obj->pN;
  for (int i{0}; i < 9; i++) {
    obj->pProcessNoise[i] = iv1[i];
    obj->pMeasurementNoise[i] = 0.0;
  }
  for (int i{0}; i < 27; i++) {
    obj->pMeasurementModel[i] = iv[i];
  }
  obj->set_MeasurementNoise();
  return obj;
}

//
// Arguments    : void
// Return Type  : trackingKF *
//
trackingKF *trackingKF::LinearizedSmoother_init()
{
  trackingKF *obj;
  obj = this;
  obj->IsLastJacobianInitialized = false;
  obj->pIsDistributionsSetup = false;
  obj->pIsInitialized = false;
  return obj;
}

//
// Arguments    : void
// Return Type  : void
//
void trackingKF::ensureMethodDefinition()
{
  ensureSmootherStateSizeIsDefined();
  if (!IsLastJacobianInitialized) {
    IsLastJacobianInitialized = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void trackingKF::ensureSmootherStateSizeIsDefined()
{
  bounded_array<double, 27U, 2U> obj;
  if (!pIsSmootherStateSizeInitialized) {
    get_MeasurementModel(obj.data, obj.size);
    pIsSmootherStateSizeInitialized = true;
  }
}

//
// Arguments    : double value_data[]
//                int value_size[2]
// Return Type  : void
//
void trackingKF::get_MeasurementModel(double value_data[],
                                      int value_size[2]) const
{
  if (pN < 3.0) {
    double d;
    int loop_ub;
    d = pN;
    if (d < 1.0) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(d);
    }
    value_size[0] = loop_ub;
    value_size[1] = 9;
    for (int i{0}; i < 9; i++) {
      for (int i1{0}; i1 < loop_ub; i1++) {
        value_data[i1 + loop_ub * i] = pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    value_size[0] = 3;
    value_size[1] = 9;
    std::copy(&pMeasurementModel[0], &pMeasurementModel[27], &value_data[0]);
  }
}

//
// Arguments    : double value_data[]
//                int value_size[2]
// Return Type  : void
//
void trackingKF::get_MeasurementNoise(double value_data[],
                                      int value_size[2]) const
{
  if (pV < 3.0) {
    double d;
    int loop_ub;
    d = pV;
    if (d < 1.0) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(d);
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
    std::copy(&pMeasurementNoise[0], &pMeasurementNoise[9], &value_data[0]);
  }
}

//
// Arguments    : const double varargin_1[81]
//                const double varargin_2[27]
// Return Type  : void
//
void trackingKF::predict(const double varargin_1[81],
                         const double varargin_2[27])
{
  double P[81];
  double obj[81];
  double b_obj[27];
  double c_obj[9];
  double d;
  int obj_tmp;
  std::copy(&varargin_1[0], &varargin_1[81], &StateTransitionModel[0]);
  std::copy(&varargin_2[0], &varargin_2[27], &ProcessNoiseModel[0]);
  std::memset(&obj[0], 0, 81U * sizeof(double));
  for (int i{0}; i < 9; i++) {
    for (int i1{0}; i1 < 9; i1++) {
      d = pStateCovariance[i1 + 9 * i];
      for (int i2{0}; i2 < 9; i2++) {
        obj_tmp = i2 + 9 * i;
        obj[obj_tmp] += StateTransitionModel[i2 + 9 * i1] * d;
      }
    }
  }
  std::memset(&b_obj[0], 0, 27U * sizeof(double));
  for (int i{0}; i < 3; i++) {
    for (int i1{0}; i1 < 3; i1++) {
      d = pProcessNoise[i1 + 3 * i];
      for (int i2{0}; i2 < 9; i2++) {
        obj_tmp = i2 + 9 * i;
        b_obj[obj_tmp] += ProcessNoiseModel[i2 + 9 * i1] * d;
      }
    }
  }
  std::memset(&P[0], 0, 81U * sizeof(double));
  for (int i{0}; i < 9; i++) {
    for (int i1{0}; i1 < 9; i1++) {
      d = StateTransitionModel[i + 9 * i1];
      for (int i2{0}; i2 < 9; i2++) {
        obj_tmp = i2 + 9 * i;
        P[obj_tmp] += obj[i2 + 9 * i1] * d;
      }
    }
  }
  std::memset(&obj[0], 0, 81U * sizeof(double));
  for (int i{0}; i < 9; i++) {
    for (int i1{0}; i1 < 3; i1++) {
      d = ProcessNoiseModel[i + 9 * i1];
      for (int i2{0}; i2 < 9; i2++) {
        obj_tmp = i2 + 9 * i;
        obj[obj_tmp] += b_obj[i2 + 9 * i1] * d;
      }
    }
  }
  for (int i{0}; i < 81; i++) {
    P[i] += obj[i];
  }
  std::memset(&c_obj[0], 0, 9U * sizeof(double));
  for (int i{0}; i < 9; i++) {
    d = pState[i];
    for (int i1{0}; i1 < 9; i1++) {
      c_obj[i1] += StateTransitionModel[i1 + 9 * i] * d;
    }
  }
  for (int i{0}; i < 9; i++) {
    pState[i] = c_obj[i];
    for (int i1{0}; i1 < 9; i1++) {
      obj_tmp = i1 + 9 * i;
      pStateCovariance[obj_tmp] = (P[obj_tmp] + P[i + 9 * i1]) * 0.5;
    }
  }
}

//
// Arguments    : const double val_data[]
// Return Type  : void
//
void trackingKF::setMeasurementNoise(const double val_data[])
{
  double n;
  int loop_ub;
  n = pV;
  if (n < 1.0) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n);
  }
  for (int i{0}; i < loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      pMeasurementNoise[i1 + 3 * i] = val_data[i1 + loop_ub * i];
    }
  }
}

//
// Arguments    : void
// Return Type  : void
//
void trackingKF::set_MeasurementNoise()
{
  double b_data[9];
  double dims[2];
  double n;
  n = pV;
  dims[0] = n;
  dims[1] = n;
  if (n == 1.0) {
    b_data[0] = 1.0;
  } else {
    int b_size[2];
    eye(dims, b_data, b_size);
  }
  setMeasurementNoise(b_data);
}

//
// Arguments    : void
// Return Type  : void
//
void trackingKF::setupInitialDistributions()
{
  ensureMethodDefinition();
  if (!pIsDistributionsSetup) {
    pIsDistributionsSetup = true;
  }
}

//
// Arguments    : const double z[3]
// Return Type  : void
//
void trackingKF::correct(const double z[3])
{
  KalmanFilter_correct(z);
  if (!pIsInitialized) {
    pIsDistributionsSetup = true;
  }
}

//
// Arguments    : void
// Return Type  : trackingKF *
//
trackingKF *trackingKF::init()
{
  trackingKF *KF;
  KF = this;
  KF->pIsStateTransitionLocked = false;
  KF->pIsSmootherStateSizeInitialized = false;
  KF = KF->LinearizedSmoother_init();
  KF = KF->KalmanFilter_init();
  KF->pIsStateTransitionLocked = true;
  return KF;
}

//
// Arguments    : double varargin_1
// Return Type  : void
//
void trackingKF::predict(double varargin_1)
{
  double A[81];
  double a__1[81];
  double G[27];
  setupInitialDistributions();
  matlabshared::tracking::internal::fusion::constAccelerationModel(varargin_1,
                                                                   A, a__1, G);
  predict(A, G);
  pIsStateTransitionLocked = true;
}

} // namespace coder

//
// File trailer for trackingKF.cpp
//
// [EOF]
//
