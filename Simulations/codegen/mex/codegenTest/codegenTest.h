/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * codegenTest.h
 *
 * Code generation for function 'codegenTest'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void codegenTest(const emlrtStack *sp, const real32_T testGPS[3],
                 real32_T testGPStime, const real32_T testAccel[3],
                 real32_T testAcceltime, real32_T testExtrapolate,
                 real32_T state[9]);

emlrtCTX emlrtGetRootTLSGlobal(void);

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, emlrtConstCTX aTLS,
                         void *aData);

/* End of code generation (codegenTest.h) */
