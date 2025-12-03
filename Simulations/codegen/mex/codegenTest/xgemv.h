/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgemv.h
 *
 * Code generation for function 'xgemv'
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
void xgemv(const emlrtStack *sp, int32_T m, int32_T n, const real32_T A[9],
           int32_T ia0, const real32_T x[9], int32_T ix0, real32_T y[3]);

/* End of code generation (xgemv.h) */
