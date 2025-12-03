/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mrdivide_helper.c
 *
 * Code generation for function 'mrdivide_helper'
 *
 */

/* Include files */
#include "mrdivide_helper.h"
#include "codegenTest_data.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "warning.h"
#include "blas.h"
#include "lapacke.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Variable Definitions */
static emlrtRSInfo vh_emlrtRSI = {
    42,      /* lineNo */
    "mrdiv", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\mrdivide_"
    "helper.m" /* pathName */
};

static emlrtRSInfo wh_emlrtRSI = {
    44,      /* lineNo */
    "mrdiv", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\mrdivide_"
    "helper.m" /* pathName */
};

static emlrtRSInfo
    xh_emlrtRSI =
        {
            67,        /* lineNo */
            "lusolve", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\lusolve.m" /* pathName */
};

static emlrtRSInfo
    yh_emlrtRSI =
        {
            107,          /* lineNo */
            "lusolveNxN", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\lusolve.m" /* pathName */
};

static emlrtRSInfo
    ai_emlrtRSI =
        {
            112,          /* lineNo */
            "lusolveNxN", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\lusolve.m" /* pathName */
};

static emlrtRSInfo
    bi_emlrtRSI =
        {
            135,          /* lineNo */
            "XtimesInvA", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\lusolve.m" /* pathName */
};

static emlrtRSInfo
    ci_emlrtRSI =
        {
            140,          /* lineNo */
            "XtimesInvA", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\lusolve.m" /* pathName */
};

static emlrtRSInfo
    di_emlrtRSI =
        {
            142,          /* lineNo */
            "XtimesInvA", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\lusolve.m" /* pathName */
};

static emlrtRSInfo ei_emlrtRSI = {
    27,       /* lineNo */
    "xgetrf", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgetrf.m" /* pathName */
};

static emlrtRSInfo fi_emlrtRSI = {
    91,             /* lineNo */
    "ceval_xgetrf", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgetrf.m" /* pathName */
};

static emlrtRSInfo ii_emlrtRSI = {
    67,      /* lineNo */
    "xtrsm", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+blas\\xtrsm."
    "m" /* pathName */
};

static emlrtRSInfo
    ki_emlrtRSI =
        {
            90,              /* lineNo */
            "warn_singular", /* fcnName */
            "C:\\Program "
            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
            "internal\\lusolve.m" /* pathName */
};

