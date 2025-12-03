/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xnrm2.h
 *
 * Code generation for function 'xnrm2'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
real32_T b_xnrm2(int32_T n, const real32_T x[3]);

real32_T xnrm2(const emlrtStack *sp, int32_T n, const real32_T x[9],
               int32_T ix0);

/* End of code generation (xnrm2.h) */
