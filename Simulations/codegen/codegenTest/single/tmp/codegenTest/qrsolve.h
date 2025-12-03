#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void qrsolve(const emlrtStack *sp, const real_T A_data[],
             const int32_T A_size[2], const real_T B_data[],
             const int32_T B_size[2], real_T Y_data[], int32_T Y_size[2]);
