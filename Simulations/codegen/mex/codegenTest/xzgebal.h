/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzgebal.h
 *
 * Code generation for function 'xzgebal'
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
int32_T xzgebal(const emlrtStack *sp, real32_T A[9], int32_T *ihi,
                real32_T scale[3]);

/* End of code generation (xzgebal.h) */
