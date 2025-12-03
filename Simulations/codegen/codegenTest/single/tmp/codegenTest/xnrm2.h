#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

real_T b_xnrm2(int32_T n, const real_T x[3]);

real_T xnrm2(const emlrtStack *sp, int32_T n, const real_T x[9], int32_T ix0);
