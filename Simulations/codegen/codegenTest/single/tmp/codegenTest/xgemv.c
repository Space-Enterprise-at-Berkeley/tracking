#include "xgemv.h"
#include "codegenTest_float_mex_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include <string.h>

static emlrtRSInfo xd_emlrtRSI = {58, "xgemv",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+refblas\\xgemv.m"};

void xgemv(const emlrtStack *sp, int32_T m, int32_T n, const real_T A[9],
           int32_T ia0, const real_T x[9], int32_T ix0, real_T y[3])
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
  st.site = &wd_emlrtRSI;
  if (m != 0) {
    int32_T i;
    int32_T ix;
    b_st.site = &yd_emlrtRSI;
    if (m > 2147483646) {
      c_st.site = &fb_emlrtRSI;
      check_forloop_overflow_error(&c_st);
    }
    ix = (uint8_T)m;
    if (ix - 1 >= 0) {
      memset(&y[0], 0, (uint32_T)ix * sizeof(real_T));
    }
    ix = ix0;
    i = ia0 + 3 * (n - 1);
    for (iac = ia0; iac <= i; iac += 3) {
      int32_T b;
      b = (iac + m) - 1;
      b_st.site = &xd_emlrtRSI;
      if ((iac <= b) && (b > 2147483646)) {
        c_st.site = &fb_emlrtRSI;
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
