/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xswap.c
 *
 * Code generation for function 'xswap'
 *
 */

/* Include files */
#include "xswap.h"
#include "codegenTest_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void xswap(const emlrtStack *sp, int32_T n, real32_T x[9], int32_T ix0,
           int32_T iy0)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int32_T i;
  int32_T k;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  st.site = &fg_emlrtRSI;
  b_st.site = &gg_emlrtRSI;
  if (n > 2147483646) {
    c_st.site = &kb_emlrtRSI;
    check_forloop_overflow_error(&c_st);
  }
  i = (uint8_T)n;
  for (k = 0; k < i; k++) {
    int32_T i1;
    int32_T temp_tmp;
    real32_T temp;
    temp_tmp = (ix0 + k) - 1;
    temp = x[temp_tmp];
    i1 = (iy0 + k) - 1;
    x[temp_tmp] = x[i1];
    x[i1] = temp;
  }
}

/* End of code generation (xswap.c) */
