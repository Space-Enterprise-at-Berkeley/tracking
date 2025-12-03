#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void codegenTest_float_mex_atexit(void);

void codegenTest_float_mex_terminate(void);

void emlrtLocationLoggingAccessor(void **info, size_t *size);

int32_T emlrtLocationLoggingGetVersion(void);
