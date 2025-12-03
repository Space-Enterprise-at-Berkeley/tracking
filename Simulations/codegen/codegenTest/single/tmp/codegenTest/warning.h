#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void b_warning(const emlrtStack *sp);

void c_warning(const emlrtStack *sp);

void d_warning(const emlrtStack *sp, int32_T varargin_1,
               const char_T varargin_2[14]);

void warning(const emlrtStack *sp);
