/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * qrsolve.c
 *
 * Code generation for function 'qrsolve'
 *
 */

/* Include files */
#include "qrsolve.h"
#include "codegenTest_data.h"
#include "rt_nonfinite.h"
#include "warning.h"
#include "lapacke.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Variable Definitions */
static emlrtRSInfo
    li_emlrtRSI =
        {
            61,        /* lineNo */
            "qrsolve", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\qrsolve.m" /* pathName */
};

static emlrtRSInfo
    mi_emlrtRSI =
        {
            72,        /* lineNo */
            "qrsolve", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\qrsolve.m" /* pathName */
};

static emlrtRSInfo
    ni_emlrtRSI =
        {
            85,        /* lineNo */
            "qrsolve", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\qrsolve.m" /* pathName */
};

static emlrtRSInfo oi_emlrtRSI = {
    63,       /* lineNo */
    "xgeqp3", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeqp3.m" /* pathName */
};

static emlrtRSInfo pi_emlrtRSI = {
    98,             /* lineNo */
    "ceval_xgeqp3", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeqp3.m" /* pathName */
};

static emlrtRSInfo qi_emlrtRSI = {
    138,            /* lineNo */
    "ceval_xgeqp3", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeqp3.m" /* pathName */
};

static emlrtRSInfo ri_emlrtRSI = {
    141,            /* lineNo */
    "ceval_xgeqp3", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeqp3.m" /* pathName */
};

static emlrtRSInfo si_emlrtRSI = {
    143,            /* lineNo */
    "ceval_xgeqp3", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeqp3.m" /* pathName */
};

static emlrtRSInfo ti_emlrtRSI = {
    148,            /* lineNo */
    "ceval_xgeqp3", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeqp3.m" /* pathName */
};

static emlrtRSInfo ui_emlrtRSI = {
    151,            /* lineNo */
    "ceval_xgeqp3", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeqp3.m" /* pathName */
};

static emlrtRSInfo vi_emlrtRSI = {
    154,            /* lineNo */
    "ceval_xgeqp3", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeqp3.m" /* pathName */
};

static emlrtRSInfo wi_emlrtRSI = {
    158,            /* lineNo */
    "ceval_xgeqp3", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeqp3.m" /* pathName */
};

static emlrtRSInfo
    xi_emlrtRSI =
        {
            173,          /* lineNo */
            "rankFromQR", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\qrsolve.m" /* pathName */
};

static emlrtRSInfo
    yi_emlrtRSI =
        {
            172,          /* lineNo */
            "rankFromQR", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\qrsolve.m" /* pathName */
};

static emlrtRSInfo
    aj_emlrtRSI =
        {
            119,         /* lineNo */
            "LSQFromQR", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\qrsolve.m" /* pathName */
};

static emlrtRSInfo
    bj_emlrtRSI =
        {
            128,         /* lineNo */
            "LSQFromQR", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\qrsolve.m" /* pathName */
};

static emlrtRSInfo
    cj_emlrtRSI =
        {
            138,         /* lineNo */
            "LSQFromQR", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\qrsolve.m" /* pathName */
};

static emlrtRSInfo dj_emlrtRSI = {
    40,         /* lineNo */
    "xunormqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xunormqr.m" /* pathName */
};

static emlrtRSInfo ej_emlrtRSI = {
    106,              /* lineNo */
    "ceval_xunormqr", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xunormqr.m" /* pathName */
};

static emlrtMCInfo c_emlrtMCI = {
    53,        /* lineNo */
    19,        /* colNo */
    "flt2str", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\flt2str.m" /* pName */
};

static emlrtRSInfo sj_emlrtRSI = {
    53,        /* lineNo */
    "flt2str", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\flt2str.m" /* pathName */
};

/* Function Declarations */
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

/* Function Definitions */
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

