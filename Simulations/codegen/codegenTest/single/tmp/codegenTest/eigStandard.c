#include "eigStandard.h"
#include "codegenTest_float_mex_data.h"
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
#include <emmintrin.h>
#include <string.h>

static emlrtRSInfo ff_emlrtRSI = {34, "eigStandard",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\ma"
                                  "tlab\\matfun\\private\\eigStandard.m"};

static emlrtRSInfo gf_emlrtRSI = {45, "eigStandard",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\ma"
                                  "tlab\\matfun\\private\\eigStandard.m"};

static emlrtRSInfo hf_emlrtRSI = {54, "xgeev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+lapack\\xgeev.m"};

static emlrtRSInfo if_emlrtRSI = {49, "xdgeev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdgeev.m"};

static emlrtRSInfo jf_emlrtRSI = {67, "xdgeev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdgeev.m"};

static emlrtRSInfo kf_emlrtRSI = {73, "xdgeev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdgeev.m"};

static emlrtRSInfo lf_emlrtRSI = {130, "xdgeev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdgeev.m"};

static emlrtRSInfo mf_emlrtRSI = {131, "xdgeev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdgeev.m"};

static emlrtRSInfo nf_emlrtRSI = {133, "xdgeev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdgeev.m"};

static emlrtRSInfo of_emlrtRSI = {134, "xdgeev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdgeev.m"};

