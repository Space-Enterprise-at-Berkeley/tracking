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

void trackingKF_correct(const emlrtStack *sp, trackingKF *KF,
                        const real_T z[3]);

void trackingKF_predict(const emlrtStack *sp, trackingKF *KF,
                        real_T varargin_1);
