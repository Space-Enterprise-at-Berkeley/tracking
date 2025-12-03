#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void codegenTest(const emlrtStack *sp, const real_T testGPS[3],
                 real_T testGPStime, const real_T testAccel[3],
                 real_T testAcceltime, real_T testExtrapolate, real_T state[9]);

emlrtCTX emlrtGetRootTLSGlobal(void);

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, emlrtConstCTX aTLS,
                         void *aData);
