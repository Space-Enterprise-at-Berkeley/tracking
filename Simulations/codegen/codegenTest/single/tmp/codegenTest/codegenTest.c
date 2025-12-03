#include "codegenTest.h"
#include "KalmanFilter.h"
#include "checkCovariance.h"
#include "codegenTest_float_mex_data.h"
#include "codegenTest_float_mex_internal_types.h"
#include "codegenTest_float_mex_mexutil.h"
#include "rt_nonfinite.h"
#include "trackingKF.h"
#include "mwmathutil.h"
#include "omp.h"
#include <emmintrin.h>
#include <string.h>

static emlrtRSInfo emlrtRSI = {
    2, "codegenTest",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\codegenTest.m"};

static emlrtRSInfo b_emlrtRSI = {
    3, "codegenTest",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\codegenTest.m"};

static emlrtRSInfo c_emlrtRSI = {
    4, "codegenTest",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\codegenTest.m"};

static emlrtRSInfo d_emlrtRSI = {
    5, "codegenTest",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\codegenTest.m"};

static emlrtRSInfo e_emlrtRSI = {
    14, "CombinedTracker/CombinedTracker",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo f_emlrtRSI = {
    17, "CombinedTracker/CombinedTracker",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo g_emlrtRSI = {234, "trackingKF/trackingKF",
                                 "C:\\Program "
                                 "Files\\MATLAB\\R2025b\\toolbox\\shared\\track"
                                 "ing\\fusionlib\\trackingKF.m"};

static emlrtRSInfo h_emlrtRSI = {237, "trackingKF/trackingKF",
                                 "C:\\Program "
                                 "Files\\MATLAB\\R2025b\\toolbox\\shared\\track"
                                 "ing\\fusionlib\\trackingKF.m"};

static emlrtRSInfo i_emlrtRSI = {212, "trackingKF/trackingKF",
                                 "C:\\Program "
                                 "Files\\MATLAB\\R2025b\\toolbox\\shared\\track"
                                 "ing\\fusionlib\\trackingKF.m"};

static emlrtRSInfo j_emlrtRSI = {240, "trackingKF/trackingKF",
                                 "C:\\Program "
                                 "Files\\MATLAB\\R2025b\\toolbox\\shared\\track"
                                 "ing\\fusionlib\\trackingKF.m"};

static emlrtRSInfo m_emlrtRSI = {
    66, "KFSmoother/KFSmoother",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\KFSmoother.m"};

static emlrtRSInfo n_emlrtRSI = {
    19, "LinearizedSmoother/LinearizedSmoother",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\LinearizedSmoother.m"};

static emlrtRSInfo o_emlrtRSI = {
    31, "GaussianSmoother/GaussianSmoother",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\smoothers\\+matlabshared\\+"
    "smoothers\\+internal\\GaussianSmoother.m"};

static emlrtRSInfo r_emlrtRSI = {
    158, "KalmanFilter/KalmanFilter",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo s_emlrtRSI = {
    162, "KalmanFilter/KalmanFilter",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo t_emlrtRSI = {
    660, "KalmanFilter/setProperties",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo u_emlrtRSI = {
    661, "KalmanFilter/setProperties",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo v_emlrtRSI = {
    662, "KalmanFilter/setProperties",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo w_emlrtRSI = {
    666, "KalmanFilter/setProperties",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo x_emlrtRSI = {
    667, "KalmanFilter/setProperties",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo y_emlrtRSI = {
    673, "KalmanFilter/setProperties",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo ab_emlrtRSI = {
    674, "KalmanFilter/setProperties",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo bb_emlrtRSI = {
    675, "KalmanFilter/setProperties",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo cb_emlrtRSI = {
    676, "KalmanFilter/setProperties",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo eb_emlrtRSI = {940, "trackingKF/set.ProcessNoise",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\shared\\trac"
                                  "king\\fusionlib\\trackingKF.m"};

static emlrtRSInfo tb_emlrtRSI = {
    444, "KalmanFilter/set.MeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo ub_emlrtRSI = {
    778, "KalmanFilter/measurementNoiseScalarExpandIfNecessary",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo ac_emlrtRSI = {
    1, "AbstractTrackingFilter/AbstractTrackingFilter",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\AbstractTracking"
    "Filter.m"};

static emlrtRSInfo bc_emlrtRSI = {
    1, "AbstractJPDAFilter/AbstractJPDAFilter",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\AbstractJPDAFilt"
    "er.m"};

static emlrtRSInfo cc_emlrtRSI = {
    1, "trackingKFMotionModelUtilities/trackingKFMotionModelUtilities",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\trackingK"
    "FMotionModelUtilities.m"};

static emlrtRSInfo dc_emlrtRSI = {
    1, "AbstractTunableFilter/AbstractTunableFilter",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\AbstractT"
    "unableFilter.m"};

static emlrtRSInfo ec_emlrtRSI = {
    1, "GaussianSmootherJIPDAFilter/GaussianSmootherJIPDAFilter",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\GaussianS"
    "mootherJIPDAFilter.m"};

static emlrtRSInfo fc_emlrtRSI = {
    1, "AbstractSmootherJIPDAFilter/AbstractSmootherJIPDAFilter",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\fusionlib\\+"
    "matlabshared\\+tracking\\+internal\\+fusion\\AbstractS"
    "mootherJIPDAFilter.m"};

static emlrtRSInfo gc_emlrtRSI = {
    1, "RetrodictionFilter/RetrodictionFilter",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\RetrodictionFilt"
    "er.m"};

static emlrtRSInfo hc_emlrtRSI = {
    1, "OOSMFilter/updateHistoryAfterCorrection",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\OOSMFilter.p"};

static emlrtRSInfo ic_emlrtRSI = {
    34, "CombinedTracker/GPSUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo jc_emlrtRSI = {
    35, "CombinedTracker/GPSUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo kc_emlrtRSI = {
    37, "CombinedTracker/GPSUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo lc_emlrtRSI = {
    38, "CombinedTracker/GPSUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo mc_emlrtRSI = {
    41, "CombinedTracker/GPSUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo qc_emlrtRSI = {
    441, "KalmanFilter/set.MeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo rc_emlrtRSI = {
    446, "KalmanFilter/set.MeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRSInfo gj_emlrtRSI = {
    44, "CombinedTracker/accelUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo hj_emlrtRSI = {
    45, "CombinedTracker/accelUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo ij_emlrtRSI = {
    47, "CombinedTracker/accelUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo jj_emlrtRSI = {
    48, "CombinedTracker/accelUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo kj_emlrtRSI = {
    51, "CombinedTracker/accelUpdate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtRSInfo lj_emlrtRSI = {
    21, "CombinedTracker/extrapolate",
    "C:\\Users\\lenowo "
    "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m"};

static emlrtECInfo emlrtECI = {
    -1, 791, 17, "KalmanFilter/setMeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRTEInfo b_emlrtRTEI = {
    790, 17, "KalmanFilter/setMeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static emlrtRTEInfo c_emlrtRTEI = {
    789, 17, "KalmanFilter/setMeasurementNoise",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

static void emlrt_update_log_1(const real_T in[3],
                               emlrtLocationLoggingDataType table[],
                               int32_T b_index);

static real_T emlrt_update_log_2(real_T in,
                                 emlrtLocationLoggingDataType table[],
                                 int32_T b_index);

static void emlrt_update_log_3(const real_T in[9],
                               emlrtLocationLoggingDataType table[],
                               int32_T b_index);

static void emlrt_update_log_4(const real_T in[81],
                               emlrtLocationLoggingDataType table[],
                               int32_T b_index);

static void emlrt_update_log_1(const real_T in[3],
                               emlrtLocationLoggingDataType table[],
                               int32_T b_index)
{
  if (b_index >= 0) {
    real_T d;
    real_T localMax;
    real_T localMin;
    int32_T i;
    localMin = ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMin;
    localMax = ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMax;

    d = in[0];
    if (d < localMin) {
      localMin = d;
    }
    if (d > localMax) {
      localMax = d;
    }

    d = in[1];
    if (d < localMin) {
      localMin = d;
    }
    if (d > localMax) {
      localMax = d;
    }

    d = in[2];
    if (d < localMin) {
      localMin = d;
    }
    if (d > localMax) {
      localMax = d;
    }
    ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMin = localMin;
    ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMax = localMax;

    i = 0;
    while (
        ((emlrtLocationLoggingDataType *)&table[b_index])[0U].IsAlwaysInteger &&
        (i < 3)) {
      if (in[i] != muDoubleScalarFloor(in[i])) {
        ((emlrtLocationLoggingDataType *)&table[b_index])[0U].IsAlwaysInteger =
            false;
      }
      i++;
    }
  }
}

static real_T emlrt_update_log_2(real_T in,
                                 emlrtLocationLoggingDataType table[],
                                 int32_T b_index)
{
  real_T out;
  if (b_index >= 0) {
    real_T localMax;
    out = ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMin;
    localMax = ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMax;

    if (in < out) {
      out = in;
    }
    if (in > localMax) {
      localMax = in;
    }
    ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMin = out;
    ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMax = localMax;

    if (in != muDoubleScalarFloor(in)) {
      ((emlrtLocationLoggingDataType *)&table[b_index])[0U].IsAlwaysInteger =
          false;
    }
  }
  return in;
}

static void emlrt_update_log_3(const real_T in[9],
                               emlrtLocationLoggingDataType table[],
                               int32_T b_index)
{
  int32_T i;
  if (b_index >= 0) {
    real_T localMax;
    real_T localMin;
    int32_T b_i;
    localMin = ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMin;
    localMax = ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMax;
    for (i = 0; i < 9; i++) {
      real_T d;

      d = in[i];
      if (d < localMin) {
        localMin = d;
      }
      if (d > localMax) {
        localMax = d;
      }
    }
    ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMin = localMin;
    ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMax = localMax;

    b_i = 0;
    while (
        ((emlrtLocationLoggingDataType *)&table[b_index])[0U].IsAlwaysInteger &&
        (b_i < 9)) {
      if (in[b_i] != muDoubleScalarFloor(in[b_i])) {
        ((emlrtLocationLoggingDataType *)&table[b_index])[0U].IsAlwaysInteger =
            false;
      }
      b_i++;
    }
  }
}

static void emlrt_update_log_4(const real_T in[81],
                               emlrtLocationLoggingDataType table[],
                               int32_T b_index)
{
  int32_T i;
  if (b_index >= 0) {
    real_T localMax;
    real_T localMin;
    int32_T b_i;
    localMin = ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMin;
    localMax = ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMax;
    for (i = 0; i < 81; i++) {
      real_T d;

      d = in[i];
      if (d < localMin) {
        localMin = d;
      }
      if (d > localMax) {
        localMax = d;
      }
    }
    ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMin = localMin;
    ((emlrtLocationLoggingDataType *)&table[b_index])[0U].SimMax = localMax;

    b_i = 0;
    while (
        ((emlrtLocationLoggingDataType *)&table[b_index])[0U].IsAlwaysInteger &&
        (b_i < 81)) {
      if (in[b_i] != muDoubleScalarFloor(in[b_i])) {
        ((emlrtLocationLoggingDataType *)&table[b_index])[0U].IsAlwaysInteger =
            false;
      }
      b_i++;
    }
  }
}

void codegenTest(const emlrtStack *sp, const real_T testGPS[3],
                 real_T testGPStime, const real_T testAccel[3],
                 real_T testAcceltime, real_T testExtrapolate, real_T state[9])
{
  static const real_T dv1[81] = {
      1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
      1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0};
  static const real_T MeasurementModelMatrix[27] = {
      1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  static const real_T ProcessNoiseModel[27] = {
      0.5, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0,
      1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0};
  static const real_T testTracker_AccelModel[27] = {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
  static const real_T testTracker_GPSNoise[9] = {5.0, 0.0, 0.0, 0.0, 5.0,
                                                 0.0, 0.0, 0.0, 5.0};
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
  emlrtStack st;
  trackingKF testTracker_Filter;
  real_T transition[81];
  real_T dv[3];
  real_T b_testTracker_Filter[2];
  real_T dt;
  real_T dt2;
  int32_T b_size[2];
  int32_T iv1[2];
  int32_T i;
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

  emlrtInitVarDataTables(emlrtLocationLoggingDataTables);

  dv[0] = testGPS[0];
  dv[1] = testGPS[1];
  dv[2] = testGPS[2];
  emlrt_update_log_1(dv, emlrtLocationLoggingDataTables, 0);

  emlrt_update_log_2(testGPStime, emlrtLocationLoggingDataTables, 1);

  dv[0] = testAccel[0];
  dv[1] = testAccel[1];
  dv[2] = testAccel[2];
  emlrt_update_log_1(dv, emlrtLocationLoggingDataTables, 2);

  emlrt_update_log_2(testAcceltime, emlrtLocationLoggingDataTables, 3);

  emlrt_update_log_2(testExtrapolate, emlrtLocationLoggingDataTables, 4);
  covrtLogFcn(&emlrtCoverageInstance, 0U, 0U);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0U, 0U);
  st.site = &emlrtRSI;
  covrtLogFcn(&emlrtCoverageInstance, 1U, 0U);
  covrtLogBasicBlock(&emlrtCoverageInstance, 1U, 0U);
  b_st.site = &e_emlrtRSI;
  dt = emlrt_update_log_2(0.0, emlrtLocationLoggingDataTables, 6);
  memset(&testTracker_Filter.pState[0], 0, 9U * sizeof(real_T));
  emlrt_update_log_3(testTracker_Filter.pState, emlrtLocationLoggingDataTables,
                     7);
  b_st.site = &f_emlrtRSI;
  c_st.site = &g_emlrtRSI;
  testTracker_Filter.pIsSmootherStateSizeInitialized = false;
  d_st.site = &m_emlrtRSI;
  testTracker_Filter.IsLastJacobianInitialized = false;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  testTracker_Filter.pIsDistributionsSetup = false;
  testTracker_Filter.pIsInitialized = false;
  c_st.site = &h_emlrtRSI;
  d_st.site = &r_emlrtRSI;
  d_st.site = &s_emlrtRSI;
  e_st.site = &t_emlrtRSI;
  f_st.site = &db_emlrtRSI;
  memcpy(&testTracker_Filter.StateTransitionModel[0], &dv1[0],
         81U * sizeof(real_T));
  e_st.site = &u_emlrtRSI;
  memset(&testTracker_Filter.pState[0], 0, 9U * sizeof(real_T));
  e_st.site = &v_emlrtRSI;
  for (i = 0; i < 81; i++) {
    testTracker_Filter.pStateCovariance[i] = b_iv[i];
  }
  e_st.site = &w_emlrtRSI;
  memcpy(&testTracker_Filter.ProcessNoiseModel[0], &ProcessNoiseModel[0],
         27U * sizeof(real_T));
  e_st.site = &x_emlrtRSI;
  f_st.site = &eb_emlrtRSI;
  for (i = 0; i < 9; i++) {
    testTracker_Filter.pProcessNoise[i] = iv[i];
  }
  e_st.site = &y_emlrtRSI;
  testTracker_Filter.pN = 3.0;
  e_st.site = &ab_emlrtRSI;
  testTracker_Filter.pV = 3.0;
  e_st.site = &bb_emlrtRSI;
  f_st.site = &sb_emlrtRSI;
  memcpy(&testTracker_Filter.pMeasurementModel[0], &MeasurementModelMatrix[0],
         27U * sizeof(real_T));
  e_st.site = &cb_emlrtRSI;
  f_st.site = &tb_emlrtRSI;
  b_size[0] = 3;
  b_size[1] = 3;
  g_st.site = &ub_emlrtRSI;
  iv1[0] = 3;
  iv1[1] = 3;
  emlrtSubAssignSizeCheckR2012b(&iv1[0], 2, &b_size[0], 2, &emlrtECI, &g_st);
  c_st.site = &i_emlrtRSI;
  d_st.site = &ac_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &bc_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &cc_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &dc_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &ec_emlrtRSI;
  e_st.site = &fc_emlrtRSI;
  c_st.site = &j_emlrtRSI;
  d_st.site = &gc_emlrtRSI;
  e_st.site = &hc_emlrtRSI;
  testTracker_Filter.pIsStateTransitionLocked = true;
  st.site = &b_emlrtRSI;

  emlrt_update_log_2(testGPStime, emlrtLocationLoggingDataTables, 8);

  dv[0] = testGPS[0];
  dv[1] = testGPS[1];
  dv[2] = testGPS[2];
  emlrt_update_log_1(dv, emlrtLocationLoggingDataTables, 9);
  covrtLogFcn(&emlrtCoverageInstance, 1U, 2U);
  covrtLogBasicBlock(&emlrtCoverageInstance, 1U, 2U);
  b_st.site = &ic_emlrtRSI;
  c_KalmanFilter_set_MeasurementM(&b_st, &testTracker_Filter,
                                  MeasurementModelMatrix);
  b_st.site = &jc_emlrtRSI;
  b_testTracker_Filter[0] = testTracker_Filter.pV;
  b_testTracker_Filter[1] = testTracker_Filter.pV;
  c_st.site = &qc_emlrtRSI;
  checkCovariance(&c_st, testTracker_GPSNoise, b_testTracker_Filter);
  c_st.site = &rc_emlrtRSI;
  if (!(testTracker_Filter.pV <= 3.0)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &c_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  if (!(testTracker_Filter.pV >= 3.0)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &b_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  iv1[0] = 3;
  b_size[0] = 3;
  iv1[1] = 3;
  b_size[1] = 3;
  emlrtSubAssignSizeCheckR2012b(&iv1[0], 2, &b_size[0], 2, &emlrtECI, &c_st);
  memcpy(&testTracker_Filter.pMeasurementNoise[0], &testTracker_GPSNoise[0],
         9U * sizeof(real_T));
  b_st.site = &kc_emlrtRSI;
  trackingKF_predict(
      &b_st, &testTracker_Filter,
      emlrt_update_log_2(testGPStime - dt, emlrtLocationLoggingDataTables, 10));
  b_st.site = &lc_emlrtRSI;
  trackingKF_correct(&b_st, &testTracker_Filter, testGPS);
  dt = emlrt_update_log_2(testGPStime, emlrtLocationLoggingDataTables, 11);
  b_st.site = &mc_emlrtRSI;
  emlrt_update_log_3(testTracker_Filter.pState, emlrtLocationLoggingDataTables,
                     12);
  st.site = &c_emlrtRSI;

  emlrt_update_log_2(testAcceltime, emlrtLocationLoggingDataTables, 13);

  dv[0] = testAccel[0];
  dv[1] = testAccel[1];
  dv[2] = testAccel[2];
  emlrt_update_log_1(dv, emlrtLocationLoggingDataTables, 14);
  covrtLogFcn(&emlrtCoverageInstance, 1U, 3U);
  covrtLogBasicBlock(&emlrtCoverageInstance, 1U, 3U);
  b_st.site = &gj_emlrtRSI;
  c_KalmanFilter_set_MeasurementM(&b_st, &testTracker_Filter,
                                  testTracker_AccelModel);
  b_st.site = &hj_emlrtRSI;
  b_testTracker_Filter[0] = testTracker_Filter.pV;
  b_testTracker_Filter[1] = testTracker_Filter.pV;
  c_st.site = &qc_emlrtRSI;
  checkCovariance(&c_st, testTracker_GPSNoise, b_testTracker_Filter);
  c_st.site = &rc_emlrtRSI;
  if (!(testTracker_Filter.pV <= 3.0)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &c_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  if (!(testTracker_Filter.pV >= 3.0)) {
    emlrtErrorWithMessageIdR2018a(&c_st, &b_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  iv1[0] = 3;
  b_size[0] = 3;
  iv1[1] = 3;
  b_size[1] = 3;
  emlrtSubAssignSizeCheckR2012b(&iv1[0], 2, &b_size[0], 2, &emlrtECI, &c_st);
  memcpy(&testTracker_Filter.pMeasurementNoise[0], &testTracker_GPSNoise[0],
         9U * sizeof(real_T));
  b_st.site = &ij_emlrtRSI;
  trackingKF_predict(&b_st, &testTracker_Filter,
                     emlrt_update_log_2(testAcceltime - dt,
                                        emlrtLocationLoggingDataTables, 15));
  b_st.site = &jj_emlrtRSI;
  trackingKF_correct(&b_st, &testTracker_Filter, testAccel);
  dt = emlrt_update_log_2(testAcceltime, emlrtLocationLoggingDataTables, 16);
  b_st.site = &kj_emlrtRSI;
  emlrt_update_log_3(testTracker_Filter.pState, emlrtLocationLoggingDataTables,
                     17);
  st.site = &d_emlrtRSI;

  emlrt_update_log_2(testExtrapolate, emlrtLocationLoggingDataTables, 18);
  covrtLogFcn(&emlrtCoverageInstance, 1U, 1U);
  covrtLogBasicBlock(&emlrtCoverageInstance, 1U, 1U);
  dt = emlrt_update_log_2(testExtrapolate - dt, emlrtLocationLoggingDataTables,
                          19);
  b_st.site = &lj_emlrtRSI;
  c_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  dt2 = emlrt_update_log_2(
      emlrt_update_log_2(dt * dt, emlrtLocationLoggingDataTables, 21) / 2.0,
      emlrtLocationLoggingDataTables, 20);
  transition[0] = 1.0;
  transition[9] = dt;
  transition[18] = dt2;
  transition[27] = 0.0;
  transition[36] = 0.0;
  transition[45] = 0.0;
  transition[54] = 0.0;
  transition[63] = 0.0;
  transition[72] = 0.0;
  transition[1] = 0.0;
  transition[10] = 1.0;
  transition[19] = dt;
  transition[28] = 0.0;
  transition[37] = 0.0;
  transition[46] = 0.0;
  transition[55] = 0.0;
  transition[64] = 0.0;
  transition[73] = 0.0;
  transition[3] = 0.0;
  transition[12] = 0.0;
  transition[21] = 0.0;
  transition[30] = 1.0;
  transition[39] = dt;
  transition[48] = dt2;
  transition[57] = 0.0;
  transition[66] = 0.0;
  transition[75] = 0.0;
  transition[4] = 0.0;
  transition[13] = 0.0;
  transition[22] = 0.0;
  transition[31] = 0.0;
  transition[40] = 1.0;
  transition[49] = dt;
  transition[58] = 0.0;
  transition[67] = 0.0;
  transition[76] = 0.0;
  transition[6] = 0.0;
  transition[15] = 0.0;
  transition[24] = 0.0;
  transition[33] = 0.0;
  transition[42] = 0.0;
  transition[51] = 0.0;
  transition[60] = 1.0;
  transition[69] = dt;
  transition[78] = dt2;
  transition[7] = 0.0;
  transition[16] = 0.0;
  transition[25] = 0.0;
  transition[34] = 0.0;
  transition[43] = 0.0;
  transition[52] = 0.0;
  transition[61] = 0.0;
  transition[70] = 1.0;
  transition[79] = dt;
  for (i = 0; i < 9; i++) {
    transition[9 * i + 2] = iv2[i];
    transition[9 * i + 5] = iv3[i];
    transition[9 * i + 8] = iv4[i];
  }
  emlrt_update_log_4(transition, emlrtLocationLoggingDataTables, 22);
  memset(&state[0], 0, 9U * sizeof(real_T));
  for (i = 0; i < 9; i++) {
    __m128d r;
    __m128d r1;
    __m128d r2;
    r = _mm_loadu_pd(&transition[9 * i]);
    r1 = _mm_loadu_pd(&state[0]);
    dt = testTracker_Filter.pState[i];
    r2 = _mm_set1_pd(dt);
    _mm_storeu_pd(&state[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&transition[9 * i + 2]);
    r1 = _mm_loadu_pd(&state[2]);
    _mm_storeu_pd(&state[2], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&transition[9 * i + 4]);
    r1 = _mm_loadu_pd(&state[4]);
    _mm_storeu_pd(&state[4], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&transition[9 * i + 6]);
    r1 = _mm_loadu_pd(&state[6]);
    _mm_storeu_pd(&state[6], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    state[8] += transition[9 * i + 8] * dt;
  }
  emlrt_update_log_3(state, emlrtLocationLoggingDataTables, 23);
  emlrt_update_log_3(state, emlrtLocationLoggingDataTables, 5);
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
