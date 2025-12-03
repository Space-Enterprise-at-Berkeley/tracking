/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * validateattributes.c
 *
 * Code generation for function 'validateattributes'
 *
 */

/* Include files */
#include "validateattributes.h"
#include "codegenTest_data.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Function Definitions */
void validateattributes(const emlrtStack *sp, const real32_T a[9])
{
  emlrtStack st;
  int32_T k;
  boolean_T exitg1;
  boolean_T p;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &fb_emlrtRSI;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 9)) {
    if ((!muSingleScalarIsInf(a[k])) && (!muSingleScalarIsNaN(a[k]))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    emlrtErrorWithMessageIdR2018a(
        &st, &e_emlrtRTEI, "Coder:toolbox:ValidateattributesexpectedFinite",
        "MATLAB:KalmanFilter:expectedFinite", 3, 4, 5, "State");
  }
}

/* End of code generation (validateattributes.c) */
