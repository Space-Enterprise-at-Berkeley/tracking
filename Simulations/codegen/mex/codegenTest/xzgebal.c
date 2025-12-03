/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzgebal.c
 *
 * Code generation for function 'xzgebal'
 *
 */

/* Include files */
#include "xzgebal.h"
#include "codegenTest_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xswap.h"
#include "mwmathutil.h"
#include <xmmintrin.h>

/* Variable Definitions */
static emlrtRSInfo vf_emlrtRSI = {
    39,        /* lineNo */
    "xzgebal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgebal.m" /* pathName */
};

static emlrtRSInfo wf_emlrtRSI = {
    55,        /* lineNo */
    "xzgebal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgebal.m" /* pathName */
};

static emlrtRSInfo xf_emlrtRSI = {
    74,        /* lineNo */
    "xzgebal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgebal.m" /* pathName */
};

static emlrtRSInfo yf_emlrtRSI = {
    76,        /* lineNo */
    "xzgebal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgebal.m" /* pathName */
};

static emlrtRSInfo ag_emlrtRSI = {
    92,        /* lineNo */
    "xzgebal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgebal.m" /* pathName */
};

static emlrtRSInfo bg_emlrtRSI = {
    95,        /* lineNo */
    "xzgebal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgebal.m" /* pathName */
};

static emlrtRSInfo cg_emlrtRSI = {
    119,       /* lineNo */
    "xzgebal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgebal.m" /* pathName */
};

static emlrtRSInfo dg_emlrtRSI = {
    120,       /* lineNo */
    "xzgebal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgebal.m" /* pathName */
};

static emlrtRSInfo eg_emlrtRSI = {
    170,       /* lineNo */
    "xzgebal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgebal.m" /* pathName */
};

