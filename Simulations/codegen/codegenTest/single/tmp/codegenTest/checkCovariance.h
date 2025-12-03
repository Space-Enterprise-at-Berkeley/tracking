#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkCovariance(const emlrtStack *sp, const real_T b_value[9],
                     const real_T dims[2]);
