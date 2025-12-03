#include "trackingKF.h"
#include "KalmanFilter.h"
#include "codegenTest_float_mex_data.h"
#include "codegenTest_float_mex_internal_types.h"
#include "mrdivide_helper.h"
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include "mwmathutil.h"
#include <emmintrin.h>
#include <stddef.h>
#include <string.h>

static emlrtRSInfo ig_emlrtRSI = {307, "trackingKF/predict",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\shared\\trac"
                                  "king\\fusionlib\\trackingKF.m"};

static emlrtRSInfo jg_emlrtRSI = {314, "trackingKF/predict",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\shared\\trac"
                                  "king\\fusionlib\\trackingKF.m"};

static emlrtRSInfo kg_emlrtRSI = {319, "trackingKF/predict",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\shared\\trac"
                                  "king\\fusionlib\\trackingKF.m"};

static emlrtRSInfo lg_emlrtRSI = {321, "trackingKF/predict",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\shared\\trac"
                                  "king\\fusionlib\\trackingKF.m"};

static emlrtRSInfo mg_emlrtRSI = {
    154, "AbstractSmoother/setupInitialDistributions",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\AbstractSmoother.m"};

static emlrtRSInfo ng_emlrtRSI = {
    77, "KFSmoother/ensureMethodDefinition",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\KFSmoother.m"};

static emlrtRSInfo og_emlrtRSI = {
    78, "KFSmoother/ensureMethodDefinition",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\KFSmoother.m"};

static emlrtRSInfo pg_emlrtRSI = {
    84, "KFSmoother/ensureSmootherStateSizeIsDefined",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\KFSmoother.m"};

static emlrtRSInfo qg_emlrtRSI = {
    116, "trackingKFMotionModelUtilities/predictionMatrices",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\trackingK"
    "FMotionModelUtilities.m"};

static emlrtRSInfo rg_emlrtRSI = {
    21, "constAccelerationModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\constAcce"
    "lerationModel.m"};

static emlrtRSInfo sg_emlrtRSI = {
    22, "constAccelerationModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\constAcce"
    "lerationModel.m"};

static emlrtRSInfo tg_emlrtRSI = {
    23, "constAccelerationModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\constAcce"
    "lerationModel.m"};

static emlrtRSInfo ug_emlrtRSI = {
    208, "KalmanFilter/predict",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo vg_emlrtRSI = {
    223, "KalmanFilter/predict",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo wg_emlrtRSI = {
    742, "KalmanFilter/parseInputsToPredict",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo xg_emlrtRSI = {
    747, "KalmanFilter/parseInputsToPredict",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo yg_emlrtRSI = {1009,
                                  "trackingKF/validateStateTransitionModel",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\shared\\trac"
                                  "king\\fusionlib\\trackingKF.m"};

static emlrtRSInfo ah_emlrtRSI = {
    619, "KalmanFilter/validateStateTransitionModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo bh_emlrtRSI = {
    504, "KalmanFilter/set.ProcessNoiseModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo ch_emlrtRSI = {94, "eml_mtimes_helper",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\ma"
                                  "tlab\\ops\\eml_mtimes_helper.m"};

static emlrtRSInfo dh_emlrtRSI = {142, "mtimes",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+blas\\mtimes.m"};

static emlrtRSInfo eh_emlrtRSI = {177, "mtimes_blas",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+blas\\mtimes.m"};

static emlrtRSInfo fh_emlrtRSI = {377, "trackingKF/correct",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\shared\\trac"
                                  "king\\fusionlib\\trackingKF.m"};

static emlrtRSInfo gh_emlrtRSI = {381, "trackingKF/correct",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\shared\\trac"
                                  "king\\fusionlib\\trackingKF.m"};

static emlrtRSInfo hh_emlrtRSI = {
    269, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo ih_emlrtRSI = {
    277, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo jh_emlrtRSI = {
    283, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo kh_emlrtRSI = {
    284, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo lh_emlrtRSI = {
    288, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo mh_emlrtRSI = {
    289, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo nh_emlrtRSI = {
    291, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo oh_emlrtRSI = {
    14, "validateInputSizeAndType",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\validateInputSiz"
    "eAndType.m"};

static emlrtRSInfo ph_emlrtRSI = {20, "mrdivide_helper",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\mrdivide_helper.m"};

static emlrtRSInfo fj_emlrtRSI = {69, "eml_mtimes_helper",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\ma"
                                  "tlab\\ops\\eml_mtimes_helper.m"};

static emlrtRTEInfo k_emlrtRTEI = {
    14, 37, "validatenonnegative",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "valattr\\validatenonnegative.m"};

static emlrtDCInfo emlrtDCI = {
    489, 45, "KalmanFilter/get.MeasurementModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m",
    1};

static emlrtBCInfo emlrtBCI = {
    1,
    3,
    489,
    45,
    "",
    "KalmanFilter/get.MeasurementModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m",
    0};

static emlrtRTEInfo l_emlrtRTEI = {1012, 20,
                                   "trackingKF/validateStateTransitionModel",
                                   "C:\\Program "
                                   "Files\\MATLAB\\R2025b\\toolbox\\shared\\tra"
                                   "cking\\fusionlib\\trackingKF.m"};

static emlrtECInfo c_emlrtECI = {
    1, 283, 34, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtECInfo d_emlrtECI = {
    2, 283, 34, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtECInfo e_emlrtECI = {
    1, 289, 34, "KalmanFilter/correct",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRTEInfo m_emlrtRTEI = {16, 19, "mrdivide_helper",
                                   "C:\\Program "
                                   "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                   "coder\\+internal\\mrdivide_helper.m"};

static emlrtDCInfo b_emlrtDCI = {
    453, 45, "KalmanFilter/get.MeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m",
    1};

static emlrtBCInfo b_emlrtBCI = {
    1,
    3,
    453,
    45,
    "",
    "KalmanFilter/get.MeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m",
    0};

static emlrtDCInfo c_emlrtDCI = {
    453, 54, "KalmanFilter/get.MeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m",
    1};

static emlrtBCInfo c_emlrtBCI = {
    1,
    3,
    453,
    54,
    "",
    "KalmanFilter/get.MeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m",
    0};

static emlrtRTEInfo n_emlrtRTEI = {138, 23, "dynamic_size_checks",
                                   "C:\\Program "
                                   "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\m"
                                   "atlab\\ops\\eml_mtimes_helper.m"};

static emlrtRTEInfo o_emlrtRTEI = {
    10, 23, "validatenumel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "valattr\\validatenumel.m"};

static emlrtRTEInfo p_emlrtRTEI = {
    18, 23, "validatenumel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "valattr\\validatenumel.m"};

void trackingKF_correct(const emlrtStack *sp, trackingKF *KF, const real_T z[3])
{
  __m128d r;
  __m128d r1;
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  real_T P_corr[81];
  real_T y[81];
  real_T a_data[27];
  real_T b_data[27];
  real_T gain_numerator_data[27];
  real_T y_data[27];
  real_T residualCovariance_data[9];
  real_T tmp_data[9];
  real_T b_tmp_data[3];
  real_T b_z[3];
  real_T alpha1;
  real_T beta1;
  int32_T gain_numerator_size[2];
  int32_T residualCovariance_size[2];
  int32_T tmp_size[2];
  int32_T i;
  int32_T i1;
  int32_T k;
  int32_T loop_ub;
  char_T TRANSA1;
  char_T TRANSB1;
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
  st.site = &fh_emlrtRSI;
  b_st.site = &hh_emlrtRSI;
  alpha1 = KF->pN;
  c_st.site = &oh_emlrtRSI;
  d_st.site = &pc_emlrtRSI;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3)) {
    if ((!muDoubleScalarIsInf(z[k])) && (!muDoubleScalarIsNaN(z[k]))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    emlrtErrorWithMessageIdR2018a(
        &d_st, &f_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 1, "z");
  }
  d_st.site = &pc_emlrtRSI;
  if ((!(muDoubleScalarFloor(alpha1) == alpha1)) ||
      muDoubleScalarIsInf(alpha1) || (!(alpha1 >= 0.0))) {
    emlrtErrorWithMessageIdR2018a(&d_st, &o_emlrtRTEI,
                                  "Coder:toolbox:ValidateattributesBadNumel",
                                  "MATLAB:validateattributes:badnumel", 0);
  }
  if (!(alpha1 == 3.0)) {
    emlrtErrorWithMessageIdR2018a(
        &d_st, &p_emlrtRTEI, "Coder:toolbox:ValidateattributesincorrectNumel",
        "MATLAB:KalmanFilter:incorrectNumel", 5, 4, 1, "z", 6, alpha1);
  }
  b_st.site = &ih_emlrtRSI;
  if (KF->pN < 3.0) {
    if (alpha1 < 1.0) {
      loop_ub = 0;
    } else {
      if (alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
        emlrtIntegerCheckR2012b(alpha1, &emlrtDCI, &b_st);
      }
      if (((int32_T)alpha1 < 1) || ((int32_T)alpha1 > 3)) {
        emlrtDynamicBoundsCheckR2012b((int32_T)alpha1, 1, 3, &emlrtBCI, &b_st);
      }
      loop_ub = (int32_T)alpha1;
    }
    for (i = 0; i < 9; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_data[i1 + loop_ub * i] = KF->pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    loop_ub = 3;
    memcpy(&b_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real_T));
  }
  b_st.site = &ih_emlrtRSI;
  c_st.site = &ch_emlrtRSI;
  if (loop_ub == 0) {
    gain_numerator_size[0] = 9;
    gain_numerator_size[1] = 0;
  } else {
    TRANSB1 = 'T';
    TRANSA1 = 'N';
    alpha1 = 1.0;
    beta1 = 0.0;
    m_t = (ptrdiff_t)9;
    n_t = (ptrdiff_t)loop_ub;
    k_t = (ptrdiff_t)9;
    lda_t = (ptrdiff_t)9;
    ldb_t = (ptrdiff_t)loop_ub;
    ldc_t = (ptrdiff_t)9;
    gain_numerator_size[0] = 9;
    gain_numerator_size[1] = loop_ub;
    dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1,
          &KF->pStateCovariance[0], &lda_t, &b_data[0], &ldb_t, &beta1,
          &gain_numerator_data[0], &ldc_t);
  }
  b_st.site = &kh_emlrtRSI;
  if (KF->pN < 3.0) {
    alpha1 = KF->pN;
    if (alpha1 < 1.0) {
      loop_ub = 0;
    } else {
      if (alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
        emlrtIntegerCheckR2012b(alpha1, &emlrtDCI, &b_st);
      }
      if (((int32_T)alpha1 < 1) || ((int32_T)alpha1 > 3)) {
        emlrtDynamicBoundsCheckR2012b((int32_T)alpha1, 1, 3, &emlrtBCI, &b_st);
      }
      loop_ub = (int32_T)alpha1;
    }
    for (i = 0; i < 9; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_data[i1 + loop_ub * i] = KF->pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    loop_ub = 3;
    memcpy(&b_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real_T));
  }
  b_st.site = &jh_emlrtRSI;
  c_st.site = &jh_emlrtRSI;
  if (KF->pN < 3.0) {
    alpha1 = KF->pN;
    if (alpha1 < 1.0) {
      k = 0;
    } else {
      if (alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
        emlrtIntegerCheckR2012b(alpha1, &emlrtDCI, &c_st);
      }
      if (((int32_T)alpha1 < 1) || ((int32_T)alpha1 > 3)) {
        emlrtDynamicBoundsCheckR2012b((int32_T)alpha1, 1, 3, &emlrtBCI, &c_st);
      }
      k = (int32_T)alpha1;
    }
    for (i = 0; i < 9; i++) {
      for (i1 = 0; i1 < k; i1++) {
        a_data[i1 + k * i] = KF->pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    k = 3;
    memcpy(&a_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real_T));
  }
  c_st.site = &ch_emlrtRSI;
  if (k == 0) {
    k = 0;
  } else {
    TRANSB1 = 'N';
    TRANSA1 = 'N';
    alpha1 = 1.0;
    beta1 = 0.0;
    m_t = (ptrdiff_t)k;
    n_t = (ptrdiff_t)9;
    k_t = (ptrdiff_t)9;
    lda_t = (ptrdiff_t)k;
    ldb_t = (ptrdiff_t)9;
    ldc_t = (ptrdiff_t)k;
    dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &a_data[0], &lda_t,
          &KF->pStateCovariance[0], &ldb_t, &beta1, &y_data[0], &ldc_t);
  }
  b_st.site = &jh_emlrtRSI;
  c_st.site = &ch_emlrtRSI;
  if ((k == 0) || (loop_ub == 0)) {
    residualCovariance_size[0] = k;
    residualCovariance_size[1] = loop_ub;
    k *= loop_ub;
    if (k - 1 >= 0) {
      memset(&residualCovariance_data[0], 0, (uint32_T)k * sizeof(real_T));
    }
  } else {
    TRANSB1 = 'T';
    TRANSA1 = 'N';
    alpha1 = 1.0;
    beta1 = 0.0;
    m_t = (ptrdiff_t)k;
    n_t = (ptrdiff_t)loop_ub;
    k_t = (ptrdiff_t)9;
    lda_t = (ptrdiff_t)k;
    ldb_t = (ptrdiff_t)loop_ub;
    ldc_t = (ptrdiff_t)k;
    residualCovariance_size[0] = k;
    residualCovariance_size[1] = loop_ub;
    dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &y_data[0], &lda_t,
          &b_data[0], &ldb_t, &beta1, &residualCovariance_data[0], &ldc_t);
  }
  b_st.site = &kh_emlrtRSI;
  if (KF->pV < 3.0) {
    alpha1 = KF->pV;
    if (alpha1 < 1.0) {
      k = 0;
    } else {
      if (alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
        emlrtIntegerCheckR2012b(alpha1, &b_emlrtDCI, &b_st);
      }
      if (((int32_T)alpha1 < 1) || ((int32_T)alpha1 > 3)) {
        emlrtDynamicBoundsCheckR2012b((int32_T)alpha1, 1, 3, &b_emlrtBCI,
                                      &b_st);
      }
      k = (int32_T)alpha1;
    }
    if (alpha1 < 1.0) {
      loop_ub = 0;
    } else {
      if (alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
        emlrtIntegerCheckR2012b(alpha1, &c_emlrtDCI, &b_st);
      }
      if (((int32_T)alpha1 < 1) || ((int32_T)alpha1 > 3)) {
        emlrtDynamicBoundsCheckR2012b((int32_T)alpha1, 1, 3, &c_emlrtBCI,
                                      &b_st);
      }
      loop_ub = (int32_T)alpha1;
    }
    tmp_size[0] = k;
    tmp_size[1] = loop_ub;
    for (i = 0; i < loop_ub; i++) {
      for (i1 = 0; i1 < k; i1++) {
        tmp_data[i1 + k * i] = KF->pMeasurementNoise[i1 + 3 * i];
      }
    }
  } else {
    tmp_size[0] = 3;
    tmp_size[1] = 3;
    memcpy(&tmp_data[0], &KF->pMeasurementNoise[0], 9U * sizeof(real_T));
  }
  if ((residualCovariance_size[0] != tmp_size[0]) &&
      ((residualCovariance_size[0] != 1) && (tmp_size[0] != 1))) {
    emlrtDimSizeImpxCheckR2021b(residualCovariance_size[0], tmp_size[0],
                                &c_emlrtECI, &st);
  }
  if ((residualCovariance_size[1] != tmp_size[1]) &&
      ((residualCovariance_size[1] != 1) && (tmp_size[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(residualCovariance_size[1], tmp_size[1],
                                &d_emlrtECI, &st);
  }
  if ((residualCovariance_size[0] == tmp_size[0]) &&
      (residualCovariance_size[1] == tmp_size[1])) {
    int32_T vectorUB;
    k = residualCovariance_size[0] * residualCovariance_size[1];
    loop_ub = (k / 2) << 1;
    vectorUB = loop_ub - 2;
    for (i = 0; i <= vectorUB; i += 2) {
      r = _mm_loadu_pd(&residualCovariance_data[i]);
      r1 = _mm_loadu_pd(&tmp_data[i]);
      _mm_storeu_pd(&residualCovariance_data[i], _mm_add_pd(r, r1));
    }
    for (i = loop_ub; i < k; i++) {
      residualCovariance_data[i] += tmp_data[i];
    }
  } else {
    plus(residualCovariance_data, residualCovariance_size, tmp_data, tmp_size);
  }
  b_st.site = &lh_emlrtRSI;
  if (residualCovariance_size[1] != gain_numerator_size[1]) {
    emlrtErrorWithMessageIdR2018a(&b_st, &m_emlrtRTEI, "MATLAB:dimagree",
                                  "MATLAB:dimagree", 0);
  }
  c_st.site = &ph_emlrtRSI;
  mrdiv(&c_st, gain_numerator_data, gain_numerator_size,
        residualCovariance_data, residualCovariance_size);
  b_st.site = &mh_emlrtRSI;
  c_st.site = &mh_emlrtRSI;
  if (KF->pN < 3.0) {
    alpha1 = KF->pN;
    if (alpha1 < 1.0) {
      k = 0;
    } else {
      if (alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
        emlrtIntegerCheckR2012b(alpha1, &emlrtDCI, &c_st);
      }
      if (((int32_T)alpha1 < 1) || ((int32_T)alpha1 > 3)) {
        emlrtDynamicBoundsCheckR2012b((int32_T)alpha1, 1, 3, &emlrtBCI, &c_st);
      }
      k = (int32_T)alpha1;
    }
    for (i = 0; i < 9; i++) {
      for (i1 = 0; i1 < k; i1++) {
        a_data[i1 + k * i] = KF->pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    k = 3;
    memcpy(&a_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real_T));
  }
  c_st.site = &ch_emlrtRSI;
  if (k == 0) {
    k = 0;
  } else {
    TRANSB1 = 'N';
    TRANSA1 = 'N';
    alpha1 = 1.0;
    beta1 = 0.0;
    m_t = (ptrdiff_t)k;
    n_t = (ptrdiff_t)1;
    k_t = (ptrdiff_t)9;
    lda_t = (ptrdiff_t)k;
    ldb_t = (ptrdiff_t)9;
    ldc_t = (ptrdiff_t)k;
    dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &a_data[0], &lda_t,
          &KF->pState[0], &ldb_t, &beta1, &b_tmp_data[0], &ldc_t);
  }
  if ((k != 3) && (k != 1)) {
    emlrtDimSizeImpxCheckR2021b(3, k, &e_emlrtECI, &st);
  }
  b_st.site = &mh_emlrtRSI;
  c_st.site = &fj_emlrtRSI;
  if (gain_numerator_size[1] != 3) {
    emlrtErrorWithMessageIdR2018a(&c_st, &n_emlrtRTEI, "MATLAB:innerdim",
                                  "MATLAB:innerdim", 0);
  }
  b_st.site = &nh_emlrtRSI;
  c_st.site = &nh_emlrtRSI;
  if (KF->pN < 3.0) {
    alpha1 = KF->pN;
    if (alpha1 < 1.0) {
      loop_ub = 0;
    } else {
      if (alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
        emlrtIntegerCheckR2012b(alpha1, &emlrtDCI, &c_st);
      }
      if (((int32_T)alpha1 < 1) || ((int32_T)alpha1 > 3)) {
        emlrtDynamicBoundsCheckR2012b((int32_T)alpha1, 1, 3, &emlrtBCI, &c_st);
      }
      loop_ub = (int32_T)alpha1;
    }
    for (i = 0; i < 9; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_data[i1 + loop_ub * i] = KF->pMeasurementModel[i1 + 3 * i];
      }
    }
  } else {
    loop_ub = 3;
    memcpy(&b_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real_T));
  }
  c_st.site = &fj_emlrtRSI;
  if (loop_ub != 3) {
    emlrtErrorWithMessageIdR2018a(&c_st, &n_emlrtRTEI, "MATLAB:innerdim",
                                  "MATLAB:innerdim", 0);
  }
  c_st.site = &ch_emlrtRSI;
  TRANSB1 = 'N';
  TRANSA1 = 'N';
  alpha1 = 1.0;
  beta1 = 0.0;
  m_t = (ptrdiff_t)9;
  n_t = (ptrdiff_t)9;
  k_t = (ptrdiff_t)3;
  lda_t = (ptrdiff_t)9;
  ldb_t = (ptrdiff_t)3;
  ldc_t = (ptrdiff_t)9;
  dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &gain_numerator_data[0],
        &lda_t, &b_data[0], &ldb_t, &beta1, &y[0], &ldc_t);
  b_st.site = &nh_emlrtRSI;
  c_st.site = &ch_emlrtRSI;
  mtimes(y, KF->pStateCovariance, P_corr);
  for (i = 0; i <= 78; i += 2) {
    r = _mm_loadu_pd(&KF->pStateCovariance[i]);
    r1 = _mm_loadu_pd(&P_corr[i]);
    r = _mm_sub_pd(r, r1);
    _mm_storeu_pd(&P_corr[i], r);
  }
  P_corr[80] = KF->pStateCovariance[80] - P_corr[80];
  if (k == 3) {
    real_T d;
    r = _mm_loadu_pd(&b_tmp_data[0]);
    _mm_storeu_pd(&b_z[0], _mm_sub_pd(_mm_loadu_pd(&z[0]), r));
    alpha1 = b_z[0];
    beta1 = b_z[1];
    d = z[2] - b_tmp_data[2];
    for (i = 0; i <= 6; i += 2) {
      r = _mm_loadu_pd(&gain_numerator_data[i]);
      r1 = _mm_mul_pd(r, _mm_set1_pd(alpha1));
      r = _mm_loadu_pd(&gain_numerator_data[i + 9]);
      r = _mm_mul_pd(r, _mm_set1_pd(beta1));
      r1 = _mm_add_pd(r1, r);
      r = _mm_loadu_pd(&gain_numerator_data[i + 18]);
      r = _mm_mul_pd(r, _mm_set1_pd(d));
      r = _mm_add_pd(r1, r);
      r1 = _mm_loadu_pd(&KF->pState[i]);
      r = _mm_add_pd(r1, r);
      _mm_storeu_pd(&KF->pState[i], r);
    }
    KF->pState[8] +=
        (gain_numerator_data[8] * alpha1 + gain_numerator_data[17] * beta1) +
        gain_numerator_data[26] * d;
  } else {
    binary_expand_op(KF, gain_numerator_data, z, b_tmp_data, &k);
  }
  for (i = 0; i < 9; i++) {
    for (i1 = 0; i1 < 9; i1++) {
      k = i1 + 9 * i;
      KF->pStateCovariance[k] = (P_corr[k] + P_corr[i + 9 * i1]) * 0.5;
    }
  }
  st.site = &gh_emlrtRSI;
  if (!KF->pIsInitialized) {
    KF->pIsDistributionsSetup = true;
  }
}

void trackingKF_predict(const emlrtStack *sp, trackingKF *KF, real_T varargin_1)
{
  __m128d r;
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack st;
  real_T P[81];
  real_T y[81];
  real_T b_KF[27];
  real_T A1dim[9];
  real_T alpha1;
  real_T beta1;
  int32_T KF_tmp;
  int32_T b_j1;
  int32_T b_kidx;
  int32_T i;
  int32_T j2;
  int32_T kidx;
  char_T TRANSA1;
  char_T TRANSB1;
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
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  h_st.prev = &g_st;
  h_st.tls = g_st.tls;
  st.site = &ig_emlrtRSI;
  b_st.site = &mg_emlrtRSI;
  c_st.site = &ng_emlrtRSI;
  if (!KF->pIsSmootherStateSizeInitialized) {
    d_st.site = &pg_emlrtRSI;
    if (KF->pN < 3.0) {
      alpha1 = KF->pN;
      if (!(alpha1 < 1.0)) {
        if (alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
          emlrtIntegerCheckR2012b(alpha1, &emlrtDCI, &d_st);
        }
        if (((int32_T)alpha1 < 1) || ((int32_T)alpha1 > 3)) {
          emlrtDynamicBoundsCheckR2012b((int32_T)alpha1, 1, 3, &emlrtBCI,
                                        &d_st);
        }
      }
    }
    KF->pIsSmootherStateSizeInitialized = true;
  }
  c_st.site = &og_emlrtRSI;
  if (!KF->IsLastJacobianInitialized) {
    KF->IsLastJacobianInitialized = true;
  }
  if (!KF->pIsDistributionsSetup) {
    KF->pIsDistributionsSetup = true;
  }
  st.site = &jg_emlrtRSI;
  b_st.site = &pc_emlrtRSI;
  if (muDoubleScalarIsInf(varargin_1) || muDoubleScalarIsNaN(varargin_1)) {
    emlrtErrorWithMessageIdR2018a(
        &b_st, &f_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:trackingKF:expectedFinite", 3, 4, 2, "dt");
  }
  b_st.site = &pc_emlrtRSI;
  if (varargin_1 < 0.0) {
    emlrtErrorWithMessageIdR2018a(
        &b_st, &k_emlrtRTEI,
        "Coder:toolbox:ValidateattributesexpectedNonnegative",
        "MATLAB:trackingKF:expectedNonnegative", 3, 4, 2, "dt");
  }
  st.site = &kg_emlrtRSI;
  b_st.site = &qg_emlrtRSI;
  c_st.site = &rg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  A1dim[0] = 1.0;
  A1dim[3] = varargin_1;
  alpha1 = varargin_1 * varargin_1 / 2.0;
  A1dim[6] = alpha1;
  A1dim[1] = 0.0;
  A1dim[4] = 1.0;
  A1dim[7] = varargin_1;
  A1dim[2] = 0.0;
  A1dim[5] = 0.0;
  A1dim[8] = 1.0;
  c_st.site = &sg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &sg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &sg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &sg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &sg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &sg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &tg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  kidx = -1;
  b_kidx = -1;
  for (b_j1 = 0; b_j1 < 3; b_j1++) {
    int32_T i1;
    i = iv[3 * b_j1];
    KF_tmp = iv[3 * b_j1 + 1];
    i1 = iv[3 * b_j1 + 2];
    for (j2 = 0; j2 < 3; j2++) {
      int32_T i2;
      r = _mm_loadu_pd(&A1dim[3 * j2]);
      _mm_storeu_pd(&P[kidx + 1], _mm_mul_pd(_mm_set1_pd(i), r));
      beta1 = A1dim[3 * j2 + 2];
      P[kidx + 3] = (real_T)i * beta1;
      kidx += 3;
      i2 = iv[j2 + 3 * b_j1];
      KF->ProcessNoiseModel[b_kidx + 1] = (real_T)i2 * alpha1;
      _mm_storeu_pd(&P[kidx + 1], _mm_mul_pd(_mm_set1_pd(KF_tmp), r));
      P[kidx + 3] = (real_T)KF_tmp * beta1;
      kidx += 3;
      KF->ProcessNoiseModel[b_kidx + 2] = (real_T)i2 * varargin_1;
      _mm_storeu_pd(&P[kidx + 1], _mm_mul_pd(_mm_set1_pd(i1), r));
      P[kidx + 3] = (real_T)i1 * beta1;
      kidx += 3;
      KF->ProcessNoiseModel[b_kidx + 3] = i2;
      b_kidx += 3;
    }
  }
  KF->pIsStateTransitionLocked = false;
  st.site = &lg_emlrtRSI;
  b_st.site = &ug_emlrtRSI;
  c_st.site = &wg_emlrtRSI;
  d_st.site = &db_emlrtRSI;
  e_st.site = &yg_emlrtRSI;
  f_st.site = &ah_emlrtRSI;
  g_st.site = &oc_emlrtRSI;
  h_st.site = &pc_emlrtRSI;
  p = true;
  kidx = 0;
  exitg1 = false;
  while ((!exitg1) && (kidx < 81)) {
    if ((!muDoubleScalarIsInf(P[kidx])) && (!muDoubleScalarIsNaN(P[kidx]))) {
      kidx++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    emlrtErrorWithMessageIdR2018a(
        &h_st, &f_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 20, "StateTransitionModel");
  }
  if (KF->pIsStateTransitionLocked) {
    emlrtErrorWithMessageIdR2018a(
        &d_st, &l_emlrtRTEI, "shared_tracking:KalmanFilter:setMotionModel",
        "shared_tracking:KalmanFilter:setMotionModel", 6, 4, 20,
        "StateTransitionModel", 4, 11, "MotionModel");
  }
  memcpy(&KF->StateTransitionModel[0], &P[0], 81U * sizeof(real_T));
  c_st.site = &xg_emlrtRSI;
  d_st.site = &bh_emlrtRSI;
  e_st.site = &pc_emlrtRSI;
  p = true;
  kidx = 0;
  exitg1 = false;
  while ((!exitg1) && (kidx < 27)) {
    if ((!muDoubleScalarIsInf(KF->ProcessNoiseModel[kidx])) &&
        (!muDoubleScalarIsNaN(KF->ProcessNoiseModel[kidx]))) {
      kidx++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    emlrtErrorWithMessageIdR2018a(
        &e_st, &f_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 17, "ProcessNoiseModel");
  }
  b_st.site = &vg_emlrtRSI;
  c_st.site = &ch_emlrtRSI;
  mtimes(KF->StateTransitionModel, KF->pStateCovariance, P);
  b_st.site = &vg_emlrtRSI;
  c_st.site = &ch_emlrtRSI;
  d_st.site = &dh_emlrtRSI;
  e_st.site = &eh_emlrtRSI;
  TRANSB1 = 'T';
  TRANSA1 = 'N';
  alpha1 = 1.0;
  beta1 = 0.0;
  m_t = (ptrdiff_t)9;
  n_t = (ptrdiff_t)9;
  k_t = (ptrdiff_t)9;
  lda_t = (ptrdiff_t)9;
  ldb_t = (ptrdiff_t)9;
  ldc_t = (ptrdiff_t)9;
  dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &P[0], &lda_t,
        &KF->StateTransitionModel[0], &ldb_t, &beta1, &y[0], &ldc_t);
  memset(&b_KF[0], 0, 27U * sizeof(real_T));
  for (b_j1 = 0; b_j1 < 3; b_j1++) {
    kidx = 9 * b_j1 + 2;
    b_kidx = 9 * b_j1 + 4;
    i = 9 * b_j1 + 6;
    KF_tmp = 9 * b_j1 + 8;
    for (j2 = 0; j2 < 3; j2++) {
      __m128d r1;
      __m128d r2;
      alpha1 = KF->pProcessNoise[j2 + 3 * b_j1];
      r = _mm_loadu_pd(&KF->ProcessNoiseModel[9 * j2]);
      r1 = _mm_loadu_pd(&b_KF[9 * b_j1]);
      r2 = _mm_set1_pd(alpha1);
      _mm_storeu_pd(&b_KF[9 * b_j1], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
      r = _mm_loadu_pd(&KF->ProcessNoiseModel[9 * j2 + 2]);
      r1 = _mm_loadu_pd(&b_KF[kidx]);
      _mm_storeu_pd(&b_KF[kidx], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
      r = _mm_loadu_pd(&KF->ProcessNoiseModel[9 * j2 + 4]);
      r1 = _mm_loadu_pd(&b_KF[b_kidx]);
      _mm_storeu_pd(&b_KF[b_kidx], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
      r = _mm_loadu_pd(&KF->ProcessNoiseModel[9 * j2 + 6]);
      r1 = _mm_loadu_pd(&b_KF[i]);
      _mm_storeu_pd(&b_KF[i], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
      b_KF[KF_tmp] += KF->ProcessNoiseModel[9 * j2 + 8] * alpha1;
    }
  }
  memset(&A1dim[0], 0, 9U * sizeof(real_T));
  for (b_j1 = 0; b_j1 < 9; b_j1++) {
    real_T d;
    real_T d1;
    alpha1 = KF->pState[b_j1];
    beta1 = b_KF[b_j1];
    d = b_KF[b_j1 + 9];
    d1 = b_KF[b_j1 + 18];
    for (j2 = 0; j2 < 9; j2++) {
      kidx = b_j1 + 9 * j2;
      P[kidx] = y[kidx] + ((beta1 * KF->ProcessNoiseModel[j2] +
                            d * KF->ProcessNoiseModel[j2 + 9]) +
                           d1 * KF->ProcessNoiseModel[j2 + 18]);
      A1dim[j2] += KF->StateTransitionModel[j2 + 9 * b_j1] * alpha1;
    }
  }
  for (b_j1 = 0; b_j1 < 9; b_j1++) {
    KF->pState[b_j1] = A1dim[b_j1];
    for (j2 = 0; j2 < 9; j2++) {
      kidx = j2 + 9 * b_j1;
      KF->pStateCovariance[kidx] = (P[kidx] + P[b_j1 + 9 * j2]) * 0.5;
    }
  }
  KF->pIsStateTransitionLocked = true;
}
