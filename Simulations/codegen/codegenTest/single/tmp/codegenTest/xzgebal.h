#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_T xzgebal(const emlrtStack *sp, real_T A[9], int32_T *ihi,
                real_T scale[3]);