/* Function Definitions */
void mrdiv(const emlrtStack *sp, real32_T A_data[], int32_T A_size[2],
           const real32_T B_data[], const int32_T B_size[2])
{
  static const char_T fname[19] = {'L', 'A', 'P', 'A', 'C', 'K', 'E',
                                   '_', 's', 'g', 'e', 't', 'r', 'f',
                                   '_', 'w', 'o', 'r', 'k'};
  ptrdiff_t ipiv_t_data[3];
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  int32_T b_A_size[2];
  int32_T b_B_size[2];
  int32_T i;
  int32_T k;
  real32_T tmp_data[27];
  real32_T b_B_data[9];
  real32_T temp;
  char_T DIAGA1;
  char_T SIDE1;
  char_T TRANSA1;
  char_T UPLO1;
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
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  if ((A_size[1] == 0) || ((B_size[0] == 0) || (B_size[1] == 0))) {
    int32_T loop_ub;
    A_size[0] = 9;
    loop_ub = B_size[0];
    A_size[1] = B_size[0];
    for (k = 0; k < loop_ub; k++) {
      for (i = 0; i < 9; i++) {
        A_data[i + 9 * k] = 0.0F;
      }
    }
  } else if (B_size[0] == B_size[1]) {
    ptrdiff_t info_t;
    int32_T ipiv_data[3];
    int32_T loop_ub;
    st.site = &vh_emlrtRSI;
    b_st.site = &xh_emlrtRSI;
    c_st.site = &yh_emlrtRSI;
    d_st.site = &bi_emlrtRSI;
    loop_ub = B_size[0] * B_size[1];
    memcpy(&b_B_data[0], &B_data[0], (uint32_T)loop_ub * sizeof(real32_T));
    e_st.site = &ei_emlrtRSI;
    loop_ub = muIntScalarMin_sint32(B_size[1], B_size[1]);
    info_t = LAPACKE_sgetrf_work(102, (ptrdiff_t)B_size[1],
                                 (ptrdiff_t)B_size[1], &b_B_data[0],
                                 (ptrdiff_t)B_size[1], &ipiv_t_data[0]);
    f_st.site = &fi_emlrtRSI;
    if ((int32_T)info_t < 0) {
      if ((int32_T)info_t == -1010) {
        emlrtErrorWithMessageIdR2018a(&f_st, &i_emlrtRTEI, "MATLAB:nomem",
                                      "MATLAB:nomem", 0);
      } else {
        emlrtErrorWithMessageIdR2018a(&f_st, &h_emlrtRTEI,
                                      "Coder:toolbox:LAPACKCallErrorInfo",
                                      "Coder:toolbox:LAPACKCallErrorInfo", 5, 4,
                                      19, &fname[0], 12, (int32_T)info_t);
      }
    }
    for (k = 0; k < loop_ub; k++) {
      ipiv_data[k] = (int32_T)ipiv_t_data[k];
    }
    d_st.site = &ci_emlrtRSI;
    e_st.site = &ii_emlrtRSI;
    temp = 1.0F;
    DIAGA1 = 'N';
    TRANSA1 = 'N';
    UPLO1 = 'U';
    SIDE1 = 'R';
    m_t = (ptrdiff_t)9;
    n_t = (ptrdiff_t)B_size[1];
    lda_t = (ptrdiff_t)B_size[1];
    ldb_t = (ptrdiff_t)9;
    strsm(&SIDE1, &UPLO1, &TRANSA1, &DIAGA1, &m_t, &n_t, &temp, &b_B_data[0],
          &lda_t, &A_data[0], &ldb_t);
    d_st.site = &di_emlrtRSI;
    e_st.site = &ii_emlrtRSI;
    temp = 1.0F;
    DIAGA1 = 'U';
    TRANSA1 = 'N';
    UPLO1 = 'L';
    SIDE1 = 'R';
    m_t = (ptrdiff_t)9;
    n_t = (ptrdiff_t)B_size[1];
    lda_t = (ptrdiff_t)B_size[1];
    ldb_t = (ptrdiff_t)9;
    strsm(&SIDE1, &UPLO1, &TRANSA1, &DIAGA1, &m_t, &n_t, &temp, &b_B_data[0],
          &lda_t, &A_data[0], &ldb_t);
    loop_ub = B_size[1] - 1;
    for (k = loop_ub; k >= 1; k--) {
      int32_T b_loop_ub;
      b_loop_ub = ipiv_data[k - 1];
      if (b_loop_ub != k) {
        for (i = 0; i < 9; i++) {
          int32_T b_i;
          int32_T temp_tmp;
          temp_tmp = i + 9 * (k - 1);
          temp = A_data[temp_tmp];
          b_i = i + 9 * (b_loop_ub - 1);
          A_data[temp_tmp] = A_data[b_i];
          A_data[b_i] = temp;
        }
      }
    }
    if (((B_size[0] != 1) || (B_size[1] != 1)) && ((int32_T)info_t > 0)) {
      c_st.site = &ai_emlrtRSI;
      if (!emlrtSetWarningFlag(&c_st)) {
        d_st.site = &ki_emlrtRSI;
        c_warning(&d_st);
      }
    }
  } else {
    int32_T tmp_size[2];
    int32_T b_loop_ub;
    int32_T loop_ub;
    real32_T b_A_data[27];
    loop_ub = B_size[1];
    b_B_size[0] = B_size[1];
    b_loop_ub = B_size[0];
    b_B_size[1] = B_size[0];
    for (k = 0; k < b_loop_ub; k++) {
      for (i = 0; i < loop_ub; i++) {
        b_B_data[i + b_B_size[0] * k] = B_data[k + B_size[0] * i];
      }
    }
    loop_ub = A_size[1];
    b_A_size[0] = loop_ub;
    b_A_size[1] = 9;
    for (k = 0; k < 9; k++) {
      for (i = 0; i < loop_ub; i++) {
        b_A_data[i + loop_ub * k] = A_data[k + 9 * i];
      }
    }
    st.site = &wh_emlrtRSI;
    qrsolve(&st, b_B_data, b_B_size, b_A_data, b_A_size, tmp_data, tmp_size);
    A_size[0] = 9;
    loop_ub = tmp_size[0];
    A_size[1] = tmp_size[0];
    for (k = 0; k < loop_ub; k++) {
      for (i = 0; i < 9; i++) {
        A_data[i + 9 * k] = tmp_data[k + tmp_size[0] * i];
      }
    }
  }
}

/* End of code generation (mrdivide_helper.c) */
