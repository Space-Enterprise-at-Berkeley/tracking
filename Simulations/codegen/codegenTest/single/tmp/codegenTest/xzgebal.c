#include "xzgebal.h"
#include "codegenTest_float_mex_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xswap.h"
#include "mwmathutil.h"
#include <emmintrin.h>

static emlrtRSInfo qf_emlrtRSI = {39, "xzgebal",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgebal.m"};

static emlrtRSInfo rf_emlrtRSI = {55, "xzgebal",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgebal.m"};

static emlrtRSInfo sf_emlrtRSI = {74, "xzgebal",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgebal.m"};

static emlrtRSInfo tf_emlrtRSI = {76, "xzgebal",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgebal.m"};

static emlrtRSInfo uf_emlrtRSI = {92, "xzgebal",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgebal.m"};

static emlrtRSInfo vf_emlrtRSI = {95, "xzgebal",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgebal.m"};

static emlrtRSInfo wf_emlrtRSI = {119, "xzgebal",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgebal.m"};

static emlrtRSInfo xf_emlrtRSI = {120, "xzgebal",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgebal.m"};

static emlrtRSInfo yf_emlrtRSI = {170, "xzgebal",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgebal.m"};

int32_T xzgebal(const emlrtStack *sp, real_T A[9], int32_T *ihi,
                real_T scale[3])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  real_T temp;
  int32_T exitg5;
  int32_T ica;
  int32_T ilo;
  int32_T ix;
  int32_T iy;
  int32_T k;
  int32_T l;
  int32_T temp_tmp;
  int32_T vectorUB;
  boolean_T notdone;
  boolean_T skipThisRow;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  scale[0] = 1.0;
  scale[1] = 1.0;
  scale[2] = 1.0;
  ilo = 1;
  l = 3;
  notdone = true;
  do {
    exitg5 = 0;
    if (notdone) {
      int32_T exitg4;
      notdone = false;
      ica = l;
      do {
        exitg4 = 0;
        if (ica > 0) {
          boolean_T exitg6;
          skipThisRow = false;
          st.site = &qf_emlrtRSI;
          iy = 0;
          exitg6 = false;
          while ((!exitg6) && (iy <= l - 1)) {
            if ((iy + 1 == ica) || (!(A[(ica + 3 * iy) - 1] != 0.0))) {
              iy++;
            } else {
              skipThisRow = true;
              exitg6 = true;
            }
          }
          if (skipThisRow) {
            ica--;
          } else {
            scale[l - 1] = ica;
            if (ica != l) {
              st.site = &rf_emlrtRSI;
              xswap(&st, l, A, (ica - 1) * 3 + 1, (l - 1) * 3 + 1);
              temp = A[ica - 1];
              A[ica - 1] = A[l - 1];
              A[l - 1] = temp;
              temp = A[ica + 2];
              A[ica + 2] = A[l + 2];
              A[l + 2] = temp;
              temp = A[ica + 5];
              A[ica + 5] = A[l + 5];
              A[l + 5] = temp;
            }
            exitg4 = 1;
          }
        } else {
          exitg4 = 2;
        }
      } while (exitg4 == 0);
      if (exitg4 == 1) {
        if (l == 1) {
          ilo = 1;
          *ihi = 1;
          exitg5 = 1;
        } else {
          l--;
          notdone = true;
        }
      }
    } else {
      notdone = true;
      while (notdone) {
        boolean_T exitg6;
        notdone = false;
        st.site = &sf_emlrtRSI;
        iy = ilo;
        exitg6 = false;
        while ((!exitg6) && (iy <= l)) {
          boolean_T exitg7;
          skipThisRow = false;
          st.site = &tf_emlrtRSI;
          ica = ilo;
          exitg7 = false;
          while ((!exitg7) && (ica <= l)) {
            if ((ica == iy) || (!(A[(ica + 3 * (iy - 1)) - 1] != 0.0))) {
              ica++;
            } else {
              skipThisRow = true;
              exitg7 = true;
            }
          }
          if (skipThisRow) {
            iy++;
          } else {
            scale[ilo - 1] = iy;
            if (iy != ilo) {
              ica = (ilo - 1) * 3;
              st.site = &uf_emlrtRSI;
              xswap(&st, l, A, (iy - 1) * 3 + 1, ica + 1);
              ix = (ica + iy) - 1;
              iy = (ica + ilo) - 1;
              st.site = &vf_emlrtRSI;
              b_st.site = &ag_emlrtRSI;
              c_st.site = &bg_emlrtRSI;
              if (4 - ilo > 2147483646) {
                d_st.site = &fb_emlrtRSI;
                check_forloop_overflow_error(&d_st);
              }
              ica = (uint8_T)(4 - ilo);
              for (k = 0; k < ica; k++) {
                temp_tmp = ix + k * 3;
                temp = A[temp_tmp];
                vectorUB = iy + k * 3;
                A[temp_tmp] = A[vectorUB];
                A[vectorUB] = temp;
              }
            }
            ilo++;
            notdone = true;
            exitg6 = true;
          }
        }
      }
      *ihi = l;
      skipThisRow = false;
      exitg5 = 2;
    }
  } while (exitg5 == 0);
  if (exitg5 != 1) {
    boolean_T exitg3;
    exitg3 = false;
    while ((!exitg3) && (!skipThisRow)) {
      int32_T exitg2;
      skipThisRow = true;
      st.site = &wf_emlrtRSI;
      ix = ilo - 1;
      do {
        exitg2 = 0;
        if (ix + 1 <= l) {
          real_T b_s;
          real_T c;
          real_T ca;
          real_T r;
          real_T s;
          ica = (l - ilo) + 1;
          st.site = &xf_emlrtRSI;
          c = xnrm2(&st, ica, A, ix * 3 + ilo);
          temp_tmp = (ilo - 1) * 3 + ix;
          r = 0.0;
          if (ica >= 1) {
            if (ica == 1) {
              r = muDoubleScalarAbs(A[temp_tmp]);
            } else {
              temp = 3.3121686421112381E-170;
              ica = (temp_tmp + (ica - 1) * 3) + 1;
              for (k = temp_tmp + 1; k <= ica; k += 3) {
                s = muDoubleScalarAbs(A[k - 1]);
                if (s > temp) {
                  b_s = temp / s;
                  r = r * b_s * b_s + 1.0;
                  temp = s;
                } else {
                  b_s = s / temp;
                  r += b_s * b_s;
                }
              }
              r = temp * muDoubleScalarSqrt(r);
            }
          }
          iy = ix * 3;
          ica = 1;
          if (l > 1) {
            temp = muDoubleScalarAbs(A[iy]);
            for (k = 2; k <= l; k++) {
              s = muDoubleScalarAbs(A[(iy + k) - 1]);
              if (s > temp) {
                ica = k;
                temp = s;
              }
            }
          }
          ca = muDoubleScalarAbs(A[(ica + 3 * ix) - 1]);
          iy = 4 - ilo;
          if (4 - ilo < 1) {
            ica = 0;
          } else {
            ica = 1;
            if (4 - ilo > 1) {
              temp = muDoubleScalarAbs(A[temp_tmp]);
              for (k = 2; k <= iy; k++) {
                s = muDoubleScalarAbs(A[temp_tmp + (k - 1) * 3]);
                if (s > temp) {
                  ica = k;
                  temp = s;
                }
              }
            }
          }
          temp = muDoubleScalarAbs(A[ix + 3 * ((ica + ilo) - 2)]);
          if ((c == 0.0) || (r == 0.0)) {
            ix++;
          } else {
            real_T f;
            int32_T exitg1;
            s = r / 2.0;
            f = 1.0;
            b_s = c + r;
            do {
              exitg1 = 0;
              if ((c < s) &&
                  (muDoubleScalarMax(f, muDoubleScalarMax(c, ca)) <
                   4.9896007738368E+291) &&
                  (muDoubleScalarMin(r, muDoubleScalarMin(s, temp)) >
                   2.0041683600089728E-292)) {
                if (muDoubleScalarIsNaN(((((c + f) + ca) + r) + s) + temp)) {
                  exitg1 = 1;
                } else {
                  f *= 2.0;
                  c *= 2.0;
                  ca *= 2.0;
                  r /= 2.0;
                  s /= 2.0;
                  temp /= 2.0;
                }
              } else {
                s = c / 2.0;
                while ((s >= r) &&
                       (muDoubleScalarMax(r, temp) < 4.9896007738368E+291) &&
                       (muDoubleScalarMin(muDoubleScalarMin(f, c),
                                          muDoubleScalarMin(s, ca)) >
                        2.0041683600089728E-292)) {
                  f /= 2.0;
                  c /= 2.0;
                  s /= 2.0;
                  ca /= 2.0;
                  r *= 2.0;
                  temp *= 2.0;
                }
                if ((!(c + r >= 0.95 * b_s)) &&
                    ((!(f < 1.0)) || (!(scale[ix] < 1.0)) ||
                     (!(f * scale[ix] <= 1.0020841800044864E-292))) &&
                    ((!(f > 1.0)) || (!(scale[ix] > 1.0)) ||
                     (!(scale[ix] >= 9.9792015476736E+291 / f)))) {
                  temp = 1.0 / f;
                  scale[ix] *= f;
                  iy = temp_tmp + 1;
                  ica = (temp_tmp + 3 * (3 - ilo)) + 1;
                  for (k = iy; k <= ica; k += 3) {
                    A[k - 1] *= temp;
                  }
                  st.site = &yf_emlrtRSI;
                  ica = ix * 3 + 1;
                  b_st.site = &pb_emlrtRSI;
                  iy = (ica + l) - 1;
                  c_st.site = &qb_emlrtRSI;
                  if ((ica <= iy) && (iy > 2147483646)) {
                    d_st.site = &fb_emlrtRSI;
                    check_forloop_overflow_error(&d_st);
                  }
                  temp_tmp = ((iy - ica) + 1) / 2 * 2 + ica;
                  vectorUB = temp_tmp - 2;
                  for (k = ica; k <= vectorUB; k += 2) {
                    __m128d b_r;
                    b_r = _mm_loadu_pd(&A[k - 1]);
                    b_r = _mm_mul_pd(_mm_set1_pd(f), b_r);
                    _mm_storeu_pd(&A[k - 1], b_r);
                  }
                  for (k = temp_tmp; k <= iy; k++) {
                    A[k - 1] *= f;
                  }
                  skipThisRow = false;
                }
                exitg1 = 2;
              }
            } while (exitg1 == 0);
            if (exitg1 == 1) {
              exitg2 = 2;
            } else {
              ix++;
            }
          }
        } else {
          exitg2 = 1;
        }
      } while (exitg2 == 0);
      if (exitg2 != 1) {
        exitg3 = true;
      }
    }
  }
  return ilo;
}
