#include "codegenTest_float_mex_initialize.h"
#include "_coder_codegenTest_float_mex_mex.h"
#include "codegenTest_float_mex_data.h"
#include "rt_nonfinite.h"

static void codegenTest_float_mex_once(void);

static void codegenTest_float_mex_once(void)
{
  mex_InitInfAndNan();

  covrtAllocateInstanceData(&emlrtCoverageInstance);

  covrtScriptInit(
      &emlrtCoverageInstance,
      "C:\\Users\\lenowo "
      "twinkpad\\Documents\\SEB\\tracking\\Simulations\\codegenTest.m",
      0U, 1U, 1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U);

  covrtFcnInit(&emlrtCoverageInstance, 0U, 0U, "codegenTest", 0, -1, 295);

  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 0U, 98, -1, 291);

  covrtScriptStart(&emlrtCoverageInstance, 0U);

  covrtAllocateInstanceData(&emlrtCoverageInstance);

  covrtScriptInit(
      &emlrtCoverageInstance,
      "C:\\Users\\lenowo "
      "twinkpad\\Documents\\SEB\\tracking\\Simulations\\CombinedTracker.m",
      1U, 4U, 4U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U);

  covrtFcnInit(&emlrtCoverageInstance, 1U, 0U,
               "CombinedTracker_CombinedTracker", 361, -1, 555);
  covrtFcnInit(&emlrtCoverageInstance, 1U, 1U, "CombinedTracker_extrapolate",
               564, -1, 1204);
  covrtFcnInit(&emlrtCoverageInstance, 1U, 2U, "CombinedTracker_GPSUpdate",
               1213, -1, 1540);
  covrtFcnInit(&emlrtCoverageInstance, 1U, 3U, "CombinedTracker_accelUpdate",
               1549, -1, 1882);

  covrtBasicBlockInit(&emlrtCoverageInstance, 1U, 0U, 27, -1, 543);
  covrtBasicBlockInit(&emlrtCoverageInstance, 1U, 1U, 616, -1, 1192);
  covrtBasicBlockInit(&emlrtCoverageInstance, 1U, 2U, 1268, -1, 1528);
  covrtBasicBlockInit(&emlrtCoverageInstance, 1U, 3U, 1606, -1, 1870);

  covrtScriptStart(&emlrtCoverageInstance, 1U);
}

void codegenTest_float_mex_initialize(void)
{
  emlrtStack st = {NULL, NULL, NULL};
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    codegenTest_float_mex_once();
  }
}
