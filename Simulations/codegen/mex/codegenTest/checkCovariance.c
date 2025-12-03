/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkCovariance.c
 *
 * Code generation for function 'checkCovariance'
 *
 */

/* Include files */
#include "checkCovariance.h"
#include "anyNonFinite.h"
#include "codegenTest_data.h"
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
#include <math.h>
#include <stddef.h>
#include <string.h>
#include <xmmintrin.h>

/* Variable Definitions */
static emlrtRSInfo lb_emlrtRSI = {
    62,              /* lineNo */
    "ceval_xsyheev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xsyheev.m" /* pathName */
};

static emlrtRSInfo xc_emlrtRSI = {
    7,                 /* lineNo */
    "checkCovariance", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\checkCovariance."
    "m" /* pathName */
};

static emlrtRSInfo yc_emlrtRSI = {
    8,                 /* lineNo */
    "checkCovariance", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\checkCovariance."
    "m" /* pathName */
};

static emlrtRSInfo ad_emlrtRSI = {
    9,                 /* lineNo */
    "checkCovariance", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\checkCovariance."
    "m" /* pathName */
};

static emlrtRSInfo bd_emlrtRSI = {
    18,                                /* lineNo */
    "isSymmetricPositiveSemiDefinite", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\isSymmetricPosit"
    "iveSemiDefinite.m" /* pathName */
};

static emlrtRSInfo cd_emlrtRSI = {
    20,                                /* lineNo */
    "isSymmetricPositiveSemiDefinite", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\isSymmetricPosit"
    "iveSemiDefinite.m" /* pathName */
};

static emlrtRSInfo dd_emlrtRSI =
    {
        13,    /* lineNo */
        "all", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\ops\\all.m" /* pathName
                                                                        */
};

static emlrtRSInfo ed_emlrtRSI =
    {
        143,        /* lineNo */
        "allOrAny", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\allOrAny."
        "m" /* pathName */
};

static emlrtRSInfo fd_emlrtRSI = {
    81,    /* lineNo */
    "eig", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m" /* pathName
                                                                       */
};

static emlrtRSInfo gd_emlrtRSI = {
    127,   /* lineNo */
    "eig", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m" /* pathName
                                                                       */
};

static emlrtRSInfo hd_emlrtRSI = {
    135,   /* lineNo */
    "eig", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m" /* pathName
                                                                       */
};

static emlrtRSInfo id_emlrtRSI = {
    143,   /* lineNo */
    "eig", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m" /* pathName
                                                                       */
};

static emlrtRSInfo md_emlrtRSI = {
    13,                     /* lineNo */
    "eigHermitianStandard", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigHerm"
    "itianStandard.m" /* pathName */
};

static emlrtRSInfo nd_emlrtRSI = {
    40,                     /* lineNo */
    "eigHermitianStandard", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigHerm"
    "itianStandard.m" /* pathName */
};

static emlrtRSInfo od_emlrtRSI = {
    8,         /* lineNo */
    "xsyheev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xsyheev.m" /* pathName */
};

static emlrtRSInfo pd_emlrtRSI = {
    10,                         /* lineNo */
    "eigSkewHermitianStandard", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigSkew"
    "HermitianStandard.m" /* pathName */
};

static emlrtRSInfo qd_emlrtRSI = {
    19,                             /* lineNo */
    "eigRealSkewSymmetricStandard", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigReal"
    "SkewSymmetricStandard.m" /* pathName */
};

static emlrtRSInfo rd_emlrtRSI = {
    35,      /* lineNo */
    "schur", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\schur.m" /* pathName
                                                                         */
};

static emlrtRSInfo sd_emlrtRSI = {
    52,      /* lineNo */
    "schur", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\schur.m" /* pathName
                                                                         */
};

static emlrtRSInfo td_emlrtRSI = {
    54,      /* lineNo */
    "schur", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\schur.m" /* pathName
                                                                         */
};

static emlrtRSInfo ud_emlrtRSI = {
    83,      /* lineNo */
    "schur", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\schur.m" /* pathName
                                                                         */
};

static emlrtRSInfo vd_emlrtRSI = {
    18,       /* lineNo */
    "xgehrd", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgehrd.m" /* pathName */
};

static emlrtRTEInfo j_emlrtRTEI = {
    24,                                /* lineNo */
    5,                                 /* colNo */
    "isSymmetricPositiveSemiDefinite", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\isSymmetricPosit"
    "iveSemiDefinite.m" /* pName */
};

static emlrtRTEInfo k_emlrtRTEI = {
    7,                  /* lineNo */
    3,                  /* colNo */
    "validateDataDims", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\validateDataDims"
    ".m" /* pName */
};

