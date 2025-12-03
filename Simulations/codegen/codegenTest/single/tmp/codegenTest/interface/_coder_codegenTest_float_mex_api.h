#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void codegenTest_api(const mxArray *const prhs[5], const mxArray **plhs);

void forcePushIntoCloud_api(void);
