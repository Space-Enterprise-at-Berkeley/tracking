#include "qrsolve.h"
#include "codegenTest_float_mex_data.h"
#include "rt_nonfinite.h"
#include "warning.h"
#include "lapacke.h"
#include "mwmathutil.h"
#include <emmintrin.h>
#include <stddef.h>
#include <string.h>

static emlrtRSInfo gi_emlrtRSI = {
    61, "qrsolve",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\qrsolve.m"};

static emlrtRSInfo hi_emlrtRSI = {
    72, "qrsolve",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\qrsolve.m"};

static emlrtRSInfo ii_emlrtRSI = {
    85, "qrsolve",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\qrsolve.m"};

static emlrtRSInfo ji_emlrtRSI = {63, "xgeqp3",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeqp3.m"};

static emlrtRSInfo ki_emlrtRSI = {98, "ceval_xgeqp3",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeqp3.m"};

static emlrtRSInfo li_emlrtRSI = {138, "ceval_xgeqp3",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeqp3.m"};

static emlrtRSInfo mi_emlrtRSI = {141, "ceval_xgeqp3",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeqp3.m"};

static emlrtRSInfo ni_emlrtRSI = {143, "ceval_xgeqp3",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeqp3.m"};

static emlrtRSInfo oi_emlrtRSI = {148, "ceval_xgeqp3",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeqp3.m"};

static emlrtRSInfo pi_emlrtRSI = {151, "ceval_xgeqp3",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeqp3.m"};

static emlrtRSInfo qi_emlrtRSI = {154, "ceval_xgeqp3",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeqp3.m"};

static emlrtRSInfo ri_emlrtRSI = {158, "ceval_xgeqp3",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeqp3.m"};

static emlrtRSInfo si_emlrtRSI = {
    173, "rankFromQR",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\qrsolve.m"};

static emlrtRSInfo ti_emlrtRSI = {
    172, "rankFromQR",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\qrsolve.m"};

static emlrtRSInfo ui_emlrtRSI = {
    119, "LSQFromQR",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\qrsolve.m"};

static emlrtRSInfo vi_emlrtRSI = {
    128, "LSQFromQR",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\qrsolve.m"};

static emlrtRSInfo wi_emlrtRSI = {
    138, "LSQFromQR",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\qrsolve.m"};

static emlrtRSInfo xi_emlrtRSI = {40, "xunormqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xunormqr.m"};

static emlrtRSInfo yi_emlrtRSI = {106, "ceval_xunormqr",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xunormqr.m"};

static emlrtMCInfo c_emlrtMCI = {53, 19, "flt2str",
                                 "C:\\Program "
                                 "Files\\MATLAB\\R2025b\\toolbox\\shared\\coder"
                                 "\\coder\\lib\\+coder\\+internal\\flt2str.m"};

static emlrtRSInfo nj_emlrtRSI = {
    53, "flt2str",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\flt2str.m"};

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               char_T y[14]);

static const mxArray *b_sprintf(const emlrtStack *sp, const mxArray *m,
                                const mxArray *m1, emlrtMCInfo *location);

static void emlrt_marshallIn(const emlrtStack *sp,
                             const mxArray *a__output_of_sprintf_,
                             const char_T *identifier, char_T y[14]);

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, char_T ret[14]);

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, char_T y[14])
{
  g_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_sprintf(const emlrtStack *sp, const mxArray *m,
                                const mxArray *m1, emlrtMCInfo *location)
{
  const mxArray *pArrays[2];
  const mxArray *m2;
  pArrays[0] = m;
  pArrays[1] = m1;
  return emlrtCallMATLABR2012b((emlrtConstCTX)sp, 1, &m2, 2, &pArrays[0],
                               "sprintf", true, location);
}

static void emlrt_marshallIn(const emlrtStack *sp,
                             const mxArray *a__output_of_sprintf_,
                             const char_T *identifier, char_T y[14])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(a__output_of_sprintf_), &thisId, y);
  emlrtDestroyArray(&a__output_of_sprintf_);
}

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, char_T ret[14])
{
  static const int32_T dims[2] = {1, 14};
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "char", false, 2U,
                          (const void *)&dims[0]);
  emlrtImportCharArrayR2015b((emlrtConstCTX)sp, src, &ret[0], 14);
  emlrtDestroyArray(&src);
}

void qrsolve(const emlrtStack *sp, const real_T A_data[],
             const int32_T A_size[2], const real_T B_data[],
             const int32_T B_size[2], real_T Y_data[], int32_T Y_size[2])
{
  static const int32_T b_iv[2] = {1, 6};
  static const char_T b_fname[14] = {'L', 'A', 'P', 'A', 'C', 'K', 'E',
                                     '_', 'd', 'o', 'r', 'm', 'q', 'r'};
  static const char_T fname[14] = {'L', 'A', 'P', 'A', 'C', 'K', 'E',
                                   '_', 'd', 'g', 'e', 'q', 'p', '3'};
  static const char_T rfmt[6] = {'%', '1', '4', '.', '6', 'e'};
  ptrdiff_t jpvt_t_data[3];
  ptrdiff_t nrc_t;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  const mxArray *b_y;
  const mxArray *m;
  const mxArray *y;
  real_T b_B_data[27];
  real_T b_A_data[9];
  real_T tau_data[3];
  real_T tol;
  int32_T jpvt_data[3];
  int32_T A_size_idx_0;
  int32_T A_size_idx_1;
  int32_T B_size_idx_0;
  int32_T Y_data_tmp;
  int32_T b_k;
  int32_T j;
  int32_T k;
  int32_T loop_ub;
  int32_T maxmn;
  int32_T minmana;
  int32_T minmn;
  int32_T rankA;
  boolean_T p;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  st.site = &gi_emlrtRSI;
  maxmn = A_size[0];
  A_size_idx_0 = A_size[0];
  loop_ub = A_size[1];
  A_size_idx_1 = A_size[1];
  minmn = A_size[0] * A_size[1];
  if (minmn - 1 >= 0) {
    memcpy(&b_A_data[0], &A_data[0], (uint32_T)minmn * sizeof(real_T));
  }
  if (loop_ub - 1 >= 0) {
    memset(&jpvt_data[0], 0, (uint32_T)loop_ub * sizeof(int32_T));
  }
  b_st.site = &ji_emlrtRSI;
  minmana = muIntScalarMin_sint32(A_size[0], A_size[1]);
  if ((A_size[0] == 0) || (A_size[1] == 0)) {
    if (minmana - 1 >= 0) {
      memset(&tau_data[0], 0, (uint32_T)minmana * sizeof(real_T));
    }
    c_st.site = &ki_emlrtRSI;
    for (k = 0; k < loop_ub; k++) {
      jpvt_data[k] = k + 1;
    }
  } else {
    for (k = 0; k < loop_ub; k++) {
      jpvt_t_data[k] = (ptrdiff_t)0;
    }
    nrc_t = LAPACKE_dgeqp3(102, (ptrdiff_t)A_size[0], (ptrdiff_t)A_size[1],
                           &b_A_data[0], (ptrdiff_t)A_size[0], &jpvt_t_data[0],
                           &tau_data[0]);
    c_st.site = &li_emlrtRSI;
    if ((int32_T)nrc_t != 0) {
      p = true;
      if ((int32_T)nrc_t != -4) {
        if ((int32_T)nrc_t == -1010) {
          emlrtErrorWithMessageIdR2018a(&c_st, &h_emlrtRTEI, "MATLAB:nomem",
                                        "MATLAB:nomem", 0);
        } else {
          emlrtErrorWithMessageIdR2018a(&c_st, &g_emlrtRTEI,
                                        "Coder:toolbox:LAPACKCallErrorInfo",
                                        "Coder:toolbox:LAPACKCallErrorInfo", 5,
                                        4, 14, &fname[0], 12, (int32_T)nrc_t);
        }
      }
    } else {
      p = false;
    }
    if (p) {
      c_st.site = &mi_emlrtRSI;
      for (k = 0; k < loop_ub; k++) {
        c_st.site = &ni_emlrtRSI;
        for (j = 0; j < maxmn; j++) {
          b_A_data[k * maxmn + j] = rtNaN;
        }
      }
      c_st.site = &oi_emlrtRSI;
      for (k = 0; k < minmana; k++) {
        tau_data[k] = rtNaN;
      }
      minmn = minmana + 1;
      c_st.site = &pi_emlrtRSI;
      if (minmn <= minmana) {
        memset(&tau_data[minmn + -1], 0,
               (uint32_T)((minmana - minmn) + 1) * sizeof(real_T));
      }
      c_st.site = &qi_emlrtRSI;
      for (k = 0; k < loop_ub; k++) {
        jpvt_data[k] = k + 1;
      }
    } else {
      c_st.site = &ri_emlrtRSI;
      for (k = 0; k < loop_ub; k++) {
        jpvt_data[k] = (int32_T)jpvt_t_data[k];
      }
    }
  }
  st.site = &hi_emlrtRSI;
  rankA = 0;
  tol = 0.0;
  if (A_size[0] < A_size[1]) {
    minmn = A_size[0];
    maxmn = A_size[1];
  } else {
    minmn = A_size[1];
  }
  if (minmn > 0) {
    tol =
        2.2204460492503131E-15 * (real_T)maxmn * muDoubleScalarAbs(b_A_data[0]);
    while (
        (rankA < minmn) &&
        (!(muDoubleScalarAbs(b_A_data[rankA + A_size_idx_0 * rankA]) <= tol))) {
      rankA++;
    }
  }
  if ((rankA < minmn) && (!emlrtSetWarningFlag(&st))) {
    char_T str[14];
    b_st.site = &si_emlrtRSI;
    y = NULL;
    m = emlrtCreateCharArray(2, &b_iv[0]);
    emlrtInitCharArrayR2013a(&b_st, 6, m, &rfmt[0]);
    emlrtAssign(&y, m);
    b_y = NULL;
    m = emlrtCreateDoubleScalar(tol);
    emlrtAssign(&b_y, m);
    c_st.site = &nj_emlrtRSI;
    emlrt_marshallIn(&c_st, b_sprintf(&c_st, y, b_y, &c_emlrtMCI),
                     "<output of sprintf>", str);
    b_st.site = &ti_emlrtRSI;
    d_warning(&b_st, rankA, str);
  }
  st.site = &ii_emlrtRSI;
  B_size_idx_0 = B_size[0];
  minmn = B_size[0] * 9;
  if (minmn - 1 >= 0) {
    memcpy(&b_B_data[0], &B_data[0], (uint32_T)minmn * sizeof(real_T));
  }
  Y_size[0] = A_size[1];
  Y_size[1] = 9;
  minmn = A_size[1] * 9;
  if (minmn - 1 >= 0) {
    memset(&Y_data[0], 0, (uint32_T)minmn * sizeof(real_T));
  }
  b_st.site = &ui_emlrtRSI;
  c_st.site = &xi_emlrtRSI;
  if ((A_size[0] != 0) && (A_size[1] != 0) && (B_size[0] != 0)) {
    nrc_t = (ptrdiff_t)B_size[0];
    nrc_t = LAPACKE_dormqr(
        102, 'L', 'T', nrc_t, (ptrdiff_t)9,
        (ptrdiff_t)muIntScalarMin_sint32(A_size[0], A_size[1]), &b_A_data[0],
        (ptrdiff_t)A_size[0], &tau_data[0], &b_B_data[0], nrc_t);
    d_st.site = &yi_emlrtRSI;
    if ((int32_T)nrc_t != 0) {
      boolean_T b_p;
      p = true;
      b_p = false;
      if ((int32_T)nrc_t == -7) {
        b_p = true;
      } else if ((int32_T)nrc_t == -9) {
        b_p = true;
      } else if ((int32_T)nrc_t == -10) {
        b_p = true;
      }
      if (!b_p) {
        if ((int32_T)nrc_t == -1010) {
          emlrtErrorWithMessageIdR2018a(&d_st, &h_emlrtRTEI, "MATLAB:nomem",
                                        "MATLAB:nomem", 0);
        } else {
          emlrtErrorWithMessageIdR2018a(&d_st, &g_emlrtRTEI,
                                        "Coder:toolbox:LAPACKCallErrorInfo",
                                        "Coder:toolbox:LAPACKCallErrorInfo", 5,
                                        4, 14, &b_fname[0], 12, (int32_T)nrc_t);
        }
      }
    } else {
      p = false;
    }
    if (p) {
      if ((int32_T)nrc_t == -10) {
        for (j = 0; j < minmana; j++) {
          if (tau_data[j] != 0.0) {
            int32_T i;
            i = j + 2;
            for (b_k = 0; b_k < 9; b_k++) {
              real_T wj;
              int32_T wj_tmp;
              wj_tmp = B_size_idx_0 * b_k;
              minmn = j + wj_tmp;
              tol = b_B_data[minmn];
              wj = tol;
              for (k = i; k <= A_size_idx_0; k++) {
                wj += b_A_data[(k + A_size_idx_0 * j) - 1] *
                      b_B_data[(k + wj_tmp) - 1];
              }
              wj *= tau_data[j];
              if (wj != 0.0) {
                b_B_data[minmn] = tol - wj;
                minmn = j + 2;
                loop_ub = (((((A_size_idx_0 - j) - 1) / 2) << 1) + j) + 2;
                maxmn = loop_ub - 2;
                for (k = minmn; k <= maxmn; k += 2) {
                  __m128d r;
                  __m128d r1;
                  r = _mm_loadu_pd(&b_A_data[(k + A_size_idx_0 * j) - 1]);
                  Y_data_tmp = (k + wj_tmp) - 1;
                  r1 = _mm_loadu_pd(&b_B_data[Y_data_tmp]);
                  _mm_storeu_pd(&b_B_data[Y_data_tmp],
                                _mm_sub_pd(r1, _mm_mul_pd(r, _mm_set1_pd(wj))));
                }
                for (k = loop_ub; k <= A_size_idx_0; k++) {
                  minmn = (k + wj_tmp) - 1;
                  b_B_data[minmn] -= b_A_data[(k + A_size_idx_0 * j) - 1] * wj;
                }
              }
            }
          }
        }
      } else {
        minmn = B_size[0] * 9;
        for (k = 0; k < minmn; k++) {
          b_B_data[k] = rtNaN;
        }
      }
    }
  }
  for (b_k = 0; b_k < 9; b_k++) {
    b_st.site = &vi_emlrtRSI;
    for (k = 0; k < rankA; k++) {
      Y_data[(jpvt_data[k] + A_size_idx_1 * b_k) - 1] =
          b_B_data[k + B_size_idx_0 * b_k];
    }
    for (k = rankA; k >= 1; k--) {
      minmn = Y_size[0] * b_k;
      maxmn = (jpvt_data[k - 1] + minmn) - 1;
      loop_ub = A_size_idx_0 * (k - 1);
      Y_data[maxmn] /= b_A_data[(k + loop_ub) - 1];
      b_st.site = &wi_emlrtRSI;
      for (j = 0; j <= k - 2; j++) {
        Y_data_tmp = (jpvt_data[j] + minmn) - 1;
        Y_data[Y_data_tmp] -= Y_data[maxmn] * b_A_data[j + loop_ub];
      }
    }
  }
}
