#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mrdiv(const emlrtStack *sp, real_T A_data[], int32_T A_size[2],
           const real_T B_data[], const int32_T B_size[2]);
