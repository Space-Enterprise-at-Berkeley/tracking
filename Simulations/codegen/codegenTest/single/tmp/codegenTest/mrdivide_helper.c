#include "mrdivide_helper.h"
#include "codegenTest_float_mex_data.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "warning.h"
#include "blas.h"
#include "lapacke.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

static emlrtRSInfo qh_emlrtRSI = {42, "mrdiv",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\mrdivide_helper.m"};

static emlrtRSInfo rh_emlrtRSI = {44, "mrdiv",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\mrdivide_helper.m"};

static emlrtRSInfo sh_emlrtRSI = {
    67, "lusolve",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"};

static emlrtRSInfo th_emlrtRSI = {
    107, "lusolveNxN",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"};

static emlrtRSInfo uh_emlrtRSI = {
    112, "lusolveNxN",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"};

static emlrtRSInfo vh_emlrtRSI = {
    135, "XtimesInvA",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"};

static emlrtRSInfo wh_emlrtRSI = {
    140, "XtimesInvA",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"};

static emlrtRSInfo xh_emlrtRSI = {
    142, "XtimesInvA",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"};

static emlrtRSInfo yh_emlrtRSI = {27, "xgetrf",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgetrf.m"};

static emlrtRSInfo ai_emlrtRSI = {91, "ceval_xgetrf",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgetrf.m"};

static emlrtRSInfo di_emlrtRSI = {67, "xtrsm",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+blas\\xtrsm.m"};

static emlrtRSInfo fi_emlrtRSI = {
    90, "warn_singular",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"};

void mrdiv(const emlrtStack *sp, real_T A_data[], int32_T A_size[2],
           const real_T B_data[], const int32_T B_size[2])
{
  static const char_T fname[19] = {'L', 'A', 'P', 'A', 'C', 'K', 'E',
                                   '_', 'd', 'g', 'e', 't', 'r', 'f',
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
  real_T tmp_data[27];
  real_T b_B_data[9];
  real_T temp;
  int32_T b_A_size[2];
  int32_T b_B_size[2];
  int32_T i;
  int32_T k;
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
      memset(&A_data[k * 9], 0, 9U * sizeof(real_T));
    }
  } else if (B_size[0] == B_size[1]) {
    ptrdiff_t info_t;
    int32_T ipiv_data[3];
    int32_T loop_ub;
    st.site = &qh_emlrtRSI;
    b_st.site = &sh_emlrtRSI;
    c_st.site = &th_emlrtRSI;
    d_st.site = &vh_emlrtRSI;
    loop_ub = B_size[0] * B_size[1];
    memcpy(&b_B_data[0], &B_data[0], (uint32_T)loop_ub * sizeof(real_T));
    e_st.site = &yh_emlrtRSI;
    loop_ub = muIntScalarMin_sint32(B_size[1], B_size[1]);
    info_t = LAPACKE_dgetrf_work(102, (ptrdiff_t)B_size[1],
                                 (ptrdiff_t)B_size[1], &b_B_data[0],
                                 (ptrdiff_t)B_size[1], &ipiv_t_data[0]);
    f_st.site = &ai_emlrtRSI;
    if ((int32_T)info_t < 0) {
      if ((int32_T)info_t == -1010) {
        emlrtErrorWithMessageIdR2018a(&f_st, &h_emlrtRTEI, "MATLAB:nomem",
                                      "MATLAB:nomem", 0);
      } else {
        emlrtErrorWithMessageIdR2018a(&f_st, &g_emlrtRTEI,
                                      "Coder:toolbox:LAPACKCallErrorInfo",
                                      "Coder:toolbox:LAPACKCallErrorInfo", 5, 4,
                                      19, &fname[0], 12, (int32_T)info_t);
      }
    }
    for (k = 0; k < loop_ub; k++) {
      ipiv_data[k] = (int32_T)ipiv_t_data[k];
    }
    d_st.site = &wh_emlrtRSI;
    e_st.site = &di_emlrtRSI;
    temp = 1.0;
    DIAGA1 = 'N';
    TRANSA1 = 'N';
    UPLO1 = 'U';
    SIDE1 = 'R';
    m_t = (ptrdiff_t)9;
    n_t = (ptrdiff_t)B_size[1];
    lda_t = (ptrdiff_t)B_size[1];
    ldb_t = (ptrdiff_t)9;
    dtrsm(&SIDE1, &UPLO1, &TRANSA1, &DIAGA1, &m_t, &n_t, &temp, &b_B_data[0],
          &lda_t, &A_data[0], &ldb_t);
    d_st.site = &xh_emlrtRSI;
    e_st.site = &di_emlrtRSI;
    temp = 1.0;
    DIAGA1 = 'U';
    TRANSA1 = 'N';
    UPLO1 = 'L';
    SIDE1 = 'R';
    m_t = (ptrdiff_t)9;
    n_t = (ptrdiff_t)B_size[1];
    lda_t = (ptrdiff_t)B_size[1];
    ldb_t = (ptrdiff_t)9;
    dtrsm(&SIDE1, &UPLO1, &TRANSA1, &DIAGA1, &m_t, &n_t, &temp, &b_B_data[0],
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
      c_st.site = &uh_emlrtRSI;
      if (!emlrtSetWarningFlag(&c_st)) {
        d_st.site = &fi_emlrtRSI;
        c_warning(&d_st);
      }
    }
  } else {
    real_T b_A_data[27];
    int32_T tmp_size[2];
    int32_T b_loop_ub;
    int32_T loop_ub;
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
    st.site = &rh_emlrtRSI;
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
