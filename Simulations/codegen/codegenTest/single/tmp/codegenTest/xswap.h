#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void xswap(const emlrtStack *sp, int32_T n, real_T x[9], int32_T ix0,
           int32_T iy0);
