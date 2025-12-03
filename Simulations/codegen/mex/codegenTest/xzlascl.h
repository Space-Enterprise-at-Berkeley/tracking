/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlascl.h
 *
 * Code generation for function 'xzlascl'
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
void b_xzlascl(const emlrtStack *sp, real32_T cfrom, real32_T cto, int32_T m,
               real32_T A[3]);

void xzlascl(const emlrtStack *sp, real32_T cfrom, real32_T cto, int32_T m,
             real32_T A[3], int32_T iA0);

/* End of code generation (xzlascl.h) */
