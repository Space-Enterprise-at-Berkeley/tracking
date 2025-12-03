/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlascl.c
 *
 * Code generation for function 'xzlascl'
 *
 */

/* Include files */
#include "xzlascl.h"
#include "codegenTest_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <xmmintrin.h>

/* Variable Definitions */
static emlrtRSInfo wb_emlrtRSI = {
    34,        /* lineNo */
    "xzlascl", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzlascl.m" /* pathName */
};

/* Function Definitions */
void b_xzlascl(const emlrtStack *sp, real32_T cfrom, real32_T cto, int32_T m,
               real32_T A[3])
{
  emlrtStack b_st;
  emlrtStack st;
  int32_T b_i;
  real32_T cfromc;
  real32_T ctoc;
  boolean_T notdone;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    int32_T i;
    int32_T scalarLB;
    int32_T vectorUB;
    real32_T cfrom1;
    real32_T cto1;
    real32_T mul;
    cfrom1 = cfromc * 1.97215226E-31F;
    cto1 = ctoc / 5.0706024E+30F;
    if ((muSingleScalarAbs(cfrom1) > muSingleScalarAbs(ctoc)) &&
        (ctoc != 0.0F)) {
      mul = 1.97215226E-31F;
      cfromc = cfrom1;
    } else if (muSingleScalarAbs(cto1) > muSingleScalarAbs(cfromc)) {
      mul = 5.0706024E+30F;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }
    st.site = &wb_emlrtRSI;
    if (m > 2147483646) {
      b_st.site = &kb_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }
    i = (uint8_T)m;
    scalarLB = ((uint8_T)m >> 2) << 2;
    vectorUB = scalarLB - 4;
    for (b_i = 0; b_i <= vectorUB; b_i += 4) {
      __m128 r;
      r = _mm_loadu_ps(&A[b_i]);
      _mm_storeu_ps(&A[b_i], _mm_mul_ps(r, _mm_set1_ps(mul)));
    }
    for (b_i = scalarLB; b_i < i; b_i++) {
      A[b_i] *= mul;
    }
  }
}

void xzlascl(const emlrtStack *sp, real32_T cfrom, real32_T cto, int32_T m,
             real32_T A[3], int32_T iA0)
{
  emlrtStack b_st;
  emlrtStack st;
  int32_T b_i;
  real32_T cfromc;
  real32_T ctoc;
  boolean_T notdone;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    int32_T i;
    int32_T scalarLB;
    int32_T vectorUB;
    real32_T cfrom1;
    real32_T cto1;
    real32_T mul;
    cfrom1 = cfromc * 1.97215226E-31F;
    cto1 = ctoc / 5.0706024E+30F;
    if ((muSingleScalarAbs(cfrom1) > muSingleScalarAbs(ctoc)) &&
        (ctoc != 0.0F)) {
      mul = 1.97215226E-31F;
      cfromc = cfrom1;
    } else if (muSingleScalarAbs(cto1) > muSingleScalarAbs(cfromc)) {
      mul = 5.0706024E+30F;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }
    st.site = &wb_emlrtRSI;
    if (m > 2147483646) {
      b_st.site = &kb_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }
    i = (uint8_T)m;
    scalarLB = ((uint8_T)m >> 2) << 2;
    vectorUB = scalarLB - 4;
    for (b_i = 0; b_i <= vectorUB; b_i += 4) {
      __m128 r;
      int32_T i1;
      i1 = (iA0 + b_i) - 1;
      r = _mm_loadu_ps(&A[i1]);
      _mm_storeu_ps(&A[i1], _mm_mul_ps(r, _mm_set1_ps(mul)));
    }
    for (b_i = scalarLB; b_i < i; b_i++) {
      vectorUB = (iA0 + b_i) - 1;
      A[vectorUB] *= mul;
    }
  }
}

/* End of code generation (xzlascl.c) */
