#include "xdlahqr.h"
#include "codegenTest_float_mex_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xzlarfg.h"
#include "mwmathutil.h"
#include <emmintrin.h>

static emlrtRSInfo oe_emlrtRSI = {337, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo pe_emlrtRSI = {301, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo qe_emlrtRSI = {273, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo re_emlrtRSI = {243, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo se_emlrtRSI = {240, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo te_emlrtRSI = {226, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo ue_emlrtRSI = {172, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo eg_emlrtRSI = {292, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo fg_emlrtRSI = {264, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo gg_emlrtRSI = {33, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

static emlrtRSInfo hg_emlrtRSI = {16, "xdlahqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdlahqr.m"};

int32_T xdlahqr(const emlrtStack *sp, int32_T ilo, int32_T ihi, real_T h[9],
                real_T wr[3], real_T wi[3])
{
  emlrtStack b_st;
  emlrtStack st;
  real_T v[3];
  real_T h11;
  real_T h12;
  real_T h21;
  real_T h22;
  real_T rt1r;
  real_T rt2r;
  real_T sum;
  int32_T b_k;
  int32_T i;
  int32_T info;
  int32_T k;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  info = 0;
  st.site = &hg_emlrtRSI;
  if (ilo - 1 > 2147483646) {
    b_st.site = &fb_emlrtRSI;
    check_forloop_overflow_error(&b_st);
  }
  k = (uint8_T)(ilo - 1);
  for (i = 0; i < k; i++) {
    wr[i] = h[i + 3 * i];
    wi[i] = 0.0;
  }
  k = ihi + 1;
  for (i = k; i < 4; i++) {
    wr[i - 1] = h[(i + 3 * (i - 1)) - 1];
    wi[i - 1] = 0.0;
  }
  if (ilo == ihi) {
    wr[ilo - 1] = h[(ilo + 3 * (ilo - 1)) - 1];
    wi[ilo - 1] = 0.0;
  } else {
    real_T smlnum;
    int32_T b_i;
    int32_T kdefl;
    boolean_T exitg1;
    st.site = &gg_emlrtRSI;
    if ((ilo <= ihi - 3) && (ihi - 3 > 2147483646)) {
      b_st.site = &fb_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }
    if (ilo <= ihi - 2) {
      h[ihi - 1] = 0.0;
    }
    smlnum = 2.2250738585072014E-308 *
             ((real_T)((ihi - ilo) + 1) / 2.2204460492503131E-16);
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
        real_T s;
        int32_T ix0;
        boolean_T exitg3;
        k = b_i;
        exitg3 = false;
        while ((!exitg3) && (k + 1 > l)) {
          sum_tmp_tmp = k + 3 * (k - 1);
          h22 = muDoubleScalarAbs(h[sum_tmp_tmp]);
          if (h22 <= smlnum) {
            exitg3 = true;
          } else {
            ix0 = k + 3 * k;
            h12 = muDoubleScalarAbs(h[ix0]);
            h11 = muDoubleScalarAbs(h[sum_tmp_tmp - 1]) + h12;
            if (h11 == 0.0) {
              if (k - 1 >= ilo) {
                h11 = muDoubleScalarAbs(h[k - 1]);
              }
              if (k + 2 <= ihi) {
                h11 += muDoubleScalarAbs(h[3 * k + 2]);
              }
            }
            if (h22 <= 2.2204460492503131E-16 * h11) {
              h21 = muDoubleScalarAbs(h[ix0 - 1]);
              h11 = muDoubleScalarAbs(h[sum_tmp_tmp - 1] - h[ix0]);
              sum = muDoubleScalarMax(h12, h11);
              h11 = muDoubleScalarMin(h12, h11);
              s = sum + h11;
              if (muDoubleScalarMin(h22, h21) *
                      (muDoubleScalarMax(h22, h21) / s) <=
                  muDoubleScalarMax(smlnum, 2.2204460492503131E-16 *
                                                (h11 * (sum / s)))) {
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
          h[k + 3 * (k - 1)] = 0.0;
        }
        if (k + 1 >= b_i) {
          converged = true;
          exitg2 = true;
        } else {
          __m128d r;
          int32_T m;
          kdefl++;
          if (kdefl - kdefl / 20 * 20 == 0) {
            s = muDoubleScalarAbs(h[b_i + 3 * (b_i - 1)]) +
                muDoubleScalarAbs(h[b_i - 1]);
            h11 = 0.75 * s + h[b_i + 3 * b_i];
            h12 = -0.4375 * s;
            h21 = s;
            h22 = h11;
          } else if (kdefl - kdefl / 10 * 10 == 0) {
            s = muDoubleScalarAbs(h[1]) + muDoubleScalarAbs(h[5]);
            h11 = 0.75 * s + h[0];
            h12 = -0.4375 * s;
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
          s = ((muDoubleScalarAbs(h11) + muDoubleScalarAbs(h12)) +
               muDoubleScalarAbs(h21)) +
              muDoubleScalarAbs(h22);
          if (s == 0.0) {
            rt1r = 0.0;
            h11 = 0.0;
            rt2r = 0.0;
            h12 = 0.0;
          } else {
            h11 /= s;
            h21 /= s;
            h12 /= s;
            h22 /= s;
            sum = (h11 + h22) / 2.0;
            h11 = (h11 - sum) * (h22 - sum) - h12 * h21;
            st.site = &ue_emlrtRSI;
            h12 = muDoubleScalarSqrt(muDoubleScalarAbs(h11));
            if (h11 >= 0.0) {
              rt1r = sum * s;
              rt2r = rt1r;
              h11 = h12 * s;
              h12 = -h11;
            } else {
              rt1r = sum + h12;
              rt2r = sum - h12;
              if (muDoubleScalarAbs(rt1r - h22) <=
                  muDoubleScalarAbs(rt2r - h22)) {
                rt1r *= s;
                rt2r = rt1r;
              } else {
                rt2r *= s;
                rt1r = rt2r;
              }
              h11 = 0.0;
              h12 = 0.0;
            }
          }
          m = b_i - 1;
          if (b_i - 1 >= 1) {
            s = (muDoubleScalarAbs(h[0] - rt2r) + muDoubleScalarAbs(h12)) +
                muDoubleScalarAbs(h[1]);
            h21 = h[1] / s;
            v[0] = (h21 * h[3] + (h[0] - rt1r) * ((h[0] - rt2r) / s)) -
                   h11 * (h12 / s);
            v[1] = h21 * (((h[0] + h[4]) - rt1r) - rt2r);
            v[2] = h21 * h[5];
            s = (muDoubleScalarAbs(v[0]) + muDoubleScalarAbs(v[1])) +
                muDoubleScalarAbs(v[2]);
            r = _mm_loadu_pd(&v[0]);
            _mm_storeu_pd(&v[0], _mm_div_pd(r, _mm_set1_pd(s)));
            v[2] /= s;
          }
          st.site = &te_emlrtRSI;
          if ((b_i - 1 <= b_i) && (b_i > 2147483646)) {
            b_st.site = &fb_emlrtRSI;
            check_forloop_overflow_error(&b_st);
          }
          for (b_k = m; b_k <= b_i; b_k++) {
            sum_tmp_tmp = (b_i - b_k) + 2;
            k = muIntScalarMin_sint32(3, sum_tmp_tmp);
            if (b_k > b_i - 1) {
              ix0 = ((b_k - 2) * 3 + b_k) - 1;
              st.site = &se_emlrtRSI;
              sum_tmp_tmp = (uint8_T)k;
              for (i = 0; i < sum_tmp_tmp; i++) {
                v[i] = h[ix0 + i];
              }
            }
            h11 = v[0];
            st.site = &re_emlrtRSI;
            h22 = b_xzlarfg(k, &h11, v);
            if (b_k > b_i - 1) {
              h[b_k - 1] = h11;
              h[b_k] = 0.0;
              if (b_k < b_i) {
              }
            }
            rt2r = v[1];
            rt1r = h22 * v[1];
            if (k == 3) {
              int32_T b;
              int32_T scalarLB;
              h12 = v[2];
              h21 = h22 * v[2];
              st.site = &fg_emlrtRSI;
              if ((b_k <= b_i + 1) && (b_i + 1 > 2147483646)) {
                b_st.site = &fb_emlrtRSI;
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
              st.site = &qe_emlrtRSI;
              if (b > 2147483646) {
                b_st.site = &fb_emlrtRSI;
                check_forloop_overflow_error(&b_st);
              }
              scalarLB = ((b / 2) << 1) + 1;
              k = scalarLB - 2;
              for (i = 1; i <= k; i += 2) {
                __m128d r1;
                __m128d r2;
                sum_tmp_tmp = (i + 3 * b_k) - 1;
                r = _mm_loadu_pd(&h[sum_tmp_tmp]);
                ix0 = (i + 3 * (b_k - 1)) - 1;
                r1 = _mm_loadu_pd(&h[ix0]);
                r2 = _mm_loadu_pd(&h[i + 5]);
                r1 =
                    _mm_add_pd(_mm_add_pd(r1, _mm_mul_pd(_mm_set1_pd(rt2r), r)),
                               _mm_mul_pd(_mm_set1_pd(h12), r2));
                r = _mm_loadu_pd(&h[ix0]);
                _mm_storeu_pd(&h[ix0],
                              _mm_sub_pd(r, _mm_mul_pd(r1, _mm_set1_pd(h22))));
                r = _mm_loadu_pd(&h[sum_tmp_tmp]);
                _mm_storeu_pd(&h[sum_tmp_tmp],
                              _mm_sub_pd(r, _mm_mul_pd(r1, _mm_set1_pd(rt1r))));
                r = _mm_loadu_pd(&h[i + 5]);
                _mm_storeu_pd(&h[i + 5],
                              _mm_sub_pd(r, _mm_mul_pd(r1, _mm_set1_pd(h21))));
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
              st.site = &eg_emlrtRSI;
              if ((b_k <= b_i + 1) && (b_i + 1 > 2147483646)) {
                b_st.site = &fb_emlrtRSI;
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
              st.site = &pe_emlrtRSI;
              if ((b_i >= 0) && (b_i + 1 > 2147483646)) {
                b_st.site = &fb_emlrtRSI;
                check_forloop_overflow_error(&b_st);
              }
              b = (((b_i + 1) / 2) << 1) + 1;
              k = b - 2;
              for (i = 1; i <= k; i += 2) {
                __m128d r1;
                __m128d r2;
                sum_tmp_tmp = (i + 3 * b_k) - 1;
                r = _mm_loadu_pd(&h[sum_tmp_tmp]);
                ix0 = (i + 3 * (b_k - 1)) - 1;
                r1 = _mm_loadu_pd(&h[ix0]);
                r2 = _mm_add_pd(r1, _mm_mul_pd(_mm_set1_pd(rt2r), r));
                _mm_storeu_pd(&h[ix0],
                              _mm_sub_pd(r1, _mm_mul_pd(r2, _mm_set1_pd(h22))));
                _mm_storeu_pd(&h[sum_tmp_tmp],
                              _mm_sub_pd(r, _mm_mul_pd(r2, _mm_set1_pd(rt1r))));
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
          wi[b_i] = 0.0;
        } else if (l == b_i) {
          k = b_i + 3 * b_i;
          h11 = h[k - 1];
          sum_tmp_tmp = b_i + 3 * (b_i - 1);
          h12 = h[sum_tmp_tmp];
          h21 = h[k];
          st.site = &oe_emlrtRSI;
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
      h[2] = 0.0;
    }
  }
  return info;
}
