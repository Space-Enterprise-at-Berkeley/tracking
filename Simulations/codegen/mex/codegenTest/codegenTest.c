/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * codegenTest.c
 *
 * Code generation for function 'codegenTest'
 *
 */

/* Include files */
#include "codegenTest.h"
#include "KalmanFilter.h"
#include "checkCovariance.h"
#include "codegenTest_data.h"
#include "codegenTest_internal_types.h"
#include "rt_nonfinite.h"
#include "trackingKF.h"
#include "validateattributes.h"
#include "omp.h"
#include <string.h>
#include <xmmintrin.h>

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = {
    2,             /* lineNo */
    "codegenTest", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\codegenTest.m" /* pathName
                                                                      */
};

static emlrtRSInfo b_emlrtRSI = {
    3,             /* lineNo */
    "codegenTest", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\codegenTest.m" /* pathName
                                                                      */
};

static emlrtRSInfo c_emlrtRSI = {
    4,             /* lineNo */
    "codegenTest", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\codegenTest.m" /* pathName
                                                                      */
};

static emlrtRSInfo d_emlrtRSI = {
    5,             /* lineNo */
    "codegenTest", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\codegenTest.m" /* pathName
                                                                      */
};

static emlrtRSInfo e_emlrtRSI = {
    14,                                /* lineNo */
    "CombinedTracker/CombinedTracker", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo f_emlrtRSI = {
    24,                                /* lineNo */
    "CombinedTracker/CombinedTracker", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo g_emlrtRSI =
    {
        234,                     /* lineNo */
        "trackingKF/trackingKF", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo h_emlrtRSI =
    {
        237,                     /* lineNo */
        "trackingKF/trackingKF", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo i_emlrtRSI =
    {
        212,                     /* lineNo */
        "trackingKF/trackingKF", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo j_emlrtRSI =
    {
        240,                     /* lineNo */
        "trackingKF/trackingKF", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo m_emlrtRSI = {
    66,                      /* lineNo */
    "KFSmoother/KFSmoother", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\KFSmoother.m" /* pathName */
};

static emlrtRSInfo n_emlrtRSI = {
    19,                                      /* lineNo */
    "LinearizedSmoother/LinearizedSmoother", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\LinearizedSmoother.m" /* pathName */
};

static emlrtRSInfo o_emlrtRSI = {
    31,                                  /* lineNo */
    "GaussianSmoother/GaussianSmoother", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\GaussianSmoother.m" /* pathName */
};

static emlrtRSInfo r_emlrtRSI = {
    158,                         /* lineNo */
    "KalmanFilter/KalmanFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo s_emlrtRSI = {
    162,                         /* lineNo */
    "KalmanFilter/KalmanFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo t_emlrtRSI = {
    648,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo u_emlrtRSI = {
    660,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo v_emlrtRSI = {
    661,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo w_emlrtRSI = {
    662,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo x_emlrtRSI = {
    666,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo y_emlrtRSI = {
    667,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo ab_emlrtRSI = {
    673,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo bb_emlrtRSI = {
    674,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo cb_emlrtRSI = {
    675,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo db_emlrtRSI = {
    676,                          /* lineNo */
    "KalmanFilter/setProperties", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo hb_emlrtRSI = {
    404,                      /* lineNo */
    "KalmanFilter/set.State", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo ib_emlrtRSI = {
    6,               /* lineNo */
    "validateState", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\validateState.m" /* pathName */
};

static emlrtRSInfo jb_emlrtRSI =
    {
        940,                           /* lineNo */
        "trackingKF/set.ProcessNoise", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\trackingK"
        "F.m" /* pathName */
};

static emlrtRSInfo yb_emlrtRSI = {
    444,                                 /* lineNo */
    "KalmanFilter/set.MeasurementNoise", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo ac_emlrtRSI = {
    778,                                                    /* lineNo */
    "KalmanFilter/measurementNoiseScalarExpandIfNecessary", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo fc_emlrtRSI = {
    1,                                               /* lineNo */
    "AbstractTrackingFilter/AbstractTrackingFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\AbstractTracking"
    "Filter.m" /* pathName */
};

static emlrtRSInfo gc_emlrtRSI = {
    1,                                       /* lineNo */
    "AbstractJPDAFilter/AbstractJPDAFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\AbstractJPDAFilt"
    "er.m" /* pathName */
};

static emlrtRSInfo hc_emlrtRSI = {
    1, /* lineNo */
    "trackingKFMotionModelUtilities/trackingKFMotionModelUtilities", /* fcnName
                                                                      */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\trackingK"
    "FMotionModelUtilities.m" /* pathName */
};

static emlrtRSInfo ic_emlrtRSI = {
    1,                                             /* lineNo */
    "AbstractTunableFilter/AbstractTunableFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\AbstractT"
    "unableFilter.m" /* pathName */
};

static emlrtRSInfo jc_emlrtRSI = {
    1,                                                         /* lineNo */
    "GaussianSmootherJIPDAFilter/GaussianSmootherJIPDAFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\GaussianS"
    "mootherJIPDAFilter.m" /* pathName */
};

static emlrtRSInfo kc_emlrtRSI = {
    1,                                                         /* lineNo */
    "AbstractSmootherJIPDAFilter/AbstractSmootherJIPDAFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\AbstractS"
    "mootherJIPDAFilter.m" /* pathName */
};

static emlrtRSInfo lc_emlrtRSI = {
    1,                                       /* lineNo */
    "RetrodictionFilter/RetrodictionFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\RetrodictionFilt"
    "er.m" /* pathName */
};

static emlrtRSInfo mc_emlrtRSI = {
    1,                                         /* lineNo */
    "OOSMFilter/updateHistoryAfterCorrection", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\OOSMFilter.p" /* pathName */
};

static emlrtRSInfo nc_emlrtRSI = {
    1,                       /* lineNo */
    "dts_cast_with_warning", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\coder\\float2fixed\\dtslib\\dts_cast_with_"
    "warning.p" /* pathName */
};

static emlrtRSInfo
    oc_emlrtRSI =
        {
            1,          /* lineNo */
            "dts_cast", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\coder\\float2fixed\\dtslib\\dts_"
            "cast.p" /* pathName */
};

static emlrtRSInfo pc_emlrtRSI = {
    41,                          /* lineNo */
    "CombinedTracker/GPSUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo qc_emlrtRSI = {
    42,                          /* lineNo */
    "CombinedTracker/GPSUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo rc_emlrtRSI = {
    44,                          /* lineNo */
    "CombinedTracker/GPSUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo sc_emlrtRSI = {
    45,                          /* lineNo */
    "CombinedTracker/GPSUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo tc_emlrtRSI = {
    48,                          /* lineNo */
    "CombinedTracker/GPSUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo vc_emlrtRSI = {
    441,                                 /* lineNo */
    "KalmanFilter/set.MeasurementNoise", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo wc_emlrtRSI = {
    446,                                 /* lineNo */
    "KalmanFilter/set.MeasurementNoise", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

static emlrtRSInfo lj_emlrtRSI = {
    51,                            /* lineNo */
    "CombinedTracker/accelUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo mj_emlrtRSI = {
    52,                            /* lineNo */
    "CombinedTracker/accelUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo nj_emlrtRSI = {
    54,                            /* lineNo */
    "CombinedTracker/accelUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo oj_emlrtRSI = {
    55,                            /* lineNo */
    "CombinedTracker/accelUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo pj_emlrtRSI = {
    58,                            /* lineNo */
    "CombinedTracker/accelUpdate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRSInfo qj_emlrtRSI = {
    28,                            /* lineNo */
    "CombinedTracker/extrapolate", /* fcnName */
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m" /* pathName
                                                                          */
};

static emlrtRTEInfo c_emlrtRTEI = {
    789,                                /* lineNo */
    17,                                 /* colNo */
    "KalmanFilter/setMeasurementNoise", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pName */
};

static emlrtRTEInfo d_emlrtRTEI = {
    790,                                /* lineNo */
    17,                                 /* colNo */
    "KalmanFilter/setMeasurementNoise", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pName */
};

static emlrtECInfo emlrtECI = {
    -1,                                 /* nDims */
    791,                                /* lineNo */
    17,                                 /* colNo */
    "KalmanFilter/setMeasurementNoise", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pName */
};

/* Function Definitions */
void codegenTest(const emlrtStack *sp, const real32_T testGPS[3],
                 real32_T testGPStime, const real32_T testAccel[3],
                 real32_T testAcceltime, real32_T testExtrapolate,
                 real32_T state[9])
{
  static const real32_T fv[81] = {
      1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.5F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.5F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.5F, 1.0F, 1.0F};
  static const real32_T MeasurementModelMatrix[27] = {
      1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F};
  static const real32_T ProcessNoiseModel[27] = {
      0.5F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.5F, 1.0F, 1.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.5F, 1.0F, 1.0F};
  static const real32_T testTracker_AccelModel[27] = {
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F};
  static const real32_T testTracker_GPSNoise[9] = {5.0F, 0.0F, 0.0F, 0.0F, 5.0F,
                                                   0.0F, 0.0F, 0.0F, 5.0F};
  static const int8_T b_iv[81] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  static const int8_T iv2[9] = {0, 0, 1, 0, 0, 0, 0, 0, 0};
  static const int8_T iv3[9] = {0, 0, 0, 0, 0, 1, 0, 0, 0};
  static const int8_T iv4[9] = {0, 0, 0, 0, 0, 0, 0, 0, 1};
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack st;
  trackingKF testTracker_coder_buffer_pobj0;
  int32_T b_size[2];
  int32_T iv1[2];
  int32_T k;
  real32_T fv1[81];
  real32_T b_value[9];
  real32_T dims[2];
  real32_T dt;
  int8_T b_data[9];
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
  st.site = &emlrtRSI;
  b_st.site = &e_emlrtRSI;
  for (k = 0; k < 9; k++) {
    b_value[k] = 0.0F;
  }
  b_st.site = &f_emlrtRSI;
  c_st.site = &f_emlrtRSI;
  d_st.site = &g_emlrtRSI;
  testTracker_coder_buffer_pobj0.pIsSmootherStateSizeInitialized = false;
  e_st.site = &m_emlrtRSI;
  testTracker_coder_buffer_pobj0.IsLastJacobianInitialized = false;
  f_st.site = &n_emlrtRSI;
  g_st.site = &o_emlrtRSI;
  testTracker_coder_buffer_pobj0.pIsDistributionsSetup = false;
  testTracker_coder_buffer_pobj0.pIsInitialized = false;
  d_st.site = &h_emlrtRSI;
  e_st.site = &r_emlrtRSI;
  e_st.site = &s_emlrtRSI;
  f_st.site = &t_emlrtRSI;
  g_st.site = &eb_emlrtRSI;
  validateattributes(&g_st, b_value);
  f_st.site = &u_emlrtRSI;
  g_st.site = &gb_emlrtRSI;
  memcpy(&testTracker_coder_buffer_pobj0.StateTransitionModel[0], &fv[0],
         81U * sizeof(real32_T));
  f_st.site = &v_emlrtRSI;
  g_st.site = &hb_emlrtRSI;
  h_st.site = &ib_emlrtRSI;
  validateattributes(&h_st, b_value);
  for (k = 0; k < 9; k++) {
    testTracker_coder_buffer_pobj0.pState[k] = 0.0F;
  }
  f_st.site = &w_emlrtRSI;
  for (k = 0; k < 81; k++) {
    testTracker_coder_buffer_pobj0.pStateCovariance[k] = b_iv[k];
  }
  f_st.site = &x_emlrtRSI;
  memcpy(&testTracker_coder_buffer_pobj0.ProcessNoiseModel[0],
         &ProcessNoiseModel[0], 27U * sizeof(real32_T));
  f_st.site = &y_emlrtRSI;
  g_st.site = &jb_emlrtRSI;
  for (k = 0; k < 9; k++) {
    testTracker_coder_buffer_pobj0.pProcessNoise[k] = iv[k];
  }
  f_st.site = &ab_emlrtRSI;
  testTracker_coder_buffer_pobj0.pN = 3.0F;
  f_st.site = &bb_emlrtRSI;
  testTracker_coder_buffer_pobj0.pV = 3.0F;
  for (k = 0; k < 9; k++) {
    testTracker_coder_buffer_pobj0.pMeasurementNoise[k] = 0.0F;
  }
  f_st.site = &cb_emlrtRSI;
  g_st.site = &xb_emlrtRSI;
  memcpy(&testTracker_coder_buffer_pobj0.pMeasurementModel[0],
         &MeasurementModelMatrix[0], 27U * sizeof(real32_T));
  f_st.site = &db_emlrtRSI;
  g_st.site = &yb_emlrtRSI;
  b_size[0] = 3;
  b_size[1] = 3;
  for (k = 0; k < 9; k++) {
    b_data[k] = 0;
  }
  for (k = 0; k < 3; k++) {
    b_data[k + 3 * k] = 1;
  }
  h_st.site = &ac_emlrtRSI;
  iv1[0] = 3;
  iv1[1] = 3;
  emlrtSubAssignSizeCheckR2012b(&iv1[0], 2, &b_size[0], 2, &emlrtECI, &h_st);
  for (k = 0; k < 9; k++) {
    testTracker_coder_buffer_pobj0.pMeasurementNoise[k] = b_data[k];
  }
  d_st.site = &i_emlrtRSI;
  e_st.site = &fc_emlrtRSI;
  d_st.site = &i_emlrtRSI;
  e_st.site = &gc_emlrtRSI;
  d_st.site = &i_emlrtRSI;
  e_st.site = &hc_emlrtRSI;
  d_st.site = &i_emlrtRSI;
  e_st.site = &ic_emlrtRSI;
  d_st.site = &i_emlrtRSI;
  e_st.site = &jc_emlrtRSI;
  f_st.site = &kc_emlrtRSI;
  d_st.site = &j_emlrtRSI;
  e_st.site = &lc_emlrtRSI;
  f_st.site = &mc_emlrtRSI;
  testTracker_coder_buffer_pobj0.pIsStateTransitionLocked = true;
  c_st.site = &nc_emlrtRSI;
  d_st.site = &oc_emlrtRSI;
  st.site = &b_emlrtRSI;
  b_st.site = &pc_emlrtRSI;
  c_KalmanFilter_set_MeasurementM(&b_st, &testTracker_coder_buffer_pobj0,
                                  MeasurementModelMatrix);
  b_st.site = &qc_emlrtRSI;
  dims[0] = testTracker_coder_buffer_pobj0.pV;
  dims[1] = testTracker_coder_buffer_pobj0.pV;
  c_st.site = &vc_emlrtRSI;
  checkCovariance(&c_st, testTracker_GPSNoise, dims);
  c_st.site = &wc_emlrtRSI;
  if (!(testTracker_coder_buffer_pobj0.pV <= 3.0F)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &c_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  if (!(testTracker_coder_buffer_pobj0.pV >= 3.0F)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &d_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  iv1[0] = 3;
  b_size[0] = 3;
  iv1[1] = 3;
  b_size[1] = 3;
  emlrtSubAssignSizeCheckR2012b(&iv1[0], 2, &b_size[0], 2, &emlrtECI, &c_st);
  for (k = 0; k < 9; k++) {
    testTracker_coder_buffer_pobj0.pMeasurementNoise[k] =
        testTracker_GPSNoise[k];
  }
  b_st.site = &rc_emlrtRSI;
  trackingKF_predict(&b_st, &testTracker_coder_buffer_pobj0, testGPStime);
  b_st.site = &sc_emlrtRSI;
  trackingKF_correct(&b_st, &testTracker_coder_buffer_pobj0, testGPS);
  b_st.site = &tc_emlrtRSI;
  st.site = &c_emlrtRSI;
  b_st.site = &lj_emlrtRSI;
  c_KalmanFilter_set_MeasurementM(&b_st, &testTracker_coder_buffer_pobj0,
                                  testTracker_AccelModel);
  b_st.site = &mj_emlrtRSI;
  dims[0] = testTracker_coder_buffer_pobj0.pV;
  dims[1] = testTracker_coder_buffer_pobj0.pV;
  c_st.site = &vc_emlrtRSI;
  checkCovariance(&c_st, testTracker_GPSNoise, dims);
  c_st.site = &wc_emlrtRSI;
  if (!(testTracker_coder_buffer_pobj0.pV <= 3.0F)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &c_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  if (!(testTracker_coder_buffer_pobj0.pV >= 3.0F)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &d_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  iv1[0] = 3;
  b_size[0] = 3;
  iv1[1] = 3;
  b_size[1] = 3;
  emlrtSubAssignSizeCheckR2012b(&iv1[0], 2, &b_size[0], 2, &emlrtECI, &c_st);
  for (k = 0; k < 9; k++) {
    testTracker_coder_buffer_pobj0.pMeasurementNoise[k] =
        testTracker_GPSNoise[k];
  }
  b_st.site = &nj_emlrtRSI;
  trackingKF_predict(&b_st, &testTracker_coder_buffer_pobj0,
                     testAcceltime - testGPStime);
  b_st.site = &oj_emlrtRSI;
  trackingKF_correct(&b_st, &testTracker_coder_buffer_pobj0, testAccel);
  b_st.site = &pj_emlrtRSI;
  for (k = 0; k < 9; k++) {
    b_value[k] = testTracker_coder_buffer_pobj0.pState[k];
  }
  real32_T dt2;
  st.site = &d_emlrtRSI;
  dt = testExtrapolate - testAcceltime;
  b_st.site = &qj_emlrtRSI;
  c_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  dt2 = dt * dt / 2.0F;
  fv1[0] = 1.0F;
  fv1[9] = dt;
  fv1[18] = dt2;
  fv1[27] = 0.0F;
  fv1[36] = 0.0F;
  fv1[45] = 0.0F;
  fv1[54] = 0.0F;
  fv1[63] = 0.0F;
  fv1[72] = 0.0F;
  fv1[1] = 0.0F;
  fv1[10] = 1.0F;
  fv1[19] = dt;
  fv1[28] = 0.0F;
  fv1[37] = 0.0F;
  fv1[46] = 0.0F;
  fv1[55] = 0.0F;
  fv1[64] = 0.0F;
  fv1[73] = 0.0F;
  fv1[3] = 0.0F;
  fv1[12] = 0.0F;
  fv1[21] = 0.0F;
  fv1[30] = 1.0F;
  fv1[39] = dt;
  fv1[48] = dt2;
  fv1[57] = 0.0F;
  fv1[66] = 0.0F;
  fv1[75] = 0.0F;
  fv1[4] = 0.0F;
  fv1[13] = 0.0F;
  fv1[22] = 0.0F;
  fv1[31] = 0.0F;
  fv1[40] = 1.0F;
  fv1[49] = dt;
  fv1[58] = 0.0F;
  fv1[67] = 0.0F;
  fv1[76] = 0.0F;
  fv1[6] = 0.0F;
  fv1[15] = 0.0F;
  fv1[24] = 0.0F;
  fv1[33] = 0.0F;
  fv1[42] = 0.0F;
  fv1[51] = 0.0F;
  fv1[60] = 1.0F;
  fv1[69] = dt;
  fv1[78] = dt2;
  fv1[7] = 0.0F;
  fv1[16] = 0.0F;
  fv1[25] = 0.0F;
  fv1[34] = 0.0F;
  fv1[43] = 0.0F;
  fv1[52] = 0.0F;
  fv1[61] = 0.0F;
  fv1[70] = 1.0F;
  fv1[79] = dt;
  memset(&state[0], 0, 9U * sizeof(real32_T));
  for (k = 0; k < 9; k++) {
    __m128 r;
    __m128 r1;
    __m128 r2;
    int32_T i;
    fv1[9 * k + 2] = iv2[k];
    fv1[9 * k + 5] = iv3[k];
    i = 9 * k + 8;
    fv1[i] = iv4[k];
    r = _mm_loadu_ps(&fv1[9 * k]);
    r1 = _mm_loadu_ps(&state[0]);
    dt = b_value[k];
    r2 = _mm_set1_ps(dt);
    _mm_storeu_ps(&state[0], _mm_add_ps(r1, _mm_mul_ps(r, r2)));
    r = _mm_loadu_ps(&fv1[9 * k + 4]);
    r1 = _mm_loadu_ps(&state[4]);
    _mm_storeu_ps(&state[4], _mm_add_ps(r1, _mm_mul_ps(r, r2)));
    state[8] += fv1[i] * dt;
  }
}

emlrtCTX emlrtGetRootTLSGlobal(void)
{
  return emlrtRootTLSGlobal;
}

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, emlrtConstCTX aTLS,
                         void *aData)
{
  omp_set_lock(&emlrtLockGlobal);
  emlrtCallLockeeFunction(aLockee, aTLS, aData);
  omp_unset_lock(&emlrtLockGlobal);
}

/* End of code generation (codegenTest.c) */
