/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdlahqr.c
 *
 * Code generation for function 'xdlahqr'
 *
 */

/* Include files */
#include "xdlahqr.h"
#include "codegenTest_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xzlarfg.h"
#include "mwmathutil.h"
#include <xmmintrin.h>

/* Variable Definitions */
static emlrtRSInfo te_emlrtRSI = {
    337,       /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo ue_emlrtRSI = {
    301,       /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo ve_emlrtRSI = {
    273,       /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo we_emlrtRSI = {
    243,       /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo xe_emlrtRSI = {
    240,       /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo ye_emlrtRSI = {
    226,       /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo af_emlrtRSI = {
    172,       /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo jg_emlrtRSI = {
    292,       /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo kg_emlrtRSI = {
    264,       /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo lg_emlrtRSI = {
    33,        /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

static emlrtRSInfo mg_emlrtRSI = {
    16,        /* lineNo */
    "xdlahqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdlahqr.m" /* pathName */
};

/* Function Definitions */
int32_T xdlahqr(const emlrtStack *sp, int32_T ilo, int32_T ihi, real32_T h[9],
                real32_T wr[3], real32_T wi[3])
{
  emlrtStack b_st;
  emlrtStack st;
  int32_T b_k;
  int32_T i;
  int32_T info;
  int32_T k;
  real32_T h11;
  real32_T h12;
  real32_T h21;
  real32_T h22;
  real32_T rt1r;
  real32_T rt2r;
  real32_T sum;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  info = 0;
  st.site = &mg_emlrtRSI;
  if (ilo - 1 > 2147483646) {
    b_st.site = &kb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  k = (uint8_T)(ilo - 1);
  for (i = 0; i < k; i++) {
    wr[i] = h[i + 3 * i];
    wi[i] = 0.0F;
  }
  k = ihi + 1;
  for (i = k; i < 4; i++) {
    wr[i - 1] = h[(i + 3 * (i - 1)) - 1];
    wi[i - 1] = 0.0F;
  }
  if (ilo == ihi) {
    wr[ilo - 1] = h[(ilo + 3 * (ilo - 1)) - 1];
    wi[ilo - 1] = 0.0F;
  } else {
    int32_T b_i;
    int32_T kdefl;
    real32_T smlnum;
    boolean_T exitg1;
    st.site = &lg_emlrtRSI;
    if ((ilo <= ihi - 3) && (ihi - 3 > 2147483646)) {
      b_st.site = &kb_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }
    if (ilo <= ihi - 2) {
      h[ihi - 1] = 0.0F;
    }
    smlnum = 1.17549435E-38F * ((real32_T)((ihi - ilo) + 1) / 1.1920929E-7F);
    kdefl = 0;
    b_i = ihi - 1;
    exitg1 = false;
    while ((!exitg1) && (b_i + 1 >= ilo)) {
      int32_T its;
      int32_T l;
      int32_T sum_tmp_tmp;
      boolean_T converged;
      boolean_T exitg2;
      l = ilo;
      converged = false;
      its = 0;
      exitg2 = false;
      while ((!exitg2) && (its < 301)) {
        int32_T ix0;
        real32_T s;
        boolean_T exitg3;
        k = b_i;
        exitg3 = false;
        while ((!exitg3) && (k + 1 > l)) {
          sum_tmp_tmp = k + 3 * (k - 1);
          h22 = muSingleScalarAbs(h[sum_tmp_tmp]);
          if (h22 <= smlnum) {
            exitg3 = true;
          } else {
            ix0 = k + 3 * k;
            h12 = muSingleScalarAbs(h[ix0]);
            h11 = muSingleScalarAbs(h[sum_tmp_tmp - 1]) + h12;
            if (h11 == 0.0F) {
              if (k - 1 >= ilo) {
                h11 = muSingleScalarAbs(h[k - 1]);
              }
              if (k + 2 <= ihi) {
                h11 += muSingleScalarAbs(h[3 * k + 2]);
              }
            }
            if (h22 <= 1.1920929E-7F * h11) {
              h21 = muSingleScalarAbs(h[ix0 - 1]);
              h11 = muSingleScalarAbs(h[sum_tmp_tmp - 1] - h[ix0]);
              sum = muSingleScalarMax(h12, h11);
              h11 = muSingleScalarMin(h12, h11);
              s = sum + h11;
              if (muSingleScalarMin(h22, h21) *
                      (muSingleScalarMax(h22, h21) / s) <=
                  muSingleScalarMax(smlnum,
                                    1.1920929E-7F * (h11 * (sum / s)))) {
                exitg3 = true;
              } else {
                k--;
              }
            } else {
              k--;
            }
          }
        }
        l = k + 1;
        if (k + 1 > ilo) {
          h[k + 3 * (k - 1)] = 0.0F;
        }
        if (k + 1 >= b_i) {
          converged = true;
          exitg2 = true;
        } else {
          int32_T m;
          real32_T v[3];
          kdefl++;
          if (kdefl - kdefl / 20 * 20 == 0) {
            s = muSingleScalarAbs(h[b_i + 3 * (b_i - 1)]) +
                muSingleScalarAbs(h[b_i - 1]);
            h11 = 0.75F * s + h[b_i + 3 * b_i];
            h12 = -0.4375F * s;
            h21 = s;
            h22 = h11;
          } else if (kdefl - kdefl / 10 * 10 == 0) {
            s = muSingleScalarAbs(h[1]) + muSingleScalarAbs(h[5]);
            h11 = 0.75F * s + h[0];
            h12 = -0.4375F * s;
            h21 = s;
            h22 = h11;
          } else {
            k = b_i + 3 * (b_i - 1);
            h11 = h[k - 1];
            h21 = h[k];
            sum_tmp_tmp = b_i + 3 * b_i;
            h12 = h[sum_tmp_tmp - 1];
            h22 = h[sum_tmp_tmp];
          }
          s = ((muSingleScalarAbs(h11) + muSingleScalarAbs(h12)) +
               muSingleScalarAbs(h21)) +
              muSingleScalarAbs(h22);
          if (s == 0.0F) {
            rt1r = 0.0F;
            h11 = 0.0F;
            rt2r = 0.0F;
            h12 = 0.0F;
          } else {
            h11 /= s;
            h21 /= s;
            h12 /= s;
            h22 /= s;
            sum = (h11 + h22) / 2.0F;
            h11 = (h11 - sum) * (h22 - sum) - h12 * h21;
            st.site = &af_emlrtRSI;
            h12 = muSingleScalarSqrt(muSingleScalarAbs(h11));
            if (h11 >= 0.0F) {
              rt1r = sum * s;
              rt2r = rt1r;
              h11 = h12 * s;
              h12 = -h11;
            } else {
              rt1r = sum + h12;
              rt2r = sum - h12;
              if (muSingleScalarAbs(rt1r - h22) <=
                  muSingleScalarAbs(rt2r - h22)) {
                rt1r *= s;
                rt2r = rt1r;
              } else {
                rt2r *= s;
                rt1r = rt2r;
              }
              h11 = 0.0F;
              h12 = 0.0F;
            }
          }
          m = b_i - 1;
          if (b_i - 1 >= 1) {
            s = (muSingleScalarAbs(h[0] - rt2r) + muSingleScalarAbs(h12)) +
                muSingleScalarAbs(h[1]);
            h21 = h[1] / s;
            v[0] = (h21 * h[3] + (h[0] - rt1r) * ((h[0] - rt2r) / s)) -
                   h11 * (h12 / s);
            v[1] = h21 * (((h[0] + h[4]) - rt1r) - rt2r);
            v[2] = h21 * h[5];
            h11 = (muSingleScalarAbs(v[0]) + muSingleScalarAbs(v[1])) +
                  muSingleScalarAbs(v[2]);
            v[0] /= h11;
            v[1] /= h11;
            v[2] /= h11;
          }
          st.site = &ye_emlrtRSI;
          if ((b_i - 1 <= b_i) && (b_i > 2147483646)) {
            b_st.site = &kb_emlrtRSI;
            check_forloop_overflow_error(&b_st);
          }
          for (b_k = m; b_k <= b_i; b_k++) {
            sum_tmp_tmp = (b_i - b_k) + 2;
            k = muIntScalarMin_sint32(3, sum_tmp_tmp);
            if (b_k > b_i - 1) {
              ix0 = ((b_k - 2) * 3 + b_k) - 1;
              st.site = &xe_emlrtRSI;
              sum_tmp_tmp = (uint8_T)k;
              for (i = 0; i < sum_tmp_tmp; i++) {
                v[i] = h[ix0 + i];
              }
            }
            h11 = v[0];
            st.site = &we_emlrtRSI;
            h22 = b_xzlarfg(k, &h11, v);
            if (b_k > b_i - 1) {
              h[b_k - 1] = h11;
              h[b_k] = 0.0F;
              if (b_k < b_i) {
                /* Check node always fails. would cause program termination and
                 * was eliminated */
              }
            }
            rt2r = v[1];
            rt1r = h22 * v[1];
            if (k == 3) {
              int32_T b;
              int32_T scalarLB;
              h12 = v[2];
              h21 = h22 * v[2];
              st.site = &kg_emlrtRSI;
              if ((b_k <= b_i + 1) && (b_i + 1 > 2147483646)) {
                b_st.site = &kb_emlrtRSI;
                check_forloop_overflow_error(&b_st);
              }
              for (i = b_k; i <= b_i + 1; i++) {
                sum_tmp_tmp = 3 * (i - 1);
                k = b_k + sum_tmp_tmp;
                h11 = h[k - 1];
                sum = (h11 + rt2r * h[k]) + h12 * h[sum_tmp_tmp + 2];
                h[k - 1] = h11 - sum * h22;
                h[k] -= sum * rt1r;
                h[sum_tmp_tmp + 2] -= sum * h21;
              }
              sum_tmp_tmp = b_k + 3;
              k = b_i + 1;
              b = muIntScalarMin_sint32(sum_tmp_tmp, k);
              st.site = &ve_emlrtRSI;
              if (b > 2147483646) {
                b_st.site = &kb_emlrtRSI;
                check_forloop_overflow_error(&b_st);
              }
              scalarLB = ((b / 4) << 2) + 1;
              k = scalarLB - 4;
              for (i = 1; i <= k; i += 4) {
                __m128 r;
                __m128 r1;
                __m128 r2;
                sum_tmp_tmp = (i + 3 * b_k) - 1;
                r = _mm_loadu_ps(&h[sum_tmp_tmp]);
                ix0 = (i + 3 * (b_k - 1)) - 1;
                r1 = _mm_loadu_ps(&h[ix0]);
                r2 = _mm_loadu_ps(&h[i + 5]);
                r1 =
                    _mm_add_ps(_mm_add_ps(r1, _mm_mul_ps(_mm_set1_ps(rt2r), r)),
                               _mm_mul_ps(_mm_set1_ps(h12), r2));
                r = _mm_loadu_ps(&h[ix0]);
                _mm_storeu_ps(&h[ix0],
                              _mm_sub_ps(r, _mm_mul_ps(r1, _mm_set1_ps(h22))));
                r = _mm_loadu_ps(&h[sum_tmp_tmp]);
                _mm_storeu_ps(&h[sum_tmp_tmp],
                              _mm_sub_ps(r, _mm_mul_ps(r1, _mm_set1_ps(rt1r))));
                r = _mm_loadu_ps(&h[i + 5]);
                _mm_storeu_ps(&h[i + 5],
                              _mm_sub_ps(r, _mm_mul_ps(r1, _mm_set1_ps(h21))));
              }
              for (i = scalarLB; i <= b; i++) {
                k = (i + 3 * (b_k - 1)) - 1;
                h11 = h[k];
                sum_tmp_tmp = (i + 3 * b_k) - 1;
                sum = (h11 + rt2r * h[sum_tmp_tmp]) + h12 * h[i + 5];
                h[k] = h11 - sum * h22;
                h[sum_tmp_tmp] -= sum * rt1r;
                h[i + 5] -= sum * h21;
              }
            } else if (k == 2) {
              int32_T b;
              st.site = &jg_emlrtRSI;
              if ((b_k <= b_i + 1) && (b_i + 1 > 2147483646)) {
                b_st.site = &kb_emlrtRSI;
                check_forloop_overflow_error(&b_st);
              }
              for (i = b_k; i <= b_i + 1; i++) {
                sum_tmp_tmp = b_k + 3 * (i - 1);
                h11 = h[sum_tmp_tmp - 1];
                h12 = h[sum_tmp_tmp];
                sum = h11 + rt2r * h12;
                h11 -= sum * h22;
                h[sum_tmp_tmp - 1] = h11;
                h12 -= sum * rt1r;
                h[sum_tmp_tmp] = h12;
              }
              st.site = &ue_emlrtRSI;
              if ((b_i >= 0) && (b_i + 1 > 2147483646)) {
                b_st.site = &kb_emlrtRSI;
                check_forloop_overflow_error(&b_st);
              }
              b = (((b_i + 1) / 4) << 2) + 1;
              k = b - 4;
              for (i = 1; i <= k; i += 4) {
                __m128 r;
                __m128 r1;
                __m128 r2;
                sum_tmp_tmp = (i + 3 * b_k) - 1;
                r = _mm_loadu_ps(&h[sum_tmp_tmp]);
                ix0 = (i + 3 * (b_k - 1)) - 1;
                r1 = _mm_loadu_ps(&h[ix0]);
                r2 = _mm_add_ps(r1, _mm_mul_ps(_mm_set1_ps(rt2r), r));
                _mm_storeu_ps(&h[ix0],
                              _mm_sub_ps(r1, _mm_mul_ps(r2, _mm_set1_ps(h22))));
                _mm_storeu_ps(&h[sum_tmp_tmp],
                              _mm_sub_ps(r, _mm_mul_ps(r2, _mm_set1_ps(rt1r))));
              }
              for (i = b; i <= b_i + 1; i++) {
                k = (i + 3 * (b_k - 1)) - 1;
                h11 = h[k];
                sum_tmp_tmp = (i + 3 * b_k) - 1;
                h12 = h[sum_tmp_tmp];
                sum = h11 + rt2r * h12;
                h11 -= sum * h22;
                h[k] = h11;
                h12 -= sum * rt1r;
                h[sum_tmp_tmp] = h12;
              }
            }
          }
          its++;
        }
      }
      if (!converged) {
        info = b_i + 1;
        exitg1 = true;
      } else {
        if (l == b_i + 1) {
          wr[b_i] = h[b_i + 3 * b_i];
          wi[b_i] = 0.0F;
        } else if (l == b_i) {
          k = b_i + 3 * b_i;
          h11 = h[k - 1];
          sum_tmp_tmp = b_i + 3 * (b_i - 1);
          h12 = h[sum_tmp_tmp];
          h21 = h[k];
          st.site = &te_emlrtRSI;
          wr[b_i - 1] = xdlanv2(&h[sum_tmp_tmp - 1], &h11, &h12, &h21,
                                &wi[b_i - 1], &sum, &h22, &rt2r, &rt1r);
          wr[b_i] = sum;
          wi[b_i] = h22;
          h[k - 1] = h11;
          h[sum_tmp_tmp] = h12;
          h[k] = h21;
        }
        kdefl = 0;
        b_i = l - 2;
      }
    }
    if (info != 0) {
      h[2] = 0.0F;
    }
  }
  return info;
}

/* End of code generation (xdlahqr.c) */
