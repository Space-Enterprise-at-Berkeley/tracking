/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * qrsolve.h
 *
 * Code generation for function 'qrsolve'
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
void qrsolve(const emlrtStack *sp, const real32_T A_data[],
             const int32_T A_size[2], const real32_T B_data[],
             const int32_T B_size[2], real32_T Y_data[], int32_T Y_size[2]);

/* End of code generation (qrsolve.h) */
