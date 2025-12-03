#include "checkCovariance.h"
#include "anyNonFinite.h"
#include "codegenTest_float_mex_data.h"
#include "eigStandard.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "warning.h"
#include "xgemv.h"
#include "xgerc.h"
#include "xhseqr.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "lapacke.h"
#include "mwmathutil.h"
#include <emmintrin.h>
#include <math.h>
#include <stddef.h>
#include <string.h>

static emlrtRSInfo gb_emlrtRSI = {62, "ceval_xsyheev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xsyheev.m"};

static emlrtRSInfo sc_emlrtRSI = {
    7, "checkCovariance",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\checkCovariance."
    "m"};

static emlrtRSInfo tc_emlrtRSI = {
    8, "checkCovariance",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\checkCovariance."
    "m"};

static emlrtRSInfo uc_emlrtRSI = {
    9, "checkCovariance",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\checkCovariance."
    "m"};

static emlrtRSInfo vc_emlrtRSI = {
    18, "isSymmetricPositiveSemiDefinite",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\isSymmetricPosit"
    "iveSemiDefinite.m"};

static emlrtRSInfo wc_emlrtRSI = {
    20, "isSymmetricPositiveSemiDefinite",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\isSymmetricPosit"
    "iveSemiDefinite.m"};

static emlrtRSInfo xc_emlrtRSI = {
    13, "all",
    "C:\\Program Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\ops\\all.m"};

