#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void xgerc(const emlrtStack *sp, int32_T m, int32_T n, real_T alpha1,
           const real_T x[3], int32_T iy0, real_T A[9], int32_T ia0);
