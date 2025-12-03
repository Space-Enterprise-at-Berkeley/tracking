/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eigStandard.c
 *
 * Code generation for function 'eigStandard'
 *
 */

/* Include files */
#include "eigStandard.h"
#include "codegenTest_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "warning.h"
#include "xdlahqr.h"
#include "xgemv.h"
#include "xgerc.h"
#include "xzgebal.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "xzlascl.h"
#include "mwmathutil.h"
#include <string.h>
#include <xmmintrin.h>

/* Variable Definitions */
static emlrtRSInfo kf_emlrtRSI = {
    34,            /* lineNo */
    "eigStandard", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigStan"
    "dard.m" /* pathName */
};

static emlrtRSInfo lf_emlrtRSI = {
    45,            /* lineNo */
    "eigStandard", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\private\\eigStan"
    "dard.m" /* pathName */
};

static emlrtRSInfo mf_emlrtRSI = {
    54,      /* lineNo */
    "xgeev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\xgeev.m" /* pathName */
};

static emlrtRSInfo nf_emlrtRSI = {
    49,       /* lineNo */
    "xdgeev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdgeev.m" /* pathName */
};

static emlrtRSInfo of_emlrtRSI = {
    67,       /* lineNo */
    "xdgeev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdgeev.m" /* pathName */
};

static emlrtRSInfo pf_emlrtRSI = {
    73,       /* lineNo */
    "xdgeev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdgeev.m" /* pathName */
};

static emlrtRSInfo qf_emlrtRSI = {
    130,      /* lineNo */
    "xdgeev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdgeev.m" /* pathName */
};

static emlrtRSInfo rf_emlrtRSI = {
    131,      /* lineNo */
    "xdgeev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdgeev.m" /* pathName */
};

static emlrtRSInfo sf_emlrtRSI = {
    133,      /* lineNo */
    "xdgeev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdgeev.m" /* pathName */
};

static emlrtRSInfo tf_emlrtRSI = {
    134,      /* lineNo */
    "xdgeev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdgeev.m" /* pathName */
};

static emlrtRSInfo uf_emlrtRSI = {
    139,      /* lineNo */
    "xdgeev", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xdgeev.m" /* pathName */
};

static emlrtRSInfo hg_emlrtRSI = {
    28,        /* lineNo */
    "xzgehrd", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgehrd.m" /* pathName */
};

static emlrtRSInfo ig_emlrtRSI = {
    37,        /* lineNo */
    "xzgehrd", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgehrd.m" /* pathName */
};

