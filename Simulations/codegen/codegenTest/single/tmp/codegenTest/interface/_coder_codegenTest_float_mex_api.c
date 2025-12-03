#include "_coder_codegenTest_float_mex_api.h"
#include "codegenTest.h"
#include "codegenTest_float_mex_data.h"
#include "forcePushIntoCloud.h"
#include "rt_nonfinite.h"

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                   const char_T *identifier))[3];

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3];

static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                 const char_T *identifier);

static const mxArray *emlrt_marshallOut(real_T u[9]);

static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3];

static real_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                   const char_T *identifier))[3]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[3];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(nullptr), &thisId);
  emlrtDestroyArray(&nullptr);
  return y;
}

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3]
{
  real_T(*y)[3];
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                 const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(nullptr), &thisId);
  emlrtDestroyArray(&nullptr);
  return y;
}

static const mxArray *emlrt_marshallOut(real_T u[9])
{
  static const int32_T i = 0;
  static const int32_T i1 = 9;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3]
{
  static const int32_T dims[2] = {1, 3};
  real_T(*ret)[3];
  int32_T b_iv[2];
  boolean_T bv[2] = {false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 2U,
                            (const void *)&dims[0], &bv[0], &b_iv[0]);
  ret = (real_T(*)[3])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void codegenTest_api(const mxArray *const prhs[5], const mxArray **plhs)
{
  emlrtStack st = {NULL, NULL, NULL};
  real_T(*state)[9];
  real_T(*testAccel)[3];
  real_T(*testGPS)[3];
  real_T testAcceltime;
  real_T testExtrapolate;
  real_T testGPStime;
  st.tls = emlrtRootTLSGlobal;
  state = (real_T(*)[9])mxMalloc(sizeof(real_T[9]));

  testGPS = c_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "testGPS");
  testGPStime = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "testGPStime");
  testAccel = c_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "testAccel");
  testAcceltime =
      e_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "testAcceltime");
  testExtrapolate =
      e_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "testExtrapolate");

  codegenTest(&st, *testGPS, testGPStime, *testAccel, testAcceltime,
              testExtrapolate, *state);

  *plhs = emlrt_marshallOut(*state);
}

void forcePushIntoCloud_api(void)
{
  emlrtStack st = {NULL, NULL, NULL};
  st.tls = emlrtRootTLSGlobal;

  forcePushIntoCloud(&st);
}
