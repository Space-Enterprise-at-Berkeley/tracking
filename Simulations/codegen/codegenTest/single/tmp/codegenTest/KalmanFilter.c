#include "KalmanFilter.h"
#include "codegenTest_float_mex_data.h"
#include "codegenTest_float_mex_internal_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <emmintrin.h>
#include <string.h>

static emlrtRSInfo nc_emlrtRSI = {
    626, "KalmanFilter/validateMeasurementModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRTEInfo emlrtRTEI = {
    628, 33, "KalmanFilter/validateMeasurementModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtECInfo b_emlrtECI = {
    -1, 478, 17, "KalmanFilter/set.MeasurementModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRTEInfo d_emlrtRTEI = {
    477, 17, "KalmanFilter/set.MeasurementModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRTEInfo e_emlrtRTEI = {
    476, 17, "KalmanFilter/set.MeasurementModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

void binary_expand_op(trackingKF *in1, const real_T in2_data[],
                      const real_T in3[3], const real_T in4_data[],
                      const int32_T *in4_size)
{
  real_T in3_idx_0;
  real_T in3_idx_1;
  real_T in3_idx_2;
  int32_T i;
  int32_T stride_0_0;
  stride_0_0 = (*in4_size != 1);
  in3_idx_0 = in3[0] - in4_data[0];
  in3_idx_1 = in3[1] - in4_data[stride_0_0];
  in3_idx_2 = in3[2] - in4_data[stride_0_0 << 1];
  for (i = 0; i <= 6; i += 2) {
    __m128d r;
    __m128d r1;
    r = _mm_loadu_pd(&in2_data[i]);
    r1 = _mm_mul_pd(r, _mm_set1_pd(in3_idx_0));
    r = _mm_loadu_pd(&in2_data[i + 9]);
    r = _mm_mul_pd(r, _mm_set1_pd(in3_idx_1));
    r1 = _mm_add_pd(r1, r);
    r = _mm_loadu_pd(&in2_data[i + 18]);
    r = _mm_mul_pd(r, _mm_set1_pd(in3_idx_2));
    r = _mm_add_pd(r1, r);
    r1 = _mm_loadu_pd(&in1->pState[i]);
    r = _mm_add_pd(r1, r);
    _mm_storeu_pd(&in1->pState[i], r);
  }
  in1->pState[8] += (in2_data[8] * in3_idx_0 + in2_data[17] * in3_idx_1) +
                    in2_data[26] * in3_idx_2;
}

void c_KalmanFilter_set_MeasurementM(const emlrtStack *sp, trackingKF *obj,
                                     const real_T MeasurementModelMatrix[27])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  real_T n;
  int32_T b_iv[2];
  int32_T iv1[2];
  int32_T k;
  boolean_T x[2];
  boolean_T exitg1;
  boolean_T p;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  st.site = &sb_emlrtRSI;
  b_st.site = &nc_emlrtRSI;
  c_st.site = &oc_emlrtRSI;
  d_st.site = &pc_emlrtRSI;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 27)) {
    if ((!muDoubleScalarIsInf(MeasurementModelMatrix[k])) &&
        (!muDoubleScalarIsNaN(MeasurementModelMatrix[k]))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    emlrtErrorWithMessageIdR2018a(
        &d_st, &f_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 16, "MeasurementModel");
  }
  x[0] = (obj->pN == 3.0);
  x[1] = true;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 1)) {
    if (!x[k]) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!p) {
    emlrtErrorWithMessageIdR2018a(
        &st, &emlrtRTEI,
        "shared_tracking:KalmanFilter:nonmatchingMeasurementState",
        "shared_tracking:KalmanFilter:nonmatchingMeasurementState", 7, 4, 16,
        "MeasurementModel", 6, obj->pN, 6, 9.0);
  }
  n = obj->pN;
  if (!(n <= 3.0)) {
    emlrtErrorWithMessageIdR2018a(sp, &e_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  if (!(n >= 3.0)) {
    emlrtErrorWithMessageIdR2018a(sp, &d_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  b_iv[0] = 3;
  iv1[0] = 3;
  b_iv[1] = 9;
  iv1[1] = 9;
  emlrtSubAssignSizeCheckR2012b(&b_iv[0], 2, &iv1[0], 2, &b_emlrtECI,
                                (emlrtCTX)sp);
  memcpy(&obj->pMeasurementModel[0], &MeasurementModelMatrix[0],
         27U * sizeof(real_T));
}

void plus(real_T in1_data[], int32_T in1_size[2], const real_T in2_data[],
          const int32_T in2_size[2])
{
  real_T b_in1_data[9];
  int32_T aux_0_1;
  int32_T aux_1_1;
  int32_T b_loop_ub;
  int32_T i;
  int32_T i1;
  int32_T loop_ub;
  int32_T stride_0_0;
  int32_T stride_0_1;
  int32_T stride_1_0;
  int32_T stride_1_1;
  if (in2_size[0] == 1) {
    loop_ub = in1_size[0];
  } else {
    loop_ub = in2_size[0];
  }
  if (in2_size[1] == 1) {
    b_loop_ub = in1_size[1];
  } else {
    b_loop_ub = in2_size[1];
  }
  stride_0_0 = (in1_size[0] != 1);
  stride_0_1 = (in1_size[1] != 1);
  stride_1_0 = (in2_size[0] != 1);
  stride_1_1 = (in2_size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in1_data[i1 + loop_ub * i] =
          in1_data[i1 * stride_0_0 + in1_size[0] * aux_0_1] +
          in2_data[i1 * stride_1_0 + in2_size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  in1_size[0] = loop_ub;
  in1_size[1] = b_loop_ub;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      stride_0_0 = loop_ub * i;
      in1_data[i1 + stride_0_0] = b_in1_data[i1 + stride_0_0];
    }
  }
}
