#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_T xdlahqr(const emlrtStack *sp, int32_T ilo, int32_T ihi, real_T h[9],
                real_T wr[3], real_T wi[3]);
