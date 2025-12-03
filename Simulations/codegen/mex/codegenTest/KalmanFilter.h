/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * KalmanFilter.h
 *
 * Code generation for function 'KalmanFilter'
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
void binary_expand_op(trackingKF *in1, const real32_T in2_data[],
                      const real32_T in3[3], const real32_T in4_data[],
                      const int32_T *in4_size);

void c_KalmanFilter_set_MeasurementM(const emlrtStack *sp, trackingKF *obj,
                                     const real32_T MeasurementModelMatrix[27]);

void plus(real32_T in1_data[], int32_T in1_size[2], const real32_T in2_data[],
          const int32_T in2_size[2]);

/* End of code generation (KalmanFilter.h) */