static emlrtRSInfo pf_emlrtRSI = {139, "xdgeev",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xdgeev.m"};

static emlrtRSInfo cg_emlrtRSI = {28, "xzgehrd",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgehrd.m"};

static emlrtRSInfo dg_emlrtRSI = {37, "xzgehrd",
                                  "C:\\Program "
                                  "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                                  "coder\\+internal\\+reflapack\\xzgehrd.m"};

void eigStandard(const emlrtStack *sp, const real_T A[9], creal_T V[3])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack st;
  real_T a[9];
  real_T tau[2];
  real_T absxk;
  real_T anrm;
  int32_T b_i;
  int32_T i;
  int32_T ihi;
  int32_T im1n;
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
  st.site = &ff_emlrtRSI;
  b_st.site = &hf_emlrtRSI;
  memcpy(&a[0], &A[0], 9U * sizeof(real_T));
  i = 0;
  anrm = 0.0;
  im1n = 0;
  exitg1 = false;
  while ((!exitg1) && (im1n < 9)) {
    absxk = muDoubleScalarAbs(A[im1n]);
    if (muDoubleScalarIsNaN(absxk)) {
      anrm = rtNaN;
      exitg1 = true;
    } else {
      if (absxk > anrm) {
        anrm = absxk;
      }
      im1n++;
    }
  }
  if (muDoubleScalarIsInf(anrm) || muDoubleScalarIsNaN(anrm)) {
    V[0].re = rtNaN;
    V[0].im = 0.0;
    V[1].re = rtNaN;
    V[1].im = 0.0;
    V[2].re = rtNaN;
    V[2].im = 0.0;
  } else {
    real_T wi[3];
    real_T work[3];
    real_T cscale;
    real_T ctoc;
    int32_T ilo;
    boolean_T guard1;
    boolean_T scalea;
    cscale = anrm;
    scalea = false;
    guard1 = false;
    if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
      scalea = true;
      cscale = 6.7178761075670888E-139;
      guard1 = true;
    } else if (anrm > 1.4885657073574029E+138) {
      scalea = true;
      cscale = 1.4885657073574029E+138;
      guard1 = true;
    }
    if (guard1) {
      boolean_T notdone;
      absxk = anrm;
      ctoc = cscale;
      notdone = true;
      while (notdone) {
        __m128d r;
        __m128d r1;
        real_T cfrom1;
        real_T cto1;
        real_T mul;
        cfrom1 = absxk * 2.0041683600089728E-292;
        cto1 = ctoc / 4.9896007738368E+291;
        if ((cfrom1 > ctoc) && (ctoc != 0.0)) {
          mul = 2.0041683600089728E-292;
          absxk = cfrom1;
        } else if (cto1 > absxk) {
          mul = 4.9896007738368E+291;
          ctoc = cto1;
        } else {
          mul = ctoc / absxk;
          notdone = false;
        }
        r = _mm_loadu_pd(&a[0]);
        r1 = _mm_set1_pd(mul);
        _mm_storeu_pd(&a[0], _mm_mul_pd(r, r1));
        r = _mm_loadu_pd(&a[2]);
        _mm_storeu_pd(&a[2], _mm_mul_pd(r, r1));
        r = _mm_loadu_pd(&a[4]);
        _mm_storeu_pd(&a[4], _mm_mul_pd(r, r1));
        r = _mm_loadu_pd(&a[6]);
        _mm_storeu_pd(&a[6], _mm_mul_pd(r, r1));
        a[8] *= mul;
      }
    }
    c_st.site = &if_emlrtRSI;
    ilo = xzgebal(&c_st, a, &ihi, work);
    c_st.site = &jf_emlrtRSI;
    if ((ihi - ilo) + 1 > 1) {
      d_st.site = &cg_emlrtRSI;
      if (ilo - 1 > 2147483646) {
        e_st.site = &fb_emlrtRSI;
        check_forloop_overflow_error(&e_st);
      }
      im1n = (uint8_T)(ilo - 1);
      if (im1n - 1 >= 0) {
        memset(&tau[0], 0, (uint32_T)im1n * sizeof(real_T));
      }
      for (b_i = ihi; b_i < 3; b_i++) {
        tau[b_i - 1] = 0.0;
      }
      work[0] = 0.0;
      work[1] = 0.0;
      work[2] = 0.0;
      d_st.site = &dg_emlrtRSI;
      if ((ilo <= ihi - 1) && (ihi - 1 > 2147483646)) {
        e_st.site = &fb_emlrtRSI;
        check_forloop_overflow_error(&e_st);
      }
      for (b_i = ilo; b_i < ihi; b_i++) {
        int32_T alpha1_tmp;
        int32_T in;
        int32_T lastv;
        int32_T n;
        im1n = (b_i - 1) * 3;
        in = b_i * 3 + 1;
        n = ihi - b_i;
        alpha1_tmp = b_i + im1n;
        absxk = a[alpha1_tmp];
        d_st.site = &rd_emlrtRSI;
        ctoc = xzlarfg(&d_st, n, &absxk, a, im1n + 3);
        tau[b_i - 1] = ctoc;
        a[alpha1_tmp] = 1.0;
        d_st.site = &sd_emlrtRSI;
        if (ctoc != 0.0) {
          lastv = n;
          i = (alpha1_tmp + n) + 1;
          while ((lastv > 0) && (a[i - 2] == 0.0)) {
            lastv--;
            i--;
          }
          im1n = ihi;
          exitg1 = false;
          while ((!exitg1) && (im1n > 0)) {
            int32_T exitg2;
            int32_T ia;
            i = (in + im1n) - 1;
            ia = i;
            do {
              exitg2 = 0;
              if (ia <= i + (lastv - 1) * 3) {
                if (a[ia - 1] != 0.0) {
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
          e_st.site = &ud_emlrtRSI;
          xgemv(&e_st, im1n, lastv, a, in, a, alpha1_tmp + 1, work);
          e_st.site = &vd_emlrtRSI;
          xgerc(&e_st, im1n, lastv, -tau[b_i - 1], work, alpha1_tmp + 1, a, in);
        }
        d_st.site = &td_emlrtRSI;
        xzlarf(&d_st, n, 3 - b_i, alpha1_tmp + 1, tau[b_i - 1], a, b_i + in,
               work);
        a[alpha1_tmp] = absxk;
      }
    }
    c_st.site = &kf_emlrtRSI;
    i = xdlahqr(&c_st, ilo, ihi, a, work, wi);
    if (scalea) {
      c_st.site = &lf_emlrtRSI;
      xzlascl(&c_st, cscale, anrm, 3 - i, work, i + 1);
      c_st.site = &mf_emlrtRSI;
      xzlascl(&c_st, cscale, anrm, 3 - i, wi, i + 1);
      if (i != 0) {
        c_st.site = &nf_emlrtRSI;
        b_xzlascl(&c_st, cscale, anrm, ilo - 1, work);
        c_st.site = &of_emlrtRSI;
        b_xzlascl(&c_st, cscale, anrm, ilo - 1, wi);
      }
    }
    if (i != 0) {
      c_st.site = &pf_emlrtRSI;
      if ((ilo <= i) && (i > 2147483646)) {
        d_st.site = &fb_emlrtRSI;
        check_forloop_overflow_error(&d_st);
      }
      for (b_i = ilo; b_i <= i; b_i++) {
        work[b_i - 1] = rtNaN;
        wi[b_i - 1] = 0.0;
      }
    }
    V[0].re = work[0];
    V[0].im = wi[0];
    V[1].re = work[1];
    V[1].im = wi[1];
    V[2].re = work[2];
    V[2].im = wi[2];
  }
  if ((i != 0) && (!emlrtSetWarningFlag((emlrtCTX)sp))) {
    st.site = &gf_emlrtRSI;
    warning(&st);
  }
}
