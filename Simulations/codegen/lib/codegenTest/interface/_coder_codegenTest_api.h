//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_codegenTest_api.h
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

#ifndef _CODER_CODEGENTEST_API_H
#define _CODER_CODEGENTEST_API_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void codegenTest(real_T testGPS[3], real_T testGPStime, real_T testAccel[3],
                 real_T testAcceltime, real_T testExtrapolate, real_T state[9]);

void codegenTest_api(const mxArray *const prhs[5], const mxArray **plhs);

void codegenTest_atexit();

void codegenTest_initialize();

void codegenTest_terminate();

void codegenTest_xil_shutdown();

void codegenTest_xil_terminate();

#endif
//
// File trailer for _coder_codegenTest_api.h
//
// [EOF]
//
