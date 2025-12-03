#include "_coder_codegenTest_float_mex_mex.h"
#include "_coder_codegenTest_float_mex_api.h"
#include "codegenTest.h"
#include "codegenTest_float_mex_data.h"
#include "codegenTest_float_mex_initialize.h"
#include "codegenTest_float_mex_terminate.h"
#include "rt_nonfinite.h"
#include "omp.h"

void codegenTest_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                             const mxArray *prhs[5])
{
  emlrtStack st = {NULL, NULL, NULL};
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;

  if (nrhs != 5) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 5, 4,
                        11, "codegenTest");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 11,
                        "codegenTest");
  }

  codegenTest_api(prhs, &outputs);

  emlrtReturnArrays(1, &plhs[0], &outputs);
}

void forcePushIntoCloud_mexFunction(int32_T nlhs, int32_T nrhs)
{
  emlrtStack st = {NULL, NULL, NULL};
  st.tls = emlrtRootTLSGlobal;

  if (nrhs != 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4,
                        18, "forcePushIntoCloud");
  }
  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 18,
                        "forcePushIntoCloud");
  }

  forcePushIntoCloud_api();
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  static jmp_buf emlrtJBEnviron;
  emlrtStack st = {NULL, NULL, NULL};
  const char_T *entryPointTemplateNames[2] = {"codegenTest",
                                              "forcePushIntoCloud"};
  mexAtExit(&codegenTest_float_mex_atexit);
  emlrtLoadLibrary("C:\\ProgramData\\MATLAB\\SupportPackages\\R2025b\\3P."
                   "instrset\\mingw_w64.instrset\\bin\\libgomp-1.dll");

  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&codegenTest_float_mex_nestLockGlobal);
  codegenTest_float_mex_initialize();
  st.tls = emlrtRootTLSGlobal;
  emlrtSetJmpBuf(&st, &emlrtJBEnviron);
  if (setjmp(emlrtJBEnviron) == 0) {
    switch (emlrtGetEntryPointIndexR2016a(
        &st, nrhs, &prhs[0], (const char_T **)&entryPointTemplateNames[0], 2)) {
    case 0:
      codegenTest_mexFunction(nlhs, plhs, nrhs - 1, &prhs[1]);
      break;
    case 1:
      forcePushIntoCloud_mexFunction(nlhs, nrhs - 1);
      break;
    }
    codegenTest_float_mex_terminate();
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&codegenTest_float_mex_nestLockGlobal);
  } else {
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&codegenTest_float_mex_nestLockGlobal);
    emlrtReportParallelRunTimeError(&st);
  }
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal,
                           &emlrtLockerFunction, omp_get_num_procs(), NULL,
                           "windows-1252", true);
  return emlrtRootTLSGlobal;
}
