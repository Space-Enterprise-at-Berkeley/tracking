/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * trackingKF.c
 *
 * Code generation for function 'trackingKF'
 *
 */

/* Include files */
#include "trackingKF.h"
#include "KalmanFilter.h"
#include "codegenTest_data.h"
#include "codegenTest_internal_types.h"
#include "mrdivide_helper.h"
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>
#include <xmmintrin.h>

/* Variable Definitions */
static emlrtRSInfo ng_emlrtRSI =
    {
        307,                  /* lineNo */
        "trackingKF/predict", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo og_emlrtRSI =
    {
        314,                  /* lineNo */
        "trackingKF/predict", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo pg_emlrtRSI =
    {
        319,                  /* lineNo */
        "trackingKF/predict", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo qg_emlrtRSI =
    {
        321,                  /* lineNo */
        "trackingKF/predict", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo rg_emlrtRSI = {
    154,                                          /* lineNo */
    "AbstractSmoother/setupInitialDistributions", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\AbstractSmoother.m" /* pathName */
};

static emlrtRSInfo sg_emlrtRSI = {
    77,                                  /* lineNo */
    "KFSmoother/ensureMethodDefinition", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\KFSmoother.m" /* pathName */
};

static emlrtRSInfo tg_emlrtRSI = {
    78,                                  /* lineNo */
    "KFSmoother/ensureMethodDefinition", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\KFSmoother.m" /* pathName */
};

static emlrtRSInfo ug_emlrtRSI = {
    84,                                            /* lineNo */
    "KFSmoother/ensureSmootherStateSizeIsDefined", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\KFSmoother.m" /* pathName */
};

static emlrtRSInfo vg_emlrtRSI = {
    116,                                                 /* lineNo */
    "trackingKFMotionModelUtilities/predictionMatrices", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\trackingK"
    "FMotionModelUtilities.m" /* pathName */
};

static emlrtRSInfo wg_emlrtRSI = {
    21,                       /* lineNo */
    "constAccelerationModel", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\constAcce"
    "lerationModel.m" /* pathName */
};

static emlrtRSInfo xg_emlrtRSI = {
    22,                       /* lineNo */
    "constAccelerationModel", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\constAcce"
    "lerationModel.m" /* pathName */
};

static emlrtRSInfo yg_emlrtRSI = {
    23,                       /* lineNo */
    "constAccelerationModel", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\constAcce"
    "lerationModel.m" /* pathName */
};

static emlrtRSInfo ah_emlrtRSI = {
    208,                    /* lineNo */
    "KalmanFilter/predict", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo bh_emlrtRSI = {
    223,                    /* lineNo */
    "KalmanFilter/predict", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo ch_emlrtRSI = {
    742,                                 /* lineNo */
    "KalmanFilter/parseInputsToPredict", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo dh_emlrtRSI = {
    747,                                 /* lineNo */
    "KalmanFilter/parseInputsToPredict", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo eh_emlrtRSI =
    {
        1009,                                      /* lineNo */
        "trackingKF/validateStateTransitionModel", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo fh_emlrtRSI = {
    619,                                         /* lineNo */
    "KalmanFilter/validateStateTransitionModel", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo gh_emlrtRSI = {
    504,                                  /* lineNo */
    "KalmanFilter/set.ProcessNoiseModel", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo hh_emlrtRSI =
    {
        94,                  /* lineNo */
        "eml_mtimes_helper", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_"
        "helper.m" /* pathName */
};

static emlrtRSInfo ih_emlrtRSI = {
    142,      /* lineNo */
    "mtimes", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "blas\\mtimes.m" /* pathName */
};

static emlrtRSInfo jh_emlrtRSI = {
    177,           /* lineNo */
    "mtimes_blas", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "blas\\mtimes.m" /* pathName */
};

static emlrtRSInfo kh_emlrtRSI =
    {
        377,                  /* lineNo */
        "trackingKF/correct", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo lh_emlrtRSI =
    {
        381,                  /* lineNo */
        "trackingKF/correct", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo mh_emlrtRSI = {
    269,                    /* lineNo */
    "KalmanFilter/correct", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo nh_emlrtRSI = {
    277,                    /* lineNo */
    "KalmanFilter/correct", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo oh_emlrtRSI = {
    283,                    /* lineNo */
    "KalmanFilter/correct", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo ph_emlrtRSI = {
    284,                    /* lineNo */
    "KalmanFilter/correct", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo qh_emlrtRSI = {
    288,                    /* lineNo */
    "KalmanFilter/correct", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo rh_emlrtRSI = {
    289,                    /* lineNo */
    "KalmanFilter/correct", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo sh_emlrtRSI = {
    291,                    /* lineNo */
    "KalmanFilter/correct", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo th_emlrtRSI = {
    14,                         /* lineNo */
    "validateInputSizeAndType", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\validateInputSiz"
    "eAndType.m" /* pathName */
};

static emlrtRSInfo uh_emlrtRSI = {
    20,                /* lineNo */
    "mrdivide_helper", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\mrdivide_"
    "helper.m" /* pathName */
};

static emlrtRSInfo kj_emlrtRSI =
    {
        69,                  /* lineNo */
        "eml_mtimes_helper", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_"
        "helper.m" /* pathName */
};

static emlrtRTEInfo emlrtRTEI =
    {
        1012,                                      /* lineNo */
        20,                                        /* colNo */
        "trackingKF/validateStateTransitionModel", /* fName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pName */
};

static emlrtRTEInfo l_emlrtRTEI = {
    14,                    /* lineNo */
    37,                    /* colNo */
    "validatenonnegative", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "valattr\\validatenonnegative.m" /* pName */
};

static emlrtDCInfo emlrtDCI = {
    489,                                 /* lineNo */
    45,                                  /* colNo */
    "KalmanFilter/get.MeasurementModel", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m", /* pName */
    1                                                     /* checkKind */
};

static emlrtBCInfo emlrtBCI = {
    1,                                   /* iFirst */
    3,                                   /* iLast */
    489,                                 /* lineNo */
    45,                                  /* colNo */
    "",                                  /* aName */
    "KalmanFilter/get.MeasurementModel", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m", /* pName */
    0                                                     /* checkKind */
};

static emlrtECInfo c_emlrtECI = {
    1,                      /* nDims */
    283,                    /* lineNo */
    34,                     /* colNo */
    "KalmanFilter/correct", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pName */
};

static emlrtECInfo d_emlrtECI = {
    2,                      /* nDims */
    283,                    /* lineNo */
    34,                     /* colNo */
    "KalmanFilter/correct", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pName */
};

static emlrtECInfo e_emlrtECI = {
    1,                      /* nDims */
    289,                    /* lineNo */
    34,                     /* colNo */
    "KalmanFilter/correct", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pName */
};

static emlrtRTEInfo m_emlrtRTEI = {
    16,                /* lineNo */
    19,                /* colNo */
    "mrdivide_helper", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\mrdivide_"
    "helper.m" /* pName */
};

static emlrtDCInfo b_emlrtDCI = {
    453,                                 /* lineNo */
    45,                                  /* colNo */
    "KalmanFilter/get.MeasurementNoise", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m", /* pName */
    1                                                     /* checkKind */
};

static emlrtBCInfo b_emlrtBCI = {
    1,                                   /* iFirst */
    3,                                   /* iLast */
    453,                                 /* lineNo */
    45,                                  /* colNo */
    "",                                  /* aName */
    "KalmanFilter/get.MeasurementNoise", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m", /* pName */
    0                                                     /* checkKind */
};

static emlrtDCInfo c_emlrtDCI = {
    453,                                 /* lineNo */
    54,                                  /* colNo */
    "KalmanFilter/get.MeasurementNoise", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m", /* pName */
    1                                                     /* checkKind */
};

static emlrtBCInfo c_emlrtBCI = {
    1,                                   /* iFirst */
    3,                                   /* iLast */
    453,                                 /* lineNo */
    54,                                  /* colNo */
    "",                                  /* aName */
    "KalmanFilter/get.MeasurementNoise", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m", /* pName */
    0                                                     /* checkKind */
};

static emlrtRTEInfo n_emlrtRTEI =
    {
        138,                   /* lineNo */
        23,                    /* colNo */
        "dynamic_size_checks", /* fName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_"
        "helper.m" /* pName */
};

static emlrtRTEInfo o_emlrtRTEI = {
    10,              /* lineNo */
    23,              /* colNo */
    "validatenumel", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "valattr\\validatenumel.m" /* pName */
};

static emlrtRTEInfo p_emlrtRTEI = {
    18,              /* lineNo */
    23,              /* colNo */
    "validatenumel", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "valattr\\validatenumel.m" /* pName */
};

/* Function Definitions */
void trackingKF_correct(const emlrtStack *sp, trackingKF *KF,
                        const real32_T z[3])
{
  __m128 r;
  __m128 r1;
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
  int32_T gain_numerator_size[2];
  int32_T residualCovariance_size[2];
  int32_T tmp_size[2];
  int32_T i;
  int32_T i1;
  int32_T k;
  int32_T loop_ub;
  real32_T P_corr[81];
  real32_T y[81];
  real32_T a_data[27];
  real32_T b_data[27];
  real32_T gain_numerator_data[27];
  real32_T y_data[27];
  real32_T residualCovariance_data[9];
  real32_T tmp_data[9];
  real32_T b_tmp_data[3];
  real32_T alpha1;
  real32_T beta1;
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
  st.site = &kh_emlrtRSI;
  b_st.site = &mh_emlrtRSI;
  alpha1 = KF->pN;
  c_st.site = &th_emlrtRSI;
  d_st.site = &fb_emlrtRSI;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3)) {
    if ((!muSingleScalarIsInf(z[k])) && (!muSingleScalarIsNaN(z[k]))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    emlrtErrorWithMessageIdR2018a(
        &d_st, &e_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 1, "z");
  }
  d_st.site = &fb_emlrtRSI;
  if ((!(muSingleScalarFloor(alpha1) == alpha1)) ||
      muSingleScalarIsInf(alpha1) || (!(alpha1 >= 0.0F))) {
    emlrtErrorWithMessageIdR2018a(&d_st, &o_emlrtRTEI,
                                  "Coder:toolbox:ValidateattributesBadNumel",
                                  "MATLAB:validateattributes:badnumel", 0);
  }
  if (!(alpha1 == 3.0F)) {
    emlrtErrorWithMessageIdR2018a(
        &d_st, &p_emlrtRTEI, "Coder:toolbox:ValidateattributesincorrectNumel",
        "MATLAB:KalmanFilter:incorrectNumel", 5, 4, 1, "z", 6, (real_T)alpha1);
  }
  b_st.site = &nh_emlrtRSI;
  if (KF->pN < 3.0F) {
    if (alpha1 < 1.0F) {
      loop_ub = 0;
    } else {
      if ((real_T)alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
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
    memcpy(&b_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real32_T));
  }
  b_st.site = &nh_emlrtRSI;
  c_st.site = &hh_emlrtRSI;
  if (loop_ub == 0) {
    gain_numerator_size[0] = 9;
    gain_numerator_size[1] = 0;
  } else {
    TRANSB1 = 'T';
    TRANSA1 = 'N';
    alpha1 = 1.0F;
    beta1 = 0.0F;
    m_t = (ptrdiff_t)9;
    n_t = (ptrdiff_t)loop_ub;
    k_t = (ptrdiff_t)9;
    lda_t = (ptrdiff_t)9;
    ldb_t = (ptrdiff_t)loop_ub;
    ldc_t = (ptrdiff_t)9;
    gain_numerator_size[0] = 9;
    gain_numerator_size[1] = loop_ub;
    sgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1,
          &KF->pStateCovariance[0], &lda_t, &b_data[0], &ldb_t, &beta1,
          &gain_numerator_data[0], &ldc_t);
  }
  b_st.site = &ph_emlrtRSI;
  if (KF->pN < 3.0F) {
    alpha1 = KF->pN;
    if (alpha1 < 1.0F) {
      loop_ub = 0;
    } else {
      if ((real_T)alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
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
    memcpy(&b_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real32_T));
  }
  b_st.site = &oh_emlrtRSI;
  c_st.site = &oh_emlrtRSI;
  if (KF->pN < 3.0F) {
    alpha1 = KF->pN;
    if (alpha1 < 1.0F) {
      k = 0;
    } else {
      if ((real_T)alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
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
    memcpy(&a_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real32_T));
  }
  c_st.site = &hh_emlrtRSI;
  if (k == 0) {
    k = 0;
  } else {
    TRANSB1 = 'N';
    TRANSA1 = 'N';
    alpha1 = 1.0F;
    beta1 = 0.0F;
    m_t = (ptrdiff_t)k;
    n_t = (ptrdiff_t)9;
    k_t = (ptrdiff_t)9;
    lda_t = (ptrdiff_t)k;
    ldb_t = (ptrdiff_t)9;
    ldc_t = (ptrdiff_t)k;
    sgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &a_data[0], &lda_t,
          &KF->pStateCovariance[0], &ldb_t, &beta1, &y_data[0], &ldc_t);
  }
  b_st.site = &oh_emlrtRSI;
  c_st.site = &hh_emlrtRSI;
  if ((k == 0) || (loop_ub == 0)) {
    residualCovariance_size[0] = k;
    residualCovariance_size[1] = loop_ub;
    k *= loop_ub;
    if (k - 1 >= 0) {
      memset(&residualCovariance_data[0], 0, (uint32_T)k * sizeof(real32_T));
    }
  } else {
    TRANSB1 = 'T';
    TRANSA1 = 'N';
    alpha1 = 1.0F;
    beta1 = 0.0F;
    m_t = (ptrdiff_t)k;
    n_t = (ptrdiff_t)loop_ub;
    k_t = (ptrdiff_t)9;
    lda_t = (ptrdiff_t)k;
    ldb_t = (ptrdiff_t)loop_ub;
    ldc_t = (ptrdiff_t)k;
    residualCovariance_size[0] = k;
    residualCovariance_size[1] = loop_ub;
    sgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &y_data[0], &lda_t,
          &b_data[0], &ldb_t, &beta1, &residualCovariance_data[0], &ldc_t);
  }
  b_st.site = &ph_emlrtRSI;
  if (KF->pV < 3.0F) {
    alpha1 = KF->pV;
    if (alpha1 < 1.0F) {
      k = 0;
    } else {
      if ((real_T)alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
        emlrtIntegerCheckR2012b(alpha1, &b_emlrtDCI, &b_st);
      }
      if (((int32_T)alpha1 < 1) || ((int32_T)alpha1 > 3)) {
        emlrtDynamicBoundsCheckR2012b((int32_T)alpha1, 1, 3, &b_emlrtBCI,
                                      &b_st);
      }
      k = (int32_T)alpha1;
    }
    if (alpha1 < 1.0F) {
      loop_ub = 0;
    } else {
      if ((real_T)alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
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
    for (i = 0; i < 9; i++) {
      tmp_data[i] = KF->pMeasurementNoise[i];
    }
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
    loop_ub = (k / 4) << 2;
    vectorUB = loop_ub - 4;
    for (i = 0; i <= vectorUB; i += 4) {
      r = _mm_loadu_ps(&residualCovariance_data[i]);
      r1 = _mm_loadu_ps(&tmp_data[i]);
      _mm_storeu_ps(&residualCovariance_data[i], _mm_add_ps(r, r1));
    }
    for (i = loop_ub; i < k; i++) {
      residualCovariance_data[i] += tmp_data[i];
    }
  } else {
    plus(residualCovariance_data, residualCovariance_size, tmp_data, tmp_size);
  }
  b_st.site = &qh_emlrtRSI;
  if (residualCovariance_size[1] != gain_numerator_size[1]) {
    emlrtErrorWithMessageIdR2018a(&b_st, &m_emlrtRTEI, "MATLAB:dimagree",
                                  "MATLAB:dimagree", 0);
  }
  c_st.site = &uh_emlrtRSI;
  mrdiv(&c_st, gain_numerator_data, gain_numerator_size,
        residualCovariance_data, residualCovariance_size);
  b_st.site = &rh_emlrtRSI;
  c_st.site = &rh_emlrtRSI;
  if (KF->pN < 3.0F) {
    alpha1 = KF->pN;
    if (alpha1 < 1.0F) {
      k = 0;
    } else {
      if ((real_T)alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
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
    memcpy(&a_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real32_T));
  }
  c_st.site = &hh_emlrtRSI;
  if (k == 0) {
    k = 0;
  } else {
    TRANSB1 = 'N';
    TRANSA1 = 'N';
    alpha1 = 1.0F;
    beta1 = 0.0F;
    m_t = (ptrdiff_t)k;
    n_t = (ptrdiff_t)1;
    k_t = (ptrdiff_t)9;
    lda_t = (ptrdiff_t)k;
    ldb_t = (ptrdiff_t)9;
    ldc_t = (ptrdiff_t)k;
    sgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &a_data[0], &lda_t,
          &KF->pState[0], &ldb_t, &beta1, &b_tmp_data[0], &ldc_t);
  }
  if ((k != 3) && (k != 1)) {
    emlrtDimSizeImpxCheckR2021b(3, k, &e_emlrtECI, &st);
  }
  b_st.site = &rh_emlrtRSI;
  c_st.site = &kj_emlrtRSI;
  if (gain_numerator_size[1] != 3) {
    emlrtErrorWithMessageIdR2018a(&c_st, &n_emlrtRTEI, "MATLAB:innerdim",
                                  "MATLAB:innerdim", 0);
  }
  b_st.site = &sh_emlrtRSI;
  c_st.site = &sh_emlrtRSI;
  if (KF->pN < 3.0F) {
    alpha1 = KF->pN;
    if (alpha1 < 1.0F) {
      loop_ub = 0;
    } else {
      if ((real_T)alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
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
    memcpy(&b_data[0], &KF->pMeasurementModel[0], 27U * sizeof(real32_T));
  }
  c_st.site = &kj_emlrtRSI;
  if (loop_ub != 3) {
    emlrtErrorWithMessageIdR2018a(&c_st, &n_emlrtRTEI, "MATLAB:innerdim",
                                  "MATLAB:innerdim", 0);
  }
  c_st.site = &hh_emlrtRSI;
  TRANSB1 = 'N';
  TRANSA1 = 'N';
  alpha1 = 1.0F;
  beta1 = 0.0F;
  m_t = (ptrdiff_t)9;
  n_t = (ptrdiff_t)9;
  k_t = (ptrdiff_t)3;
  lda_t = (ptrdiff_t)9;
  ldb_t = (ptrdiff_t)3;
  ldc_t = (ptrdiff_t)9;
  sgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &gain_numerator_data[0],
        &lda_t, &b_data[0], &ldb_t, &beta1, &y[0], &ldc_t);
  b_st.site = &sh_emlrtRSI;
  c_st.site = &hh_emlrtRSI;
  mtimes(y, KF->pStateCovariance, P_corr);
  for (i = 0; i <= 76; i += 4) {
    r = _mm_loadu_ps(&KF->pStateCovariance[i]);
    r1 = _mm_loadu_ps(&P_corr[i]);
    r = _mm_sub_ps(r, r1);
    _mm_storeu_ps(&P_corr[i], r);
  }
  P_corr[80] = KF->pStateCovariance[80] - P_corr[80];
  if (k == 3) {
    real32_T z_idx_2;
    alpha1 = z[0] - b_tmp_data[0];
    beta1 = z[1] - b_tmp_data[1];
    z_idx_2 = z[2] - b_tmp_data[2];
    for (i = 0; i <= 4; i += 4) {
      r = _mm_loadu_ps(&gain_numerator_data[i]);
      r1 = _mm_mul_ps(r, _mm_set1_ps(alpha1));
      r = _mm_loadu_ps(&gain_numerator_data[i + 9]);
      r = _mm_mul_ps(r, _mm_set1_ps(beta1));
      r1 = _mm_add_ps(r1, r);
      r = _mm_loadu_ps(&gain_numerator_data[i + 18]);
      r = _mm_mul_ps(r, _mm_set1_ps(z_idx_2));
      r = _mm_add_ps(r1, r);
      r1 = _mm_loadu_ps(&KF->pState[i]);
      r = _mm_add_ps(r1, r);
      _mm_storeu_ps(&KF->pState[i], r);
    }
    KF->pState[8] +=
        (gain_numerator_data[8] * alpha1 + gain_numerator_data[17] * beta1) +
        gain_numerator_data[26] * z_idx_2;
  } else {
    binary_expand_op(KF, gain_numerator_data, z, b_tmp_data, &k);
  }
  for (i = 0; i < 9; i++) {
    for (i1 = 0; i1 < 9; i1++) {
      k = i1 + 9 * i;
      KF->pStateCovariance[k] = (P_corr[k] + P_corr[i + 9 * i1]) * 0.5F;
    }
  }
  st.site = &lh_emlrtRSI;
  if (!KF->pIsInitialized) {
    KF->pIsDistributionsSetup = true;
  }
}

void trackingKF_predict(const emlrtStack *sp, trackingKF *KF,
                        real32_T varargin_1)
{
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
  int32_T b_j1;
  int32_T b_kidx;
  int32_T i1;
  int32_T j2;
  int32_T kidx;
  real32_T P[81];
  real32_T y[81];
  real32_T b_KF[27];
  real32_T A1dim[9];
  real32_T G1dim[3];
  real32_T alpha1;
  real32_T beta1;
  real32_T f;
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
  st.site = &ng_emlrtRSI;
  b_st.site = &rg_emlrtRSI;
  c_st.site = &sg_emlrtRSI;
  if (!KF->pIsSmootherStateSizeInitialized) {
    d_st.site = &ug_emlrtRSI;
    if (KF->pN < 3.0F) {
      alpha1 = KF->pN;
      if (!(alpha1 < 1.0F)) {
        if ((real_T)alpha1 != (int32_T)muDoubleScalarFloor(alpha1)) {
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
  c_st.site = &tg_emlrtRSI;
  if (!KF->IsLastJacobianInitialized) {
    KF->IsLastJacobianInitialized = true;
  }
  if (!KF->pIsDistributionsSetup) {
    KF->pIsDistributionsSetup = true;
  }
  st.site = &og_emlrtRSI;
  b_st.site = &fb_emlrtRSI;
  if (muSingleScalarIsInf(varargin_1) || muSingleScalarIsNaN(varargin_1)) {
    emlrtErrorWithMessageIdR2018a(
        &b_st, &e_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:trackingKF:expectedFinite", 3, 4, 2, "dt");
  }
  b_st.site = &fb_emlrtRSI;
  if (varargin_1 < 0.0F) {
    emlrtErrorWithMessageIdR2018a(
        &b_st, &l_emlrtRTEI,
        "Coder:toolbox:ValidateattributesexpectedNonnegative",
        "MATLAB:trackingKF:expectedNonnegative", 3, 4, 2, "dt");
  }
  st.site = &pg_emlrtRSI;
  b_st.site = &vg_emlrtRSI;
  c_st.site = &wg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  A1dim[0] = 1.0F;
  A1dim[3] = varargin_1;
  alpha1 = varargin_1 * varargin_1 / 2.0F;
  A1dim[6] = alpha1;
  A1dim[1] = 0.0F;
  A1dim[4] = 1.0F;
  A1dim[7] = varargin_1;
  A1dim[2] = 0.0F;
  A1dim[5] = 0.0F;
  A1dim[8] = 1.0F;
  c_st.site = &xg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &xg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &xg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &xg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &xg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &xg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  c_st.site = &yg_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  e_st.site = &l_emlrtRSI;
  G1dim[0] = alpha1;
  G1dim[1] = varargin_1;
  G1dim[2] = 1.0F;
  kidx = -1;
  b_kidx = -1;
  for (b_j1 = 0; b_j1 < 3; b_j1++) {
    for (j2 = 0; j2 < 3; j2++) {
      alpha1 = A1dim[3 * j2];
      beta1 = A1dim[3 * j2 + 1];
      f = A1dim[3 * j2 + 2];
      for (i1 = 0; i1 < 3; i1++) {
        int32_T P_tmp;
        P_tmp = iv[i1 + 3 * b_j1];
        P[kidx + 1] = (real32_T)P_tmp * alpha1;
        P[kidx + 2] = (real32_T)P_tmp * beta1;
        P[kidx + 3] = (real32_T)P_tmp * f;
        kidx += 3;
        KF->ProcessNoiseModel[(b_kidx + i1) + 1] =
            (real32_T)iv[j2 + 3 * b_j1] * G1dim[i1];
      }
      b_kidx += 3;
    }
  }
  KF->pIsStateTransitionLocked = false;
  st.site = &qg_emlrtRSI;
  b_st.site = &ah_emlrtRSI;
  c_st.site = &ch_emlrtRSI;
  d_st.site = &gb_emlrtRSI;
  e_st.site = &eh_emlrtRSI;
  f_st.site = &fh_emlrtRSI;
  g_st.site = &eb_emlrtRSI;
  h_st.site = &fb_emlrtRSI;
  p = true;
  kidx = 0;
  exitg1 = false;
  while ((!exitg1) && (kidx < 81)) {
    if ((!muSingleScalarIsInf(P[kidx])) && (!muSingleScalarIsNaN(P[kidx]))) {
      kidx++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    emlrtErrorWithMessageIdR2018a(
        &h_st, &e_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 20, "StateTransitionModel");
  }
  if (KF->pIsStateTransitionLocked) {
    emlrtErrorWithMessageIdR2018a(
        &d_st, &emlrtRTEI, "shared_tracking:KalmanFilter:setMotionModel",
        "shared_tracking:KalmanFilter:setMotionModel", 6, 4, 20,
        "StateTransitionModel", 4, 11, "MotionModel");
  }
  memcpy(&KF->StateTransitionModel[0], &P[0], 81U * sizeof(real32_T));
  c_st.site = &dh_emlrtRSI;
  d_st.site = &gh_emlrtRSI;
  e_st.site = &fb_emlrtRSI;
  p = true;
  kidx = 0;
  exitg1 = false;
  while ((!exitg1) && (kidx < 27)) {
    if ((!muSingleScalarIsInf(KF->ProcessNoiseModel[kidx])) &&
        (!muSingleScalarIsNaN(KF->ProcessNoiseModel[kidx]))) {
      kidx++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    emlrtErrorWithMessageIdR2018a(
        &e_st, &e_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 17, "ProcessNoiseModel");
  }
  b_st.site = &bh_emlrtRSI;
  c_st.site = &hh_emlrtRSI;
  mtimes(KF->StateTransitionModel, KF->pStateCovariance, P);
  b_st.site = &bh_emlrtRSI;
  c_st.site = &hh_emlrtRSI;
  d_st.site = &ih_emlrtRSI;
  e_st.site = &jh_emlrtRSI;
  TRANSB1 = 'T';
  TRANSA1 = 'N';
  alpha1 = 1.0F;
  beta1 = 0.0F;
  m_t = (ptrdiff_t)9;
  n_t = (ptrdiff_t)9;
  k_t = (ptrdiff_t)9;
  lda_t = (ptrdiff_t)9;
  ldb_t = (ptrdiff_t)9;
  ldc_t = (ptrdiff_t)9;
  sgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &P[0], &lda_t,
        &KF->StateTransitionModel[0], &ldb_t, &beta1, &y[0], &ldc_t);
  memset(&b_KF[0], 0, 27U * sizeof(real32_T));
  for (b_j1 = 0; b_j1 < 3; b_j1++) {
    kidx = 9 * b_j1 + 4;
    b_kidx = 9 * b_j1 + 8;
    for (j2 = 0; j2 < 3; j2++) {
      __m128 r;
      __m128 r1;
      __m128 r2;
      alpha1 = KF->pProcessNoise[j2 + 3 * b_j1];
      r = _mm_loadu_ps(&KF->ProcessNoiseModel[9 * j2]);
      r1 = _mm_loadu_ps(&b_KF[9 * b_j1]);
      r2 = _mm_set1_ps(alpha1);
      _mm_storeu_ps(&b_KF[9 * b_j1], _mm_add_ps(r1, _mm_mul_ps(r, r2)));
      r = _mm_loadu_ps(&KF->ProcessNoiseModel[9 * j2 + 4]);
      r1 = _mm_loadu_ps(&b_KF[kidx]);
      _mm_storeu_ps(&b_KF[kidx], _mm_add_ps(r1, _mm_mul_ps(r, r2)));
      b_KF[b_kidx] += KF->ProcessNoiseModel[9 * j2 + 8] * alpha1;
    }
  }
  memset(&A1dim[0], 0, 9U * sizeof(real32_T));
  for (b_j1 = 0; b_j1 < 9; b_j1++) {
    real32_T f1;
    alpha1 = KF->pState[b_j1];
    beta1 = b_KF[b_j1];
    f = b_KF[b_j1 + 9];
    f1 = b_KF[b_j1 + 18];
    for (j2 = 0; j2 < 9; j2++) {
      kidx = b_j1 + 9 * j2;
      P[kidx] = y[kidx] + ((beta1 * KF->ProcessNoiseModel[j2] +
                            f * KF->ProcessNoiseModel[j2 + 9]) +
                           f1 * KF->ProcessNoiseModel[j2 + 18]);
      A1dim[j2] += KF->StateTransitionModel[j2 + 9 * b_j1] * alpha1;
    }
  }
  for (b_j1 = 0; b_j1 < 9; b_j1++) {
    KF->pState[b_j1] = A1dim[b_j1];
    for (j2 = 0; j2 < 9; j2++) {
      kidx = j2 + 9 * b_j1;
      KF->pStateCovariance[kidx] = (P[kidx] + P[b_j1 + 9 * j2]) * 0.5F;
    }
  }
  KF->pIsStateTransitionLocked = true;
}

/* End of code generation (trackingKF.c) */
