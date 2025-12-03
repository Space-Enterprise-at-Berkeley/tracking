/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlarf.h
 *
 * Code generation for function 'xzlarf'
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
void xzlarf(const emlrtStack *sp, int32_T m, int32_T n, int32_T iv0,
            real32_T tau, real32_T C[9], int32_T ic0, real32_T work[3]);

/* End of code generation (xzlarf.h) */