/* Function Definitions */
void checkCovariance(const emlrtStack *sp, const real32_T b_value[9],
                     const real32_T dims[2])
{
  static const char_T fname[13] = {'L', 'A', 'P', 'A', 'C', 'K', 'E',
                                   '_', 's', 's', 'y', 'e', 'v'};
  __m128 r;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack i_st;
  emlrtStack st;
  creal32_T d[3];
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T idx;
  real32_T A[9];
  real32_T y[9];
  real32_T fv[4];
  real32_T fv1[4];
  real32_T work[3];
  real32_T absx;
  real32_T f;
  real32_T tol;
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
  st.site = &xc_emlrtRSI;
  b_st.site = &eb_emlrtRSI;
  c_st.site = &fb_emlrtRSI;
  notPositiveSemidefinite = true;
  i2 = 0;
  exitg1 = false;
  while ((!exitg1) && (i2 < 9)) {
    if ((!muSingleScalarIsInf(b_value[i2])) &&
        (!muSingleScalarIsNaN(b_value[i2]))) {
      i2++;
    } else {
      notPositiveSemidefinite = false;
      exitg1 = true;
    }
  }
  if (!notPositiveSemidefinite) {
    emlrtErrorWithMessageIdR2018a(
        &c_st, &e_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 16, "MeasurementNoise");
  }
  st.site = &yc_emlrtRSI;
  x[0] = (dims[0] != 3.0F);
  x[1] = (dims[1] != 3.0F);
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
        &st, &k_emlrtRTEI, "shared_tracking:KalmanFilter:invalidCovarianceDims",
        "shared_tracking:KalmanFilter:invalidCovarianceDims", 7, 4, 16,
        "MeasurementNoise", 6, (real_T)dims[0], 6, (real_T)dims[1]);
  }
  st.site = &ad_emlrtRSI;
  work[0] = muSingleScalarAbs(b_value[0]);
  work[1] = muSingleScalarAbs(b_value[4]);
  work[2] = muSingleScalarAbs(b_value[8]);
  if (!muSingleScalarIsNaN(work[0])) {
    idx = 1;
  } else {
    idx = 0;
    i2 = 2;
    exitg1 = false;
    while ((!exitg1) && (i2 < 4)) {
      if (!muSingleScalarIsNaN(work[i2 - 1])) {
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
      f = work[i - 1];
      if (absx < f) {
        absx = f;
      }
    }
  }
  if (muSingleScalarIsInf(absx) || muSingleScalarIsNaN(absx)) {
    absx = rtNaNF;
  } else if (absx < 2.3509887E-38F) {
    absx = 1.4013E-45F;
  } else {
    frexpf(absx, &i1);
    absx = ldexpf(1.0F, i1 - 24);
  }
  tol = 100.0F * absx;
  for (i = 0; i < 3; i++) {
    A[3 * i] = b_value[i];
    A[3 * i + 1] = b_value[i + 3];
    A[3 * i + 2] = b_value[i + 6];
  }
  r = _mm_loadu_ps(&A[0]);
  _mm_storeu_ps(&fv[0], _mm_sub_ps(_mm_loadu_ps(&b_value[0]), r));
  fv1[0] = muSingleScalarAbs(fv[0]);
  fv1[1] = muSingleScalarAbs(fv[1]);
  fv1[2] = muSingleScalarAbs(fv[2]);
  fv1[3] = muSingleScalarAbs(fv[3]);
  r = _mm_loadu_ps(&fv1[0]);
  _mm_storeu_ps(&y[0], r);
  r = _mm_loadu_ps(&A[4]);
  _mm_storeu_ps(&fv[0], _mm_sub_ps(_mm_loadu_ps(&b_value[4]), r));
  fv1[0] = muSingleScalarAbs(fv[0]);
  fv1[1] = muSingleScalarAbs(fv[1]);
  fv1[2] = muSingleScalarAbs(fv[2]);
  fv1[3] = muSingleScalarAbs(fv[3]);
  r = _mm_loadu_ps(&fv1[0]);
  _mm_storeu_ps(&y[4], r);
  y[8] = muSingleScalarAbs(b_value[8] - A[8]);
  b_st.site = &bd_emlrtRSI;
  absx = muSingleScalarSqrt(tol);
  b_st.site = &bd_emlrtRSI;
  c_st.site = &dd_emlrtRSI;
  b_y[0] = true;
  b_y[1] = true;
  b_y[2] = true;
  i2 = 3;
  for (i = 0; i < 3; i++) {
    idx = i2;
    i1 = i2 - 2;
    i2 += 3;
    d_st.site = &ed_emlrtRSI;
    if ((i1 <= idx) && (idx > 2147483646)) {
      e_st.site = &kb_emlrtRSI;
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
  __m128 r1;
  r = _mm_loadu_ps(&A[0]);
  r1 = _mm_set1_ps(2.0F);
  _mm_storeu_ps(&A[0],
                _mm_div_ps(_mm_add_ps(_mm_loadu_ps(&b_value[0]), r), r1));
  r = _mm_loadu_ps(&A[4]);
  _mm_storeu_ps(&A[4],
                _mm_div_ps(_mm_add_ps(_mm_loadu_ps(&b_value[4]), r), r1));
  A[8] = (b_value[8] + A[8]) / 2.0F;
  b_st.site = &cd_emlrtRSI;
  c_st.site = &fd_emlrtRSI;
  if (anyNonFinite(A)) {
    d[0].re = rtNaNF;
    d[1].re = rtNaNF;
    d[2].re = rtNaNF;
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
      c_st.site = &gd_emlrtRSI;
      d_st.site = &md_emlrtRSI;
      e_st.site = &od_emlrtRSI;
      n_t = (ptrdiff_t)3;
      n_t = LAPACKE_ssyev(102, 'N', 'L', n_t, &A[0], n_t, &work[0]);
      f_st.site = &lb_emlrtRSI;
      if ((int32_T)n_t < 0) {
        if ((int32_T)n_t == -1010) {
          emlrtErrorWithMessageIdR2018a(&f_st, &i_emlrtRTEI, "MATLAB:nomem",
                                        "MATLAB:nomem", 0);
        } else {
          emlrtErrorWithMessageIdR2018a(&f_st, &h_emlrtRTEI,
                                        "Coder:toolbox:LAPACKCallErrorInfo",
                                        "Coder:toolbox:LAPACKCallErrorInfo", 5,
                                        4, 13, &fname[0], 12, (int32_T)n_t);
        }
      }
      d[0].re = work[0];
      d[1].re = work[1];
      d[2].re = work[2];
      if (((int32_T)n_t != 0) && (!emlrtSetWarningFlag(&c_st))) {
        d_st.site = &nd_emlrtRSI;
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
        c_st.site = &hd_emlrtRSI;
        d_st.site = &pd_emlrtRSI;
        e_st.site = &qd_emlrtRSI;
        f_st.site = &rd_emlrtRSI;
        if (anyNonFinite(A)) {
          for (i = 0; i < 9; i++) {
            A[i] = rtNaNF;
          }
          i2 = 2;
          for (i = 0; i < 2; i++) {
            if (i2 <= 3) {
              memset(&A[(i * 3 + i2) + -1], 0,
                     (uint32_T)(-i2 + 4) * sizeof(real32_T));
            }
            i2++;
          }
        } else {
          real32_T tau[2];
          f_st.site = &sd_emlrtRSI;
          g_st.site = &vd_emlrtRSI;
          work[0] = 0.0F;
          work[1] = 0.0F;
          work[2] = 0.0F;
          for (i = 0; i < 2; i++) {
            int32_T alpha1_tmp_tmp;
            int32_T in;
            int32_T lastv;
            in = (i + 1) * 3;
            alpha1_tmp_tmp = i + 3 * i;
            absx = A[alpha1_tmp_tmp + 1];
            h_st.site = &wd_emlrtRSI;
            f = xzlarfg(&h_st, 2 - i, &absx, A, i * 3 + 3);
            tau[i] = f;
            A[alpha1_tmp_tmp + 1] = 1.0F;
            h_st.site = &xd_emlrtRSI;
            if (f != 0.0F) {
              lastv = 2 - i;
              idx = (alpha1_tmp_tmp - i) + 2;
              while ((lastv > 0) && (A[idx] == 0.0F)) {
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
                    if (A[i1 - 1] != 0.0F) {
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
              i_st.site = &ae_emlrtRSI;
              xgemv(&i_st, idx, lastv, A, in + 1, A, alpha1_tmp_tmp + 2, work);
              i_st.site = &be_emlrtRSI;
              xgerc(&i_st, idx, lastv, -tau[i], work, alpha1_tmp_tmp + 2, A,
                    in + 1);
            }
            h_st.site = &yd_emlrtRSI;
            xzlarf(&h_st, 2 - i, 2 - i, alpha1_tmp_tmp + 2, tau[i], A,
                   (i + in) + 2, work);
            A[alpha1_tmp_tmp + 1] = absx;
          }
          f_st.site = &td_emlrtRSI;
          i2 = xhseqr(A);
          if ((i2 != 0) && (!emlrtSetWarningFlag(&e_st))) {
            f_st.site = &ud_emlrtRSI;
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
              if (absx != 0.0F) {
                absx = muSingleScalarAbs(absx);
                d[i2 - 1].re = 0.0F;
                d[i2 - 1].im = absx;
                d[i2].re = 0.0F;
                d[i2].im = -absx;
                i2 += 2;
              } else {
                guard1 = true;
              }
            } else {
              guard1 = true;
            }
            if (guard1) {
              d[i2 - 1].re = 0.0F;
              d[i2 - 1].im = 0.0F;
              i2++;
            }
          } else {
            exitg2 = 1;
          }
        } while (exitg2 == 0);
      } else {
        c_st.site = &id_emlrtRSI;
        eigStandard(&c_st, A, d);
      }
    }
  }
  b_y[0] = (d[0].re < -tol);
  b_y[1] = (d[1].re < -tol);
  b_y[2] = (d[2].re < -tol);
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
        &st, &j_emlrtRTEI,
        "shared_tracking:KalmanFilter:invalidCovarianceValues",
        "shared_tracking:KalmanFilter:invalidCovarianceValues", 3, 4, 16,
        "MeasurementNoise");
  }
}

/* End of code generation (checkCovariance.c) */
