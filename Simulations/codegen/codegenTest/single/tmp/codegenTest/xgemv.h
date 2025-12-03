#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void xgemv(const emlrtStack *sp, int32_T m, int32_T n, const real_T A[9],
           int32_T ia0, const real_T x[9], int32_T ix0, real_T y[3]);