/* Function Definitions */
void eigStandard(const emlrtStack *sp, const real32_T A[9], creal32_T V[3])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack st;
  int32_T b_i;
  int32_T i;
  int32_T ihi;
  int32_T im1n;
  real32_T a[9];
  real32_T tau[2];
  real32_T absxk;
  real32_T anrm;
  boolean_T exitg1;
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
  st.site = &kf_emlrtRSI;
  b_st.site = &mf_emlrtRSI;
  for (i = 0; i < 9; i++) {
    a[i] = A[i];
  }
  b_i = 0;
  anrm = 0.0F;
  im1n = 0;
  exitg1 = false;
  while ((!exitg1) && (im1n < 9)) {
    absxk = muSingleScalarAbs(A[im1n]);
    if (muSingleScalarIsNaN(absxk)) {
      anrm = rtNaNF;
      exitg1 = true;
    } else {
      if (absxk > anrm) {
        anrm = absxk;
      }
      im1n++;
    }
  }
  if (muSingleScalarIsInf(anrm) || muSingleScalarIsNaN(anrm)) {
    V[0].re = rtNaNF;
    V[0].im = 0.0F;
    V[1].re = rtNaNF;
    V[1].im = 0.0F;
    V[2].re = rtNaNF;
    V[2].im = 0.0F;
  } else {
    int32_T ilo;
    real32_T wi[3];
    real32_T work[3];
    real32_T cscale;
    real32_T ctoc;
    boolean_T guard1;
    boolean_T scalea;
    cscale = anrm;
    scalea = false;
    guard1 = false;
    if ((anrm > 0.0F) && (anrm < 9.09494702E-13F)) {
      scalea = true;
      cscale = 9.09494702E-13F;
      guard1 = true;
    } else if (anrm > 1.09951163E+12F) {
      scalea = true;
      cscale = 1.09951163E+12F;
      guard1 = true;
    }
    if (guard1) {
      boolean_T notdone;
      absxk = anrm;
      ctoc = cscale;
      notdone = true;
      while (notdone) {
        __m128 r;
        __m128 r1;
        real32_T cfrom1;
        real32_T cto1;
        real32_T mul;
        cfrom1 = absxk * 1.97215226E-31F;
        cto1 = ctoc / 5.0706024E+30F;
        if ((cfrom1 > ctoc) && (ctoc != 0.0F)) {
          mul = 1.97215226E-31F;
          absxk = cfrom1;
        } else if (cto1 > absxk) {
          mul = 5.0706024E+30F;
          ctoc = cto1;
        } else {
          mul = ctoc / absxk;
          notdone = false;
        }
        r = _mm_loadu_ps(&a[0]);
        r1 = _mm_set1_ps(mul);
        _mm_storeu_ps(&a[0], _mm_mul_ps(r, r1));
        r = _mm_loadu_ps(&a[4]);
        _mm_storeu_ps(&a[4], _mm_mul_ps(r, r1));
        a[8] *= mul;
      }
    }
    c_st.site = &nf_emlrtRSI;
    ilo = xzgebal(&c_st, a, &ihi, work);
    c_st.site = &of_emlrtRSI;
    if ((ihi - ilo) + 1 > 1) {
      d_st.site = &hg_emlrtRSI;
      if (ilo - 1 > 2147483646) {
        e_st.site = &kb_emlrtRSI;
        check_forloop_overflow_error(&e_st);
      }
      im1n = (uint8_T)(ilo - 1);
      if (im1n - 1 >= 0) {
        memset(&tau[0], 0, (uint32_T)im1n * sizeof(real32_T));
      }
      for (i = ihi; i < 3; i++) {
        tau[i - 1] = 0.0F;
      }
      work[0] = 0.0F;
      work[1] = 0.0F;
      work[2] = 0.0F;
      d_st.site = &ig_emlrtRSI;
      if ((ilo <= ihi - 1) && (ihi - 1 > 2147483646)) {
        e_st.site = &kb_emlrtRSI;
        check_forloop_overflow_error(&e_st);
      }
      for (i = ilo; i < ihi; i++) {
        int32_T alpha1_tmp;
        int32_T in;
        int32_T lastv;
        int32_T n;
        im1n = (i - 1) * 3;
        in = i * 3 + 1;
        n = ihi - i;
        alpha1_tmp = i + im1n;
        absxk = a[alpha1_tmp];
        d_st.site = &wd_emlrtRSI;
        ctoc = xzlarfg(&d_st, n, &absxk, a, im1n + 3);
        tau[i - 1] = ctoc;
        a[alpha1_tmp] = 1.0F;
        d_st.site = &xd_emlrtRSI;
        if (ctoc != 0.0F) {
          lastv = n;
          b_i = (alpha1_tmp + n) + 1;
          while ((lastv > 0) && (a[b_i - 2] == 0.0F)) {
            lastv--;
            b_i--;
          }
          im1n = ihi;
          exitg1 = false;
          while ((!exitg1) && (im1n > 0)) {
            int32_T exitg2;
            int32_T ia;
            b_i = (in + im1n) - 1;
            ia = b_i;
            do {
              exitg2 = 0;
              if (ia <= b_i + (lastv - 1) * 3) {
                if (a[ia - 1] != 0.0F) {
                  exitg2 = 1;
                } else {
                  ia += 3;
                }
              } else {
                im1n--;
                exitg2 = 2;
              }
            } while (exitg2 == 0);
            if (exitg2 == 1) {
              exitg1 = true;
            }
          }
        } else {
          lastv = 0;
          im1n = 0;
        }
        if (lastv > 0) {
          e_st.site = &ae_emlrtRSI;
          xgemv(&e_st, im1n, lastv, a, in, a, alpha1_tmp + 1, work);
          e_st.site = &be_emlrtRSI;
          xgerc(&e_st, im1n, lastv, -tau[i - 1], work, alpha1_tmp + 1, a, in);
        }
        d_st.site = &yd_emlrtRSI;
        xzlarf(&d_st, n, 3 - i, alpha1_tmp + 1, tau[i - 1], a, i + in, work);
        a[alpha1_tmp] = absxk;
      }
    }
    c_st.site = &pf_emlrtRSI;
    b_i = xdlahqr(&c_st, ilo, ihi, a, work, wi);
    if (scalea) {
      c_st.site = &qf_emlrtRSI;
      xzlascl(&c_st, cscale, anrm, 3 - b_i, work, b_i + 1);
      c_st.site = &rf_emlrtRSI;
      xzlascl(&c_st, cscale, anrm, 3 - b_i, wi, b_i + 1);
      if (b_i != 0) {
        c_st.site = &sf_emlrtRSI;
        b_xzlascl(&c_st, cscale, anrm, ilo - 1, work);
        c_st.site = &tf_emlrtRSI;
        b_xzlascl(&c_st, cscale, anrm, ilo - 1, wi);
      }
    }
    if (b_i != 0) {
      c_st.site = &uf_emlrtRSI;
      if ((ilo <= b_i) && (b_i > 2147483646)) {
        d_st.site = &kb_emlrtRSI;
        check_forloop_overflow_error(&d_st);
      }
      for (i = ilo; i <= b_i; i++) {
        work[i - 1] = rtNaNF;
        wi[i - 1] = 0.0F;
      }
    }
    V[0].re = work[0];
    V[0].im = wi[0];
    V[1].re = work[1];
    V[1].im = wi[1];
    V[2].re = work[2];
    V[2].im = wi[2];
  }
  if ((b_i != 0) && (!emlrtSetWarningFlag((emlrtCTX)sp))) {
    st.site = &lf_emlrtRSI;
    warning(&st);
  }
}

/* End of code generation (eigStandard.c) */
