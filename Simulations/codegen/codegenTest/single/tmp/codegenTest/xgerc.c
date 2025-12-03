#include "xgerc.h"
#include "codegenTest_float_mex_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>

void xgerc(const emlrtStack *sp, int32_T m, int32_T n, real_T alpha1,
           const real_T x[3], int32_T iy0, real_T A[9], int32_T ia0)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack st;
  int32_T ijA;
  int32_T j;
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
  st.site = &ae_emlrtRSI;
  b_st.site = &be_emlrtRSI;
  c_st.site = &ce_emlrtRSI;
  if (!(alpha1 == 0.0)) {
    int32_T i;
    int32_T jA;
    jA = ia0;
    d_st.site = &de_emlrtRSI;
    if (n > 2147483646) {
      e_st.site = &fb_emlrtRSI;
      check_forloop_overflow_error(&e_st);
    }
    i = (uint8_T)n;
    for (j = 0; j < i; j++) {
      real_T temp;
      temp = A[(iy0 + j) - 1];
      if (temp != 0.0) {
        int32_T b;
        int32_T scalarLB;
        int32_T vectorUB;
        temp *= alpha1;
        b = (m + jA) - 1;
        d_st.site = &ee_emlrtRSI;
        if ((jA <= b) && (b > 2147483646)) {
          e_st.site = &fb_emlrtRSI;
          check_forloop_overflow_error(&e_st);
        }
        scalarLB = ((b - jA) + 1) / 2 * 2 + jA;
        vectorUB = scalarLB - 2;
        for (ijA = jA; ijA <= vectorUB; ijA += 2) {
          __m128d r;
          __m128d r1;
          r = _mm_loadu_pd(&x[ijA - jA]);
          r = _mm_mul_pd(r, _mm_set1_pd(temp));
          r1 = _mm_loadu_pd(&A[ijA - 1]);
          r = _mm_add_pd(r1, r);
          _mm_storeu_pd(&A[ijA - 1], r);
        }
        for (ijA = scalarLB; ijA <= b; ijA++) {
          A[ijA - 1] += x[ijA - jA] * temp;
        }
      }
      jA += 3;
    }
  }
}
