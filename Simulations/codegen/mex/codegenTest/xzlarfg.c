/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlarfg.c
 *
 * Code generation for function 'xzlarfg'
 *
 */

/* Include files */
#include "xzlarfg.h"
#include "codegenTest_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "mwmathutil.h"
#include <xmmintrin.h>

/* Variable Definitions */
static emlrtRSInfo mb_emlrtRSI = {
    81,        /* lineNo */
    "xzlarfg", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzlarfg.m" /* pathName */
};

static emlrtRSInfo nb_emlrtRSI = {
    71,        /* lineNo */
    "xzlarfg", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzlarfg.m" /* pathName */
};

static emlrtRSInfo ob_emlrtRSI = {
    68,        /* lineNo */
    "xzlarfg", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzlarfg.m" /* pathName */
};

static emlrtRSInfo pb_emlrtRSI = {
    53,        /* lineNo */
    "xzlarfg", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzlarfg.m" /* pathName */
};

static emlrtRSInfo qb_emlrtRSI = {
    41,        /* lineNo */
    "xzlarfg", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzlarfg.m" /* pathName */
};

static emlrtRSInfo rb_emlrtRSI = {
    20,        /* lineNo */
    "xzlarfg", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzlarfg.m" /* pathName */
};

/* Function Definitions */
real32_T b_xzlarfg(int32_T n, real32_T *alpha1, real32_T x[3])
{
  int32_T k;
  real32_T tau;
  tau = 0.0F;
  if (n > 0) {
    real32_T xnorm;
    xnorm = b_xnrm2(n - 1, x);
    if (xnorm != 0.0F) {
      real32_T beta1;
      beta1 = muSingleScalarHypot(*alpha1, xnorm);
      if (*alpha1 >= 0.0F) {
        beta1 = -beta1;
      }
      if (muSingleScalarAbs(beta1) < 9.86076132E-32F) {
        __m128 r;
        int32_T b_vectorUB;
        int32_T knt;
        int32_T scalarLB;
        int32_T vectorUB;
        knt = 0;
        scalarLB = (((n - 1) / 4) << 2) + 2;
        vectorUB = scalarLB - 4;
        do {
          knt++;
          for (k = 2; k <= vectorUB; k += 4) {
            r = _mm_loadu_ps(&x[k - 1]);
            _mm_storeu_ps(&x[k - 1],
                          _mm_mul_ps(_mm_set1_ps(1.01412048E+31F), r));
          }
          for (k = scalarLB; k <= n; k++) {
            x[k - 1] *= 1.01412048E+31F;
          }
          beta1 *= 1.01412048E+31F;
          *alpha1 *= 1.01412048E+31F;
        } while ((muSingleScalarAbs(beta1) < 9.86076132E-32F) && (knt < 20));
        beta1 = muSingleScalarHypot(*alpha1, b_xnrm2(n - 1, x));
        if (*alpha1 >= 0.0F) {
          beta1 = -beta1;
        }
        tau = (beta1 - *alpha1) / beta1;
        xnorm = 1.0F / (*alpha1 - beta1);
        b_vectorUB = scalarLB - 4;
        for (k = 2; k <= b_vectorUB; k += 4) {
          r = _mm_loadu_ps(&x[k - 1]);
          _mm_storeu_ps(&x[k - 1], _mm_mul_ps(_mm_set1_ps(xnorm), r));
        }
        for (k = scalarLB; k <= n; k++) {
          x[k - 1] *= xnorm;
        }
        for (k = 0; k < knt; k++) {
          beta1 *= 9.86076132E-32F;
        }
        *alpha1 = beta1;
      } else {
        int32_T b_vectorUB;
        int32_T vectorUB;
        tau = (beta1 - *alpha1) / beta1;
        xnorm = 1.0F / (*alpha1 - beta1);
        vectorUB = (((n - 1) / 4) << 2) + 2;
        b_vectorUB = vectorUB - 4;
        for (k = 2; k <= b_vectorUB; k += 4) {
          __m128 r;
          r = _mm_loadu_ps(&x[k - 1]);
          _mm_storeu_ps(&x[k - 1], _mm_mul_ps(_mm_set1_ps(xnorm), r));
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

real32_T xzlarfg(const emlrtStack *sp, int32_T n, real32_T *alpha1,
                 real32_T x[9], int32_T ix0)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  int32_T k;
  real32_T tau;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  tau = 0.0F;
  if (n > 0) {
    real32_T xnorm;
    st.site = &rb_emlrtRSI;
    xnorm = xnrm2(&st, n - 1, x, ix0);
    if (xnorm != 0.0F) {
      real32_T beta1;
      beta1 = muSingleScalarHypot(*alpha1, xnorm);
      if (*alpha1 >= 0.0F) {
        beta1 = -beta1;
      }
      if (muSingleScalarAbs(beta1) < 9.86076132E-32F) {
        __m128 r;
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
          st.site = &qb_emlrtRSI;
          b_st.site = &ub_emlrtRSI;
          c_st.site = &vb_emlrtRSI;
          if (overflow) {
            d_st.site = &kb_emlrtRSI;
            check_forloop_overflow_error(&d_st);
          }
          scalarLB = ((b - ix0) + 1) / 4 * 4 + ix0;
          vectorUB = scalarLB - 4;
          for (k = ix0; k <= vectorUB; k += 4) {
            r = _mm_loadu_ps(&x[k - 1]);
            r = _mm_mul_ps(_mm_set1_ps(1.01412048E+31F), r);
            _mm_storeu_ps(&x[k - 1], r);
          }
          for (k = scalarLB; k <= b; k++) {
            x[k - 1] *= 1.01412048E+31F;
          }
          beta1 *= 1.01412048E+31F;
          *alpha1 *= 1.01412048E+31F;
        } while ((muSingleScalarAbs(beta1) < 9.86076132E-32F) && (knt < 20));
        st.site = &pb_emlrtRSI;
        xnorm = xnrm2(&st, n - 1, x, ix0);
        beta1 = muSingleScalarHypot(*alpha1, xnorm);
        if (*alpha1 >= 0.0F) {
          beta1 = -beta1;
        }
        tau = (beta1 - *alpha1) / beta1;
        xnorm = 1.0F / (*alpha1 - beta1);
        st.site = &ob_emlrtRSI;
        b_st.site = &ub_emlrtRSI;
        c_st.site = &vb_emlrtRSI;
        b_scalarLB = ((b - ix0) + 1) / 4 * 4 + ix0;
        scalarLB = b_scalarLB - 4;
        for (k = ix0; k <= scalarLB; k += 4) {
          r = _mm_loadu_ps(&x[k - 1]);
          r = _mm_mul_ps(_mm_set1_ps(xnorm), r);
          _mm_storeu_ps(&x[k - 1], r);
        }
        for (k = b_scalarLB; k <= b; k++) {
          x[k - 1] *= xnorm;
        }
        st.site = &nb_emlrtRSI;
        for (k = 0; k < knt; k++) {
          beta1 *= 9.86076132E-32F;
        }
        *alpha1 = beta1;
      } else {
        int32_T b_scalarLB;
        int32_T scalarLB;
        int32_T vectorUB;
        tau = (beta1 - *alpha1) / beta1;
        xnorm = 1.0F / (*alpha1 - beta1);
        st.site = &mb_emlrtRSI;
        b_st.site = &ub_emlrtRSI;
        scalarLB = (ix0 + n) - 2;
        c_st.site = &vb_emlrtRSI;
        if ((ix0 <= scalarLB) && (scalarLB > 2147483646)) {
          d_st.site = &kb_emlrtRSI;
          check_forloop_overflow_error(&d_st);
        }
        vectorUB = ((scalarLB - ix0) + 1) / 4 * 4 + ix0;
        b_scalarLB = vectorUB - 4;
        for (k = ix0; k <= b_scalarLB; k += 4) {
          __m128 r;
          r = _mm_loadu_ps(&x[k - 1]);
          r = _mm_mul_ps(_mm_set1_ps(xnorm), r);
          _mm_storeu_ps(&x[k - 1], r);
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

/* End of code generation (xzlarfg.c) */
