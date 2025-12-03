#pragma once

#include "codegenTest_float_mex_internal_types.h"
#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void binary_expand_op(trackingKF *in1, const real_T in2_data[],
                      const real_T in3[3], const real_T in4_data[],
                      const int32_T *in4_size);

void c_KalmanFilter_set_MeasurementM(const emlrtStack *sp, trackingKF *obj,
                                     const real_T MeasurementModelMatrix[27]);

void plus(real_T in1_data[], int32_T in1_size[2], const real_T in2_data[],
          const int32_T in2_size[2]);