static emlrtRSInfo yc_emlrtRSI = {
    143, "allOrAny",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\allOrAny.m"};

static emlrtRSInfo ad_emlrtRSI = {
    81, "eig",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m"};

static emlrtRSInfo bd_emlrtRSI = {
    127, "eig",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m"};

static emlrtRSInfo cd_emlrtRSI = {
    135, "eig",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m"};

static emlrtRSInfo dd_emlrtRSI = {
    143, "eig",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m"};

static emlrtRSInfo hd_emlrtRSI = {
    13, "eigHermitianStandard",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigHerm"
    "itianStandard.m"};

static emlrtRSInfo id_emlrtRSI = {
    40, "eigHermitianStandard",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigHerm"
    "itianStandard.m"};

static emlrtRSInfo jd_emlrtRSI = {8, "xsyheev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xsyheev.m"};

static emlrtRSInfo kd_emlrtRSI = {
    10, "eigSkewHermitianStandard",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigSkew"
    "HermitianStandard.m"};

static emlrtRSInfo ld_emlrtRSI = {
    19, "eigRealSkewSymmetricStandard",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigReal"
    "SkewSymmetricStandard.m"};

static emlrtRSInfo md_emlrtRSI = {
    35, "schur",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\schur.m"};

static emlrtRSInfo nd_emlrtRSI = {
    52, "schur",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\schur.m"};

static emlrtRSInfo od_emlrtRSI = {
    54, "schur",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\schur.m"};

static emlrtRSInfo pd_emlrtRSI = {
    83, "schur",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\schur.m"};

static emlrtRSInfo qd_emlrtRSI = {18, "xgehrd",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgehrd.m"};

static emlrtRTEInfo i_emlrtRTEI = {
    24, 5, "isSymmetricPositiveSemiDefinite",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\isSymmetricPosit"
    "iveSemiDefinite.m"};

static emlrtRTEInfo j_emlrtRTEI = {
    7, 3, "validateDataDims",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\validateDataDims"
    ".m"};

void checkCovariance(const emlrtStack *sp, const real_T b_value[9],
                     const real_T dims[2])
{
  static const char_T fname[13] = {'L', 'A', 'P', 'A', 'C', 'K', 'E',
                                   '_', 'd', 's', 'y', 'e', 'v'};
  __m128d r;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack i_st;
  emlrtStack st;
  creal_T b_d[3];
  real_T A[9];
  real_T y[9];
  real_T work[3];
  real_T dv[2];
  real_T tau[2];
  real_T absx;
  real_T d;
  real_T tol;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T idx;
  boolean_T b_y[3];
  boolean_T x[2];
  boolean_T c_y;
  boolean_T exitg1;
  boolean_T notPositiveSemidefinite;
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
  i_st.prev = &h_st;
  i_st.tls = h_st.tls;
  st.site = &sc_emlrtRSI;
  b_st.site = &oc_emlrtRSI;
  c_st.site = &pc_emlrtRSI;
  notPositiveSemidefinite = true;
  i2 = 0;
  exitg1 = false;
  while ((!exitg1) && (i2 < 9)) {
    if ((!muDoubleScalarIsInf(b_value[i2])) &&
        (!muDoubleScalarIsNaN(b_value[i2]))) {
      i2++;
    } else {
      notPositiveSemidefinite = false;
      exitg1 = true;
    }
  }
  if (!notPositiveSemidefinite) {
    emlrtErrorWithMessageIdR2018a(
        &c_st, &f_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 16, "MeasurementNoise");
  }
  st.site = &tc_emlrtRSI;
  x[0] = (dims[0] != 3.0);
  x[1] = (dims[1] != 3.0);
  notPositiveSemidefinite = false;
  i2 = 0;
  exitg1 = false;
  while ((!exitg1) && (i2 < 2)) {
    if (x[i2]) {
      notPositiveSemidefinite = true;
      exitg1 = true;
    } else {
      i2++;
    }
  }
  if (notPositiveSemidefinite) {
    emlrtErrorWithMessageIdR2018a(
        &st, &j_emlrtRTEI, "shared_tracking:KalmanFilter:invalidCovarianceDims",
        "shared_tracking:KalmanFilter:invalidCovarianceDims", 7, 4, 16,
        "MeasurementNoise", 6, dims[0], 6, dims[1]);
  }
  st.site = &uc_emlrtRSI;
  work[0] = muDoubleScalarAbs(b_value[0]);
  work[1] = muDoubleScalarAbs(b_value[4]);
  work[2] = muDoubleScalarAbs(b_value[8]);
  if (!muDoubleScalarIsNaN(work[0])) {
    idx = 1;
  } else {
    idx = 0;
    i2 = 2;
    exitg1 = false;
    while ((!exitg1) && (i2 < 4)) {
      if (!muDoubleScalarIsNaN(work[i2 - 1])) {
        idx = i2;
        exitg1 = true;
      } else {
        i2++;
      }
    }
  }
  if (idx == 0) {
    absx = work[0];
  } else {
    absx = work[idx - 1];
    i2 = idx + 1;
    for (i = i2; i < 4; i++) {
      d = work[i - 1];
      if (absx < d) {
        absx = d;
      }
    }
  }
  if (muDoubleScalarIsInf(absx) || muDoubleScalarIsNaN(absx)) {
    absx = rtNaN;
  } else if (absx < 4.4501477170144028E-308) {
    absx = 4.94065645841247E-324;
  } else {
    frexp(absx, &i1);
    absx = ldexp(1.0, i1 - 53);
  }
  tol = 100.0 * absx;
  for (i = 0; i < 3; i++) {
    A[3 * i] = b_value[i];
    A[3 * i + 1] = b_value[i + 3];
    A[3 * i + 2] = b_value[i + 6];
  }
  r = _mm_loadu_pd(&A[0]);
  _mm_storeu_pd(&tau[0], _mm_sub_pd(_mm_loadu_pd(&b_value[0]), r));
  dv[0] = muDoubleScalarAbs(tau[0]);
  dv[1] = muDoubleScalarAbs(tau[1]);
  r = _mm_loadu_pd(&dv[0]);
  _mm_storeu_pd(&y[0], r);
  r = _mm_loadu_pd(&A[2]);
  _mm_storeu_pd(&tau[0], _mm_sub_pd(_mm_loadu_pd(&b_value[2]), r));
  dv[0] = muDoubleScalarAbs(tau[0]);
  dv[1] = muDoubleScalarAbs(tau[1]);
  r = _mm_loadu_pd(&dv[0]);
  _mm_storeu_pd(&y[2], r);
  r = _mm_loadu_pd(&A[4]);
  _mm_storeu_pd(&tau[0], _mm_sub_pd(_mm_loadu_pd(&b_value[4]), r));
  dv[0] = muDoubleScalarAbs(tau[0]);
  dv[1] = muDoubleScalarAbs(tau[1]);
  r = _mm_loadu_pd(&dv[0]);
  _mm_storeu_pd(&y[4], r);
  r = _mm_loadu_pd(&A[6]);
  _mm_storeu_pd(&tau[0], _mm_sub_pd(_mm_loadu_pd(&b_value[6]), r));
  dv[0] = muDoubleScalarAbs(tau[0]);
  dv[1] = muDoubleScalarAbs(tau[1]);
  r = _mm_loadu_pd(&dv[0]);
  _mm_storeu_pd(&y[6], r);
  y[8] = muDoubleScalarAbs(b_value[8] - A[8]);
  b_st.site = &vc_emlrtRSI;
  absx = muDoubleScalarSqrt(tol);
  b_st.site = &vc_emlrtRSI;
  c_st.site = &xc_emlrtRSI;
  b_y[0] = true;
  b_y[1] = true;
  b_y[2] = true;
  i2 = 3;
  for (i = 0; i < 3; i++) {
    idx = i2;
    i1 = i2 - 2;
    i2 += 3;
    d_st.site = &yc_emlrtRSI;
    if ((i1 <= idx) && (idx > 2147483646)) {
      e_st.site = &fb_emlrtRSI;
      check_forloop_overflow_error(&e_st);
    }
    exitg1 = false;
    while ((!exitg1) && (i1 <= idx)) {
      if (!(y[i1 - 1] < absx)) {
        b_y[i] = false;
        exitg1 = true;
      } else {
        i1++;
      }
    }
  }
  c_y = true;
  i2 = 0;
  exitg1 = false;
  while ((!exitg1) && (i2 <= 2)) {
    if (!b_y[i2]) {
      c_y = false;
      exitg1 = true;
    } else {
      i2++;
    }
  }
  __m128d r1;
  b_st.site = &wc_emlrtRSI;
  r = _mm_loadu_pd(&A[0]);
  r1 = _mm_set1_pd(2.0);
  _mm_storeu_pd(&A[0],
                _mm_div_pd(_mm_add_pd(_mm_loadu_pd(&b_value[0]), r), r1));
  r = _mm_loadu_pd(&A[2]);
  _mm_storeu_pd(&A[2],
                _mm_div_pd(_mm_add_pd(_mm_loadu_pd(&b_value[2]), r), r1));
  r = _mm_loadu_pd(&A[4]);
  _mm_storeu_pd(&A[4],
                _mm_div_pd(_mm_add_pd(_mm_loadu_pd(&b_value[4]), r), r1));
  r = _mm_loadu_pd(&A[6]);
  _mm_storeu_pd(&A[6],
                _mm_div_pd(_mm_add_pd(_mm_loadu_pd(&b_value[6]), r), r1));
  A[8] = (b_value[8] + A[8]) / 2.0;
  c_st.site = &ad_emlrtRSI;
  if (anyNonFinite(A)) {
    b_d[0].re = rtNaN;
    b_d[1].re = rtNaN;
    b_d[2].re = rtNaN;
  } else {
    int32_T exitg2;
    notPositiveSemidefinite = true;
    i2 = 0;
    exitg1 = false;
    while ((!exitg1) && (i2 < 3)) {
      idx = 0;
      do {
        exitg2 = 0;
        if (idx <= i2) {
          if (!(A[idx + 3 * i2] == A[i2 + 3 * idx])) {
            notPositiveSemidefinite = false;
            exitg2 = 1;
          } else {
            idx++;
          }
        } else {
          i2++;
          exitg2 = 2;
        }
      } while (exitg2 == 0);
      if (exitg2 == 1) {
        exitg1 = true;
      }
    }
    if (notPositiveSemidefinite) {
      ptrdiff_t n_t;
      c_st.site = &bd_emlrtRSI;
      d_st.site = &hd_emlrtRSI;
      e_st.site = &jd_emlrtRSI;
      n_t = (ptrdiff_t)3;
      n_t = LAPACKE_dsyev(102, 'N', 'L', n_t, &A[0], n_t, &work[0]);
      f_st.site = &gb_emlrtRSI;
      if ((int32_T)n_t < 0) {
        if ((int32_T)n_t == -1010) {
          emlrtErrorWithMessageIdR2018a(&f_st, &h_emlrtRTEI, "MATLAB:nomem",
                                        "MATLAB:nomem", 0);
        } else {
          emlrtErrorWithMessageIdR2018a(&f_st, &g_emlrtRTEI,
                                        "Coder:toolbox:LAPACKCallErrorInfo",
                                        "Coder:toolbox:LAPACKCallErrorInfo", 5,
                                        4, 13, &fname[0], 12, (int32_T)n_t);
        }
      }
      b_d[0].re = work[0];
      b_d[1].re = work[1];
      b_d[2].re = work[2];
      if (((int32_T)n_t != 0) && (!emlrtSetWarningFlag(&c_st))) {
        d_st.site = &id_emlrtRSI;
        warning(&d_st);
      }
    } else {
      notPositiveSemidefinite = true;
      i2 = 0;
      exitg1 = false;
      while ((!exitg1) && (i2 < 3)) {
        idx = 0;
        do {
          exitg2 = 0;
          if (idx <= i2) {
            if (!(A[idx + 3 * i2] == -A[i2 + 3 * idx])) {
              notPositiveSemidefinite = false;
              exitg2 = 1;
            } else {
              idx++;
            }
          } else {
            i2++;
            exitg2 = 2;
          }
        } while (exitg2 == 0);
        if (exitg2 == 1) {
          exitg1 = true;
        }
      }
      if (notPositiveSemidefinite) {
        c_st.site = &cd_emlrtRSI;
        d_st.site = &kd_emlrtRSI;
        e_st.site = &ld_emlrtRSI;
        f_st.site = &md_emlrtRSI;
        if (anyNonFinite(A)) {
          for (i = 0; i < 9; i++) {
            A[i] = rtNaN;
          }
          i2 = 2;
          for (i = 0; i < 2; i++) {
            if (i2 <= 3) {
              memset(&A[(i * 3 + i2) + -1], 0,
                     (uint32_T)(-i2 + 4) * sizeof(real_T));
            }
            i2++;
          }
        } else {
          f_st.site = &nd_emlrtRSI;
          g_st.site = &qd_emlrtRSI;
          work[0] = 0.0;
          work[1] = 0.0;
          work[2] = 0.0;
          for (i = 0; i < 2; i++) {
            int32_T alpha1_tmp_tmp;
            int32_T in;
            int32_T lastv;
            in = (i + 1) * 3;
            alpha1_tmp_tmp = i + 3 * i;
            absx = A[alpha1_tmp_tmp + 1];
            h_st.site = &rd_emlrtRSI;
            d = xzlarfg(&h_st, 2 - i, &absx, A, i * 3 + 3);
            tau[i] = d;
            A[alpha1_tmp_tmp + 1] = 1.0;
            h_st.site = &sd_emlrtRSI;
            if (d != 0.0) {
              lastv = 2 - i;
              idx = (alpha1_tmp_tmp - i) + 2;
              while ((lastv > 0) && (A[idx] == 0.0)) {
                lastv--;
                idx--;
              }
              idx = 3;
              exitg1 = false;
              while ((!exitg1) && (idx > 0)) {
                i2 = in + idx;
                i1 = i2;
                do {
                  exitg2 = 0;
                  if (i1 <= i2 + (lastv - 1) * 3) {
                    if (A[i1 - 1] != 0.0) {
                      exitg2 = 1;
                    } else {
                      i1 += 3;
                    }
                  } else {
                    idx--;
                    exitg2 = 2;
                  }
                } while (exitg2 == 0);
                if (exitg2 == 1) {
                  exitg1 = true;
                }
              }
            } else {
              lastv = 0;
              idx = 0;
            }
            if (lastv > 0) {
              i_st.site = &ud_emlrtRSI;
              xgemv(&i_st, idx, lastv, A, in + 1, A, alpha1_tmp_tmp + 2, work);
              i_st.site = &vd_emlrtRSI;
              xgerc(&i_st, idx, lastv, -tau[i], work, alpha1_tmp_tmp + 2, A,
                    in + 1);
            }
            h_st.site = &td_emlrtRSI;
            xzlarf(&h_st, 2 - i, 2 - i, alpha1_tmp_tmp + 2, tau[i], A,
                   (i + in) + 2, work);
            A[alpha1_tmp_tmp + 1] = absx;
          }
          f_st.site = &od_emlrtRSI;
          i2 = xhseqr(A);
          if ((i2 != 0) && (!emlrtSetWarningFlag(&e_st))) {
            f_st.site = &pd_emlrtRSI;
            b_warning(&f_st);
          }
        }
        i2 = 1;
        do {
          exitg2 = 0;
          if (i2 <= 3) {
            boolean_T guard1;
            guard1 = false;
            if (i2 != 3) {
              absx = A[i2 + 3 * (i2 - 1)];
              if (absx != 0.0) {
                absx = muDoubleScalarAbs(absx);
                b_d[i2 - 1].re = 0.0;
                b_d[i2 - 1].im = absx;
                b_d[i2].re = 0.0;
                b_d[i2].im = -absx;
                i2 += 2;
              } else {
                guard1 = true;
              }
            } else {
              guard1 = true;
            }
            if (guard1) {
              b_d[i2 - 1].re = 0.0;
              b_d[i2 - 1].im = 0.0;
              i2++;
            }
          } else {
            exitg2 = 1;
          }
        } while (exitg2 == 0);
      } else {
        c_st.site = &dd_emlrtRSI;
        eigStandard(&c_st, A, b_d);
      }
    }
  }
  b_y[0] = (b_d[0].re < -tol);
  b_y[1] = (b_d[1].re < -tol);
  b_y[2] = (b_d[2].re < -tol);
  notPositiveSemidefinite = false;
  i2 = 0;
  exitg1 = false;
  while ((!exitg1) && (i2 < 3)) {
    if (b_y[i2]) {
      notPositiveSemidefinite = true;
      exitg1 = true;
    } else {
      i2++;
    }
  }
  if (notPositiveSemidefinite || (!c_y)) {
    emlrtErrorWithMessageIdR2018a(
        &st, &i_emlrtRTEI,
        "shared_tracking:KalmanFilter:invalidCovarianceValues",
        "shared_tracking:KalmanFilter:invalidCovarianceValues", 3, 4, 16,
        "MeasurementNoise");
  }
}
