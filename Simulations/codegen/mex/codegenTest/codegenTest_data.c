/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * codegenTest_data.c
 *
 * Code generation for function 'codegenTest_data'
 *
 */

/* Include files */
#include "codegenTest_data.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131675U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "codegenTest",                                        /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

emlrtRSInfo k_emlrtRSI = {
    44,       /* lineNo */
    "mpower", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\mpower.m" /* pathName
                                                                          */
};

emlrtRSInfo l_emlrtRSI =
    {
        71,      /* lineNo */
        "power", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\ops\\power.m" /* pathName
                                                                          */
};

emlrtRSInfo eb_emlrtRSI = {
    6,                        /* lineNo */
    "validateDataAttributes", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\validateDataAttr"
    "ibutes.m" /* pathName */
};

emlrtRSInfo fb_emlrtRSI = {
    93,                   /* lineNo */
    "validateattributes", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\lang\\validateattributes"
    ".m" /* pathName */
};

emlrtRSInfo gb_emlrtRSI = {
    461,                                     /* lineNo */
    "KalmanFilter/set.StateTransitionModel", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

emlrtRSInfo kb_emlrtRSI = {
    20,                               /* lineNo */
    "eml_int_forloop_overflow_check", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\eml\\eml_int_forloop_"
    "overflow_check.m" /* pathName */
};

emlrtRSInfo ub_emlrtRSI = {
    31,      /* lineNo */
    "xscal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+blas\\xscal."
    "m" /* pathName */
};

emlrtRSInfo vb_emlrtRSI = {
    18,      /* lineNo */
    "xscal", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "refblas\\xscal.m" /* pathName */
};

emlrtRSInfo xb_emlrtRSI = {
    467,                                 /* lineNo */
    "KalmanFilter/set.MeasurementModel", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m" /* pathName */
};

emlrtRSInfo wd_emlrtRSI = {
    46,        /* lineNo */
    "xzgehrd", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgehrd.m" /* pathName */
};

emlrtRSInfo xd_emlrtRSI = {
    50,        /* lineNo */
    "xzgehrd", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgehrd.m" /* pathName */
};

emlrtRSInfo yd_emlrtRSI = {
    58,        /* lineNo */
    "xzgehrd", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzgehrd.m" /* pathName */
};

emlrtRSInfo ae_emlrtRSI = {
    84,       /* lineNo */
    "xzlarf", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzlarf.m" /* pathName */
};

emlrtRSInfo be_emlrtRSI = {
    91,       /* lineNo */
    "xzlarf", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "reflapack\\xzlarf.m" /* pathName */
};

emlrtRSInfo ce_emlrtRSI = {
    86,      /* lineNo */
    "xgemv", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+blas\\xgemv."
    "m" /* pathName */
};

emlrtRSInfo ee_emlrtRSI = {
    37,      /* lineNo */
    "xgemv", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "refblas\\xgemv.m" /* pathName */
};

emlrtRSInfo fe_emlrtRSI = {
    45,      /* lineNo */
    "xgerc", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+blas\\xgerc."
    "m" /* pathName */
};

emlrtRSInfo ge_emlrtRSI =
    {
        45,     /* lineNo */
        "xger", /* fcnName */
        "C:\\Program "
        "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
        "blas\\xger.m" /* pathName */
};

emlrtRSInfo he_emlrtRSI = {
    15,     /* lineNo */
    "xger", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "refblas\\xger.m" /* pathName */
};

emlrtRSInfo ie_emlrtRSI = {
    41,      /* lineNo */
    "xgerx", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "refblas\\xgerx.m" /* pathName */
};

emlrtRSInfo je_emlrtRSI = {
    54,      /* lineNo */
    "xgerx", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "refblas\\xgerx.m" /* pathName */
};

emlrtRSInfo fg_emlrtRSI = {
    30,      /* lineNo */
    "xswap", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+blas\\xswap."
    "m" /* pathName */
};

emlrtRSInfo gg_emlrtRSI = {
    20,      /* lineNo */
    "xswap", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "refblas\\xswap.m" /* pathName */
};

omp_lock_t emlrtLockGlobal;

omp_nest_lock_t codegenTest_nestLockGlobal;

emlrtRTEInfo e_emlrtRTEI = {
    14,               /* lineNo */
    37,               /* colNo */
    "validatefinite", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "valattr\\validatefinite.m" /* pName */
};

emlrtRTEInfo h_emlrtRTEI = {
    48,          /* lineNo */
    13,          /* colNo */
    "infocheck", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\infocheck.m" /* pName */
};

emlrtRTEInfo i_emlrtRTEI = {
    45,          /* lineNo */
    13,          /* colNo */
    "infocheck", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+internal\\+"
    "lapack\\infocheck.m" /* pName */
};

const int8_T iv[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

/* End of code generation (codegenTest_data.c) */
