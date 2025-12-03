/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * trackingKF.h
 *
 * Code generation for function 'trackingKF'
 *
 */

#pragma once

/* Include files */
#include "codegenTest_internal_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void trackingKF_correct(const emlrtStack *sp, trackingKF *KF,
                        const real32_T z[3]);

void trackingKF_predict(const emlrtStack *sp, trackingKF *KF,
                        real32_T varargin_1);

/* End of code generation (trackingKF.h) */
