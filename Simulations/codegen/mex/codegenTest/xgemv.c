/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgemv.c
 *
 * Code generation for function 'xgemv'
 *
 */

/* Include files */
#include "xgemv.h"
#include "codegenTest_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Variable Definitions */
static emlrtRSInfo de_emlrtRSI = {
    58,      /* lineNo */
    "xgemv", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "refblas\\xgemv.m" /* pathName */
};

/* Function Definitions */
void xgemv(const emlrtStack *sp, int32_T m, int32_T n, const real32_T A[9],
           int32_T ia0, const real32_T x[9], int32_T ix0, real32_T y[3])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int32_T ia;
  int32_T iac;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  st.site = &ce_emlrtRSI;
  if (m != 0) {
    int32_T i;
    int32_T ix;
    b_st.site = &ee_emlrtRSI;
    if (m > 2147483646) {
      c_st.site = &kb_emlrtRSI;
      check_forloop_overflow_error(&c_st);
    }
    ix = (uint8_T)m;
    if (ix - 1 >= 0) {
      memset(&y[0], 0, (uint32_T)ix * sizeof(real32_T));
    }
    ix = ix0;
    i = ia0 + 3 * (n - 1);
    for (iac = ia0; iac <= i; iac += 3) {
      int32_T b;
      b = (iac + m) - 1;
      b_st.site = &de_emlrtRSI;
      if ((iac <= b) && (b > 2147483646)) {
        c_st.site = &kb_emlrtRSI;
        check_forloop_overflow_error(&c_st);
      }
      for (ia = iac; ia <= b; ia++) {
        int32_T i1;
        i1 = ia - iac;
        y[i1] += A[ia - 1] * x[ix - 1];
      }
      ix++;
    }
  }
}

/* End of code generation (xgemv.c) */
