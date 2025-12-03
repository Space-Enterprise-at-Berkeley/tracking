/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xnrm2.c
 *
 * Code generation for function 'xnrm2'
 *
 */

/* Include files */
#include "xnrm2.h"
#include "codegenTest_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Variable Definitions */
static emlrtRSInfo sb_emlrtRSI = {
    23,      /* lineNo */
    "xnrm2", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+blas\\xnrm2."
    "m" /* pathName */
};

static emlrtRSInfo tb_emlrtRSI = {
    38,      /* lineNo */
    "xnrm2", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "refblas\\xnrm2.m" /* pathName */
};

/* Function Definitions */
real32_T b_xnrm2(int32_T n, const real32_T x[3])
{
  real32_T y;
  y = 0.0F;
  if (n >= 1) {
    if (n == 1) {
      y = muSingleScalarAbs(x[1]);
    } else {
      real32_T absxk;
      real32_T scale;
      real32_T t;
      scale = 1.29246971E-26F;
      absxk = muSingleScalarAbs(x[1]);
      if (absxk > 1.29246971E-26F) {
        y = 1.0F;
        scale = absxk;
      } else {
        t = absxk / 1.29246971E-26F;
        y = t * t;
      }
      absxk = muSingleScalarAbs(x[2]);
      if (absxk > scale) {
        t = scale / absxk;
        y = y * t * t + 1.0F;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
      y = scale * muSingleScalarSqrt(y);
    }
  }
  return y;
}

real32_T xnrm2(const emlrtStack *sp, int32_T n, const real32_T x[9],
               int32_T ix0)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int32_T k;
  real32_T y;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  st.site = &sb_emlrtRSI;
  y = 0.0F;
  if (n >= 1) {
    if (n == 1) {
      y = muSingleScalarAbs(x[ix0 - 1]);
    } else {
      int32_T kend;
      real32_T scale;
      scale = 1.29246971E-26F;
      kend = (ix0 + n) - 1;
      b_st.site = &tb_emlrtRSI;
      if ((ix0 <= kend) && (kend > 2147483646)) {
        c_st.site = &kb_emlrtRSI;
        check_forloop_overflow_error(&c_st);
      }
      for (k = ix0; k <= kend; k++) {
        real32_T absxk;
        absxk = muSingleScalarAbs(x[k - 1]);
        if (absxk > scale) {
          real32_T t;
          t = scale / absxk;
          y = y * t * t + 1.0F;
          scale = absxk;
        } else {
          real32_T t;
          t = absxk / scale;
          y += t * t;
        }
      }
      y = scale * muSingleScalarSqrt(y);
    }
  }
  return y;
}

/* End of code generation (xnrm2.c) */
