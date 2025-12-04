//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_codegenTest_api.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 20:32:31
//

// Include Files
#include "_coder_codegenTest_api.h"
#include "_coder_codegenTest_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131675U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "codegenTest",                                        // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static real32_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId);

static void b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                               const char_T *identifier, real32_T y[9]);

static void b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real32_T y[9]);

static void c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real32_T ret[3]);

static void d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real32_T ret[9]);

static void emlrtExitTimeCleanupDtorFcn(const void *r);

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                             const char_T *identifier, real32_T y[3]);

static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, real32_T y[3]);

static real32_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                                 const char_T *identifier);

static real32_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static const mxArray *emlrt_marshallOut(const real32_T u[9]);

// Function Definitions
//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real32_T
//
static real32_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real32_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "single|double",
                          false, 0U, (const void *)&dims);
  emlrtImportArrayR2015b((emlrtConstCTX)&sp, src, &ret, 4, false);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *b_nullptr
//                const char_T *identifier
//                real32_T y[9]
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                               const char_T *identifier, real32_T y[9])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId, y);
  emlrtDestroyArray(&b_nullptr);
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                real32_T y[9]
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real32_T y[9])
{
  d_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                real32_T ret[3]
// Return Type  : void
//
static void c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real32_T ret[3])
{
  static const int32_T dims[2]{1, 3};
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "single|double",
                          false, 2U, (const void *)&dims[0]);
  emlrtImportArrayR2015b((emlrtConstCTX)&sp, src, &ret[0], 4, false);
  emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                real32_T ret[9]
// Return Type  : void
//
static void d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real32_T ret[9])
{
  static const int32_T dims[2]{3, 3};
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "single|double",
                          false, 2U, (const void *)&dims[0]);
  emlrtImportArrayR2015b((emlrtConstCTX)&sp, src, &ret[0], 4, false);
  emlrtDestroyArray(&src);
}

//
// Arguments    : const void *r
// Return Type  : void
//
static void emlrtExitTimeCleanupDtorFcn(const void *r)
{
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *b_nullptr
//                const char_T *identifier
//                real32_T y[3]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                             const char_T *identifier, real32_T y[3])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId, y);
  emlrtDestroyArray(&b_nullptr);
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                real32_T y[3]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, real32_T y[3])
{
  c_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *b_nullptr
//                const char_T *identifier
// Return Type  : real32_T
//
static real32_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *b_nullptr,
                                 const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real32_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId);
  emlrtDestroyArray(&b_nullptr);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real32_T
//
static real32_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = b_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const real32_T u[9]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real32_T u[9])
{
  static const int32_T i{9};
  const mxArray *m;
  const mxArray *y;
  real32_T *pData;
  y = nullptr;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxSINGLE_CLASS, mxREAL);
  pData = static_cast<real32_T *>(emlrtMxGetData(m));
  for (int32_T b_i{0}; b_i < 9; b_i++) {
    pData[b_i] = u[b_i];
  }
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const mxArray * const prhs[8]
//                const mxArray **plhs
// Return Type  : void
//
void codegenTest_api(const mxArray *const prhs[8], const mxArray **plhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real32_T state[9];
  real32_T testGPSNoise[9];
  real32_T testProcessNoise[9];
  real32_T testGPS[3];
  real32_T testAccel;
  real32_T testAccelNoise;
  real32_T testAcceltime;
  real32_T testExtrapolate;
  real32_T testGPStime;
  st.tls = emlrtRootTLSGlobal;
  // Marshall function inputs
  emlrt_marshallIn(st, emlrtAliasP(prhs[0]), "testGPS", testGPS);
  testGPStime = emlrt_marshallIn(st, emlrtAliasP(prhs[1]), "testGPStime");
  testAccel = emlrt_marshallIn(st, emlrtAliasP(prhs[2]), "testAccel");
  testAcceltime = emlrt_marshallIn(st, emlrtAliasP(prhs[3]), "testAcceltime");
  testExtrapolate =
      emlrt_marshallIn(st, emlrtAliasP(prhs[4]), "testExtrapolate");
  b_emlrt_marshallIn(st, emlrtAliasP(prhs[5]), "testProcessNoise",
                     testProcessNoise);
  b_emlrt_marshallIn(st, emlrtAliasP(prhs[6]), "testGPSNoise", testGPSNoise);
  testAccelNoise = emlrt_marshallIn(st, emlrtAliasP(prhs[7]), "testAccelNoise");
  // Invoke the target function
  codegenTest(testGPS, testGPStime, testAccel, testAcceltime, testExtrapolate,
              testProcessNoise, testGPSNoise, testAccelNoise, state);
  // Marshall function outputs
  *plhs = emlrt_marshallOut(state);
}

//
// Arguments    : void
// Return Type  : void
//
void codegenTest_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtPushHeapReferenceStackR2021a(&st, false, nullptr,
                                    (void *)&emlrtExitTimeCleanupDtorFcn,
                                    nullptr, nullptr, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  codegenTest_xil_terminate();
  codegenTest_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void codegenTest_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void codegenTest_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_codegenTest_api.cpp
//
// [EOF]
//