void qrsolve(const emlrtStack *sp, const real32_T A_data[],
             const int32_T A_size[2], const real32_T B_data[],
             const int32_T B_size[2], real32_T Y_data[], int32_T Y_size[2])
{
  static const int32_T b_iv[2] = {1, 6};
  static const char_T b_fname[14] = {'L', 'A', 'P', 'A', 'C', 'K', 'E',
                                     '_', 's', 'o', 'r', 'm', 'q', 'r'};
  static const char_T fname[14] = {'L', 'A', 'P', 'A', 'C', 'K', 'E',
                                   '_', 's', 'g', 'e', 'q', 'p', '3'};
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
  real32_T b_B_data[27];
  real32_T b_A_data[9];
  real32_T tau_data[3];
  real32_T tol;
  boolean_T p;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  st.site = &li_emlrtRSI;
  maxmn = A_size[0];
  A_size_idx_0 = A_size[0];
  loop_ub = A_size[1];
  A_size_idx_1 = A_size[1];
  minmn = A_size[0] * A_size[1];
  if (minmn - 1 >= 0) {
    memcpy(&b_A_data[0], &A_data[0], (uint32_T)minmn * sizeof(real32_T));
  }
  if (loop_ub - 1 >= 0) {
    memset(&jpvt_data[0], 0, (uint32_T)loop_ub * sizeof(int32_T));
  }
  b_st.site = &oi_emlrtRSI;
  minmana = muIntScalarMin_sint32(A_size[0], A_size[1]);
  if ((A_size[0] == 0) || (A_size[1] == 0)) {
    if (minmana - 1 >= 0) {
      memset(&tau_data[0], 0, (uint32_T)minmana * sizeof(real32_T));
    }
    c_st.site = &pi_emlrtRSI;
    for (k = 0; k < loop_ub; k++) {
      jpvt_data[k] = k + 1;
    }
  } else {
    for (k = 0; k < loop_ub; k++) {
      jpvt_t_data[k] = (ptrdiff_t)0;
    }
    nrc_t = LAPACKE_sgeqp3(102, (ptrdiff_t)A_size[0], (ptrdiff_t)A_size[1],
                           &b_A_data[0], (ptrdiff_t)A_size[0], &jpvt_t_data[0],
                           &tau_data[0]);
    c_st.site = &qi_emlrtRSI;
    if ((int32_T)nrc_t != 0) {
      p = true;
      if ((int32_T)nrc_t != -4) {
        if ((int32_T)nrc_t == -1010) {
          emlrtErrorWithMessageIdR2018a(&c_st, &i_emlrtRTEI, "MATLAB:nomem",
                                        "MATLAB:nomem", 0);
        } else {
          emlrtErrorWithMessageIdR2018a(&c_st, &h_emlrtRTEI,
                                        "Coder:toolbox:LAPACKCallErrorInfo",
                                        "Coder:toolbox:LAPACKCallErrorInfo", 5,
                                        4, 14, &fname[0], 12, (int32_T)nrc_t);
        }
      }
    } else {
      p = false;
    }
    if (p) {
      c_st.site = &ri_emlrtRSI;
      for (k = 0; k < loop_ub; k++) {
        c_st.site = &si_emlrtRSI;
        for (j = 0; j < maxmn; j++) {
          b_A_data[k * maxmn + j] = rtNaNF;
        }
      }
      c_st.site = &ti_emlrtRSI;
      for (k = 0; k < minmana; k++) {
        tau_data[k] = rtNaNF;
      }
      minmn = minmana + 1;
      c_st.site = &ui_emlrtRSI;
      if (minmn <= minmana) {
        memset(&tau_data[minmn + -1], 0,
               (uint32_T)((minmana - minmn) + 1) * sizeof(real32_T));
      }
      c_st.site = &vi_emlrtRSI;
      for (k = 0; k < loop_ub; k++) {
        jpvt_data[k] = k + 1;
      }
    } else {
      c_st.site = &wi_emlrtRSI;
      for (k = 0; k < loop_ub; k++) {
        jpvt_data[k] = (int32_T)jpvt_t_data[k];
      }
    }
  }
  st.site = &mi_emlrtRSI;
  rankA = 0;
  tol = 0.0F;
  if (A_size[0] < A_size[1]) {
    minmn = A_size[0];
    maxmn = A_size[1];
  } else {
    minmn = A_size[1];
  }
  if (minmn > 0) {
    tol = 1.1920929E-6F * (real32_T)maxmn * muSingleScalarAbs(b_A_data[0]);
    while (
        (rankA < minmn) &&
        (!(muSingleScalarAbs(b_A_data[rankA + A_size_idx_0 * rankA]) <= tol))) {
      rankA++;
    }
  }
  if ((rankA < minmn) && (!emlrtSetWarningFlag(&st))) {
    char_T str[14];
    b_st.site = &xi_emlrtRSI;
    y = NULL;
    m = emlrtCreateCharArray(2, &b_iv[0]);
    emlrtInitCharArrayR2013a(&b_st, 6, m, &rfmt[0]);
    emlrtAssign(&y, m);
    b_y = NULL;
    m = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
    *(real32_T *)emlrtMxGetData(m) = tol;
    emlrtAssign(&b_y, m);
    c_st.site = &sj_emlrtRSI;
    emlrt_marshallIn(&c_st, b_sprintf(&c_st, y, b_y, &c_emlrtMCI),
                     "<output of sprintf>", str);
    b_st.site = &yi_emlrtRSI;
    d_warning(&b_st, rankA, str);
  }
  st.site = &ni_emlrtRSI;
  B_size_idx_0 = B_size[0];
  minmn = B_size[0] * 9;
  if (minmn - 1 >= 0) {
    memcpy(&b_B_data[0], &B_data[0], (uint32_T)minmn * sizeof(real32_T));
  }
  Y_size[0] = A_size[1];
  Y_size[1] = 9;
  minmn = A_size[1] * 9;
  if (minmn - 1 >= 0) {
    memset(&Y_data[0], 0, (uint32_T)minmn * sizeof(real32_T));
  }
  b_st.site = &aj_emlrtRSI;
  c_st.site = &dj_emlrtRSI;
  if ((A_size[0] != 0) && (A_size[1] != 0) && (B_size[0] != 0)) {
    nrc_t = (ptrdiff_t)B_size[0];
    nrc_t = LAPACKE_sormqr(
        102, 'L', 'T', nrc_t, (ptrdiff_t)9,
        (ptrdiff_t)muIntScalarMin_sint32(A_size[0], A_size[1]), &b_A_data[0],
        (ptrdiff_t)A_size[0], &tau_data[0], &b_B_data[0], nrc_t);
    d_st.site = &ej_emlrtRSI;
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
          emlrtErrorWithMessageIdR2018a(&d_st, &i_emlrtRTEI, "MATLAB:nomem",
                                        "MATLAB:nomem", 0);
        } else {
          emlrtErrorWithMessageIdR2018a(&d_st, &h_emlrtRTEI,
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
          if (tau_data[j] != 0.0F) {
            Y_data_tmp = j + 2;
            for (b_k = 0; b_k < 9; b_k++) {
              real32_T wj;
              loop_ub = B_size_idx_0 * b_k;
              minmn = j + loop_ub;
              tol = b_B_data[minmn];
              wj = tol;
              for (k = Y_data_tmp; k <= A_size_idx_0; k++) {
                wj += b_A_data[(k + A_size_idx_0 * j) - 1] *
                      b_B_data[(k + loop_ub) - 1];
              }
              wj *= tau_data[j];
              if (wj != 0.0F) {
                b_B_data[minmn] = tol - wj;
                minmn = j + 2;
                for (k = minmn; k <= A_size_idx_0; k++) {
                  maxmn = (k + loop_ub) - 1;
                  b_B_data[maxmn] -= b_A_data[(k + A_size_idx_0 * j) - 1] * wj;
                }
              }
            }
          }
        }
      } else {
        minmn = B_size[0] * 9;
        for (k = 0; k < minmn; k++) {
          b_B_data[k] = rtNaNF;
        }
      }
    }
  }
  for (b_k = 0; b_k < 9; b_k++) {
    b_st.site = &bj_emlrtRSI;
    for (k = 0; k < rankA; k++) {
      Y_data[(jpvt_data[k] + A_size_idx_1 * b_k) - 1] =
          b_B_data[k + B_size_idx_0 * b_k];
    }
    for (k = rankA; k >= 1; k--) {
      minmn = Y_size[0] * b_k;
      maxmn = (jpvt_data[k - 1] + minmn) - 1;
      loop_ub = A_size_idx_0 * (k - 1);
      Y_data[maxmn] /= b_A_data[(k + loop_ub) - 1];
      b_st.site = &cj_emlrtRSI;
      for (j = 0; j <= k - 2; j++) {
        Y_data_tmp = (jpvt_data[j] + minmn) - 1;
        Y_data[Y_data_tmp] -= Y_data[maxmn] * b_A_data[j + loop_ub];
      }
    }
  }
}

/* End of code generation (qrsolve.c) */
