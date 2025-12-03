/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_codegenTest_api.c
 *
 * Code generation for function '_coder_codegenTest_api'
 *
 */

/* Include files */
#include "_coder_codegenTest_api.h"
#include "codegenTest.h"
#include "codegenTest_data.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                               const char_T *identifier, real32_T y[3]);

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real32_T y[3]);

static real32_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                   const char_T *identifier);

static const mxArray *emlrt_marshallOut(const real32_T u[9]);

static real32_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId);

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               real32_T ret[3]);

static real32_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId);

/* Function Definitions */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                               const char_T *identifier, real32_T y[3])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(nullptr), &thisId, y);
  emlrtDestroyArray(&nullptr);
}

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real32_T y[3])
{
  h_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real32_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                   const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real32_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(nullptr), &thisId);
  emlrtDestroyArray(&nullptr);
  return y;
}

static const mxArray *emlrt_marshallOut(const real32_T u[9])
{
  static const int32_T i = 9;
  const mxArray *m;
  const mxArray *y;
  int32_T b_i;
  real32_T *pData;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)emlrtMxGetData(m);
  for (b_i = 0; b_i < 9; b_i++) {
    pData[b_i] = u[b_i];
  }
  emlrtAssign(&y, m);
  return y;
}

static real32_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real32_T ret[3])
{
  static const int32_T dims[2] = {1, 3};
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "single|double", false,
                          2U, (const void *)&dims[0]);
  emlrtImportArrayR2015b((emlrtConstCTX)sp, src, &ret[0], 4, false);
  emlrtDestroyArray(&src);
}

static real32_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real32_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "single|double", false,
                          0U, (const void *)&dims);
  emlrtImportArrayR2015b((emlrtConstCTX)sp, src, &ret, 4, false);
  emlrtDestroyArray(&src);
  return ret;
}

void codegenTest_api(const mxArray *const prhs[5], const mxArray **plhs)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  real32_T state[9];
  real32_T testAccel[3];
  real32_T testGPS[3];
  real32_T testAcceltime;
  real32_T testExtrapolate;
  real32_T testGPStime;
  st.tls = emlrtRootTLSGlobal;
  /* Marshall function inputs */
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "testGPS", testGPS);
  testGPStime = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "testGPStime");
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "testAccel", testAccel);
  testAcceltime =
      e_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "testAcceltime");
  testExtrapolate =
      e_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "testExtrapolate");
  /* Invoke the target function */
  codegenTest(&st, testGPS, testGPStime, testAccel, testAcceltime,
              testExtrapolate, state);
  /* Marshall function outputs */
  *plhs = emlrt_marshallOut(state);
}

/* End of code generation (_coder_codegenTest_api.c) */