/* Function Definitions */
int32_T xzgebal(const emlrtStack *sp, real32_T A[9], int32_T *ihi,
                real32_T scale[3])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  int32_T exitg5;
  int32_T ica;
  int32_T ilo;
  int32_T ix;
  int32_T iy;
  int32_T k;
  int32_T l;
  int32_T temp_tmp;
  int32_T vectorUB;
  real32_T temp;
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
  scale[0] = 1.0F;
  scale[1] = 1.0F;
  scale[2] = 1.0F;
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
          st.site = &vf_emlrtRSI;
          iy = 0;
          exitg6 = false;
          while ((!exitg6) && (iy <= l - 1)) {
            if ((iy + 1 == ica) || (!(A[(ica + 3 * iy) - 1] != 0.0F))) {
              iy++;
            } else {
              skipThisRow = true;
              exitg6 = true;
            }
          }
          if (skipThisRow) {
            ica--;
          } else {
            scale[l - 1] = (real32_T)ica;
            if (ica != l) {
              st.site = &wf_emlrtRSI;
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
        st.site = &xf_emlrtRSI;
        iy = ilo;
        exitg6 = false;
        while ((!exitg6) && (iy <= l)) {
          boolean_T exitg7;
          skipThisRow = false;
          st.site = &yf_emlrtRSI;
          ica = ilo;
          exitg7 = false;
          while ((!exitg7) && (ica <= l)) {
            if ((ica == iy) || (!(A[(ica + 3 * (iy - 1)) - 1] != 0.0F))) {
              ica++;
            } else {
              skipThisRow = true;
              exitg7 = true;
            }
          }
          if (skipThisRow) {
            iy++;
          } else {
            scale[ilo - 1] = (real32_T)iy;
            if (iy != ilo) {
              ica = (ilo - 1) * 3;
              st.site = &ag_emlrtRSI;
              xswap(&st, l, A, (iy - 1) * 3 + 1, ica + 1);
              ix = (ica + iy) - 1;
              iy = (ica + ilo) - 1;
              st.site = &bg_emlrtRSI;
              b_st.site = &fg_emlrtRSI;
              c_st.site = &gg_emlrtRSI;
              if (4 - ilo > 2147483646) {
                d_st.site = &kb_emlrtRSI;
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
      st.site = &cg_emlrtRSI;
      ix = ilo - 1;
      do {
        exitg2 = 0;
        if (ix + 1 <= l) {
          real32_T b_s;
          real32_T c;
          real32_T ca;
          real32_T r;
          real32_T s;
          ica = (l - ilo) + 1;
          st.site = &dg_emlrtRSI;
          c = xnrm2(&st, ica, A, ix * 3 + ilo);
          temp_tmp = (ilo - 1) * 3 + ix;
          r = 0.0F;
          if (ica >= 1) {
            if (ica == 1) {
              r = muSingleScalarAbs(A[temp_tmp]);
            } else {
              temp = 1.29246971E-26F;
              ica = (temp_tmp + (ica - 1) * 3) + 1;
              for (k = temp_tmp + 1; k <= ica; k += 3) {
                s = muSingleScalarAbs(A[k - 1]);
                if (s > temp) {
                  b_s = temp / s;
                  r = r * b_s * b_s + 1.0F;
                  temp = s;
                } else {
                  b_s = s / temp;
                  r += b_s * b_s;
                }
              }
              r = temp * muSingleScalarSqrt(r);
            }
          }
          iy = ix * 3;
          ica = 1;
          if (l > 1) {
            temp = muSingleScalarAbs(A[iy]);
            for (k = 2; k <= l; k++) {
              s = muSingleScalarAbs(A[(iy + k) - 1]);
              if (s > temp) {
                ica = k;
                temp = s;
              }
            }
          }
          ca = muSingleScalarAbs(A[(ica + 3 * ix) - 1]);
          iy = 4 - ilo;
          if (4 - ilo < 1) {
            ica = 0;
          } else {
            ica = 1;
            if (4 - ilo > 1) {
              temp = muSingleScalarAbs(A[temp_tmp]);
              for (k = 2; k <= iy; k++) {
                s = muSingleScalarAbs(A[temp_tmp + (k - 1) * 3]);
                if (s > temp) {
                  ica = k;
                  temp = s;
                }
              }
            }
          }
          temp = muSingleScalarAbs(A[ix + 3 * ((ica + ilo) - 2)]);
          if ((c == 0.0F) || (r == 0.0F)) {
            ix++;
          } else {
            int32_T exitg1;
            real32_T f;
            s = r / 2.0F;
            f = 1.0F;
            b_s = c + r;
            do {
              exitg1 = 0;
              if ((c < s) &&
                  (muSingleScalarMax(f, muSingleScalarMax(c, ca)) <
                   5.0706024E+30F) &&
                  (muSingleScalarMin(r, muSingleScalarMin(s, temp)) >
                   1.97215226E-31F)) {
                if (muSingleScalarIsNaN(((((c + f) + ca) + r) + s) + temp)) {
                  exitg1 = 1;
                } else {
                  f *= 2.0F;
                  c *= 2.0F;
                  ca *= 2.0F;
                  r /= 2.0F;
                  s /= 2.0F;
                  temp /= 2.0F;
                }
              } else {
                s = c / 2.0F;
                while ((s >= r) &&
                       (muSingleScalarMax(r, temp) < 5.0706024E+30F) &&
                       (muSingleScalarMin(muSingleScalarMin(f, c),
                                          muSingleScalarMin(s, ca)) >
                        1.97215226E-31F)) {
                  f /= 2.0F;
                  c /= 2.0F;
                  s /= 2.0F;
                  ca /= 2.0F;
                  r *= 2.0F;
                  temp *= 2.0F;
                }
                if ((!(c + r >= 0.95F * b_s)) &&
                    ((!(f < 1.0F)) || (!(scale[ix] < 1.0F)) ||
                     (!(f * scale[ix] <= 9.86076132E-32F))) &&
                    ((!(f > 1.0F)) || (!(scale[ix] > 1.0F)) ||
                     (!(scale[ix] >= 1.01412048E+31F / f)))) {
                  temp = 1.0F / f;
                  scale[ix] *= f;
                  iy = temp_tmp + 1;
                  ica = (temp_tmp + 3 * (3 - ilo)) + 1;
                  for (k = iy; k <= ica; k += 3) {
                    A[k - 1] *= temp;
                  }
                  st.site = &eg_emlrtRSI;
                  ica = ix * 3 + 1;
                  b_st.site = &ub_emlrtRSI;
                  iy = (ica + l) - 1;
                  c_st.site = &vb_emlrtRSI;
                  if ((ica <= iy) && (iy > 2147483646)) {
                    d_st.site = &kb_emlrtRSI;
                    check_forloop_overflow_error(&d_st);
                  }
                  temp_tmp = ((iy - ica) + 1) / 4 * 4 + ica;
                  vectorUB = temp_tmp - 4;
                  for (k = ica; k <= vectorUB; k += 4) {
                    __m128 b_r;
                    b_r = _mm_loadu_ps(&A[k - 1]);
                    b_r = _mm_mul_ps(_mm_set1_ps(f), b_r);
                    _mm_storeu_ps(&A[k - 1], b_r);
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

/* End of code generation (xzgebal.c) */
