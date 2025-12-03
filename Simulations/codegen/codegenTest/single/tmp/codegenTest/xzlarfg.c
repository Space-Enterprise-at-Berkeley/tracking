#include "xzlarfg.h"
#include "codegenTest_float_mex_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "mwmathutil.h"
#include <emmintrin.h>

static emlrtRSInfo hb_emlrtRSI = {81, "xzlarfg",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzlarfg.m"};

static emlrtRSInfo ib_emlrtRSI = {71, "xzlarfg",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzlarfg.m"};

static emlrtRSInfo jb_emlrtRSI = {68, "xzlarfg",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzlarfg.m"};

static emlrtRSInfo kb_emlrtRSI = {53, "xzlarfg",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzlarfg.m"};

static emlrtRSInfo lb_emlrtRSI = {41, "xzlarfg",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzlarfg.m"};

static emlrtRSInfo mb_emlrtRSI = {20, "xzlarfg",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzlarfg.m"};

real_T b_xzlarfg(int32_T n, real_T *alpha1, real_T x[3])
{
  real_T tau;
  int32_T k;
  tau = 0.0;
  if (n > 0) {
    real_T xnorm;
    xnorm = b_xnrm2(n - 1, x);
    if (xnorm != 0.0) {
      real_T beta1;
      beta1 = muDoubleScalarHypot(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        beta1 = -beta1;
      }
      if (muDoubleScalarAbs(beta1) < 1.0020841800044864E-292) {
        __m128d r;
        int32_T b_vectorUB;
        int32_T knt;
        int32_T scalarLB;
        int32_T vectorUB;
        knt = 0;
        scalarLB = (((n - 1) / 2) << 1) + 2;
        vectorUB = scalarLB - 2;
        do {
          knt++;
          for (k = 2; k <= vectorUB; k += 2) {
            r = _mm_loadu_pd(&x[k - 1]);
            _mm_storeu_pd(&x[k - 1],
                          _mm_mul_pd(_mm_set1_pd(9.9792015476736E+291), r));
          }
          for (k = scalarLB; k <= n; k++) {
            x[k - 1] *= 9.9792015476736E+291;
          }
          beta1 *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while ((muDoubleScalarAbs(beta1) < 1.0020841800044864E-292) &&
                 (knt < 20));
        beta1 = muDoubleScalarHypot(*alpha1, b_xnrm2(n - 1, x));
        if (*alpha1 >= 0.0) {
          beta1 = -beta1;
        }
        tau = (beta1 - *alpha1) / beta1;
        xnorm = 1.0 / (*alpha1 - beta1);
        b_vectorUB = scalarLB - 2;
        for (k = 2; k <= b_vectorUB; k += 2) {
          r = _mm_loadu_pd(&x[k - 1]);
          _mm_storeu_pd(&x[k - 1], _mm_mul_pd(_mm_set1_pd(xnorm), r));
        }
        for (k = scalarLB; k <= n; k++) {
          x[k - 1] *= xnorm;
        }
        for (k = 0; k < knt; k++) {
          beta1 *= 1.0020841800044864E-292;
        }
        *alpha1 = beta1;
      } else {
        int32_T b_vectorUB;
        int32_T vectorUB;
        tau = (beta1 - *alpha1) / beta1;
        xnorm = 1.0 / (*alpha1 - beta1);
        vectorUB = (((n - 1) / 2) << 1) + 2;
        b_vectorUB = vectorUB - 2;
        for (k = 2; k <= b_vectorUB; k += 2) {
          __m128d r;
          r = _mm_loadu_pd(&x[k - 1]);
          _mm_storeu_pd(&x[k - 1], _mm_mul_pd(_mm_set1_pd(xnorm), r));
        }
        for (k = vectorUB; k <= n; k++) {
          x[k - 1] *= xnorm;
        }
        *alpha1 = beta1;
      }
    }
  }
  return tau;
}

real_T xzlarfg(const emlrtStack *sp, int32_T n, real_T *alpha1, real_T x[9],
               int32_T ix0)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  real_T tau;
  int32_T k;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  tau = 0.0;
  if (n > 0) {
    real_T xnorm;
    st.site = &mb_emlrtRSI;
    xnorm = xnrm2(&st, n - 1, x, ix0);
    if (xnorm != 0.0) {
      real_T beta1;
      beta1 = muDoubleScalarHypot(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        beta1 = -beta1;
      }
      if (muDoubleScalarAbs(beta1) < 1.0020841800044864E-292) {
        __m128d r;
        int32_T b;
        int32_T b_scalarLB;
        int32_T knt;
        int32_T scalarLB;
        boolean_T overflow;
        knt = 0;
        b = (ix0 + n) - 2;
        overflow = ((ix0 <= b) && (b > 2147483646));
        do {
          int32_T vectorUB;
          knt++;
          st.site = &lb_emlrtRSI;
          b_st.site = &pb_emlrtRSI;
          c_st.site = &qb_emlrtRSI;
          if (overflow) {
            d_st.site = &fb_emlrtRSI;
            check_forloop_overflow_error(&d_st);
          }
          scalarLB = ((b - ix0) + 1) / 2 * 2 + ix0;
          vectorUB = scalarLB - 2;
          for (k = ix0; k <= vectorUB; k += 2) {
            r = _mm_loadu_pd(&x[k - 1]);
            r = _mm_mul_pd(_mm_set1_pd(9.9792015476736E+291), r);
            _mm_storeu_pd(&x[k - 1], r);
          }
          for (k = scalarLB; k <= b; k++) {
            x[k - 1] *= 9.9792015476736E+291;
          }
          beta1 *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while ((muDoubleScalarAbs(beta1) < 1.0020841800044864E-292) &&
                 (knt < 20));
        st.site = &kb_emlrtRSI;
        xnorm = xnrm2(&st, n - 1, x, ix0);
        beta1 = muDoubleScalarHypot(*alpha1, xnorm);
        if (*alpha1 >= 0.0) {
          beta1 = -beta1;
        }
        tau = (beta1 - *alpha1) / beta1;
        xnorm = 1.0 / (*alpha1 - beta1);
        st.site = &jb_emlrtRSI;
        b_st.site = &pb_emlrtRSI;
        c_st.site = &qb_emlrtRSI;
        b_scalarLB = ((b - ix0) + 1) / 2 * 2 + ix0;
        scalarLB = b_scalarLB - 2;
        for (k = ix0; k <= scalarLB; k += 2) {
          r = _mm_loadu_pd(&x[k - 1]);
          r = _mm_mul_pd(_mm_set1_pd(xnorm), r);
          _mm_storeu_pd(&x[k - 1], r);
        }
        for (k = b_scalarLB; k <= b; k++) {
          x[k - 1] *= xnorm;
        }
        st.site = &ib_emlrtRSI;
        for (k = 0; k < knt; k++) {
          beta1 *= 1.0020841800044864E-292;
        }
        *alpha1 = beta1;
      } else {
        int32_T b_scalarLB;
        int32_T scalarLB;
        int32_T vectorUB;
        tau = (beta1 - *alpha1) / beta1;
        xnorm = 1.0 / (*alpha1 - beta1);
        st.site = &hb_emlrtRSI;
        b_st.site = &pb_emlrtRSI;
        scalarLB = (ix0 + n) - 2;
        c_st.site = &qb_emlrtRSI;
        if ((ix0 <= scalarLB) && (scalarLB > 2147483646)) {
          d_st.site = &fb_emlrtRSI;
          check_forloop_overflow_error(&d_st);
        }
        vectorUB = ((scalarLB - ix0) + 1) / 2 * 2 + ix0;
        b_scalarLB = vectorUB - 2;
        for (k = ix0; k <= b_scalarLB; k += 2) {
          __m128d r;
          r = _mm_loadu_pd(&x[k - 1]);
          r = _mm_mul_pd(_mm_set1_pd(xnorm), r);
          _mm_storeu_pd(&x[k - 1], r);
        }
        for (k = vectorUB; k <= scalarLB; k++) {
          x[k - 1] *= xnorm;
        }
        *alpha1 = beta1;
      }
    }
  }
  return tau;
}
