#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

real_T b_xzlarfg(int32_T n, real_T *alpha1, real_T x[3]);

real_T xzlarfg(const emlrtStack *sp, int32_T n, real_T *alpha1, real_T x[9],
               int32_T ix0);
