#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void b_xzlascl(const emlrtStack *sp, real_T cfrom, real_T cto, int32_T m,
               real_T A[3]);

void xzlascl(const emlrtStack *sp, real_T cfrom, real_T cto, int32_T m,
             real_T A[3], int32_T iA0);
