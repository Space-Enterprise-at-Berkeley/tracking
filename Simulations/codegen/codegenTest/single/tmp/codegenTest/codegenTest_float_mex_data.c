#include "codegenTest_float_mex_data.h"
#include "rt_nonfinite.h"

emlrtLocationLoggingDataType emlrtLocationLoggingDataTables[24];

emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,
    false,
    131675U,
    NULL,
    "codegenTest_float_mex",
    NULL,
    false,
    {2045744189U, 2170104910U, 2743257031U, 4284093946U},
    NULL};

emlrtRSInfo k_emlrtRSI = {
    44, "mpower",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\matfun\\mpower.m"};

emlrtRSInfo l_emlrtRSI = {
    71, "power",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\ops\\power.m"};

emlrtRSInfo db_emlrtRSI = {
    461, "KalmanFilter/set.StateTransitionModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

emlrtRSInfo fb_emlrtRSI = {20, "eml_int_forloop_overflow_check",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\e"
                           "ml\\eml_int_forloop_overflow_check.m"};

emlrtRSInfo pb_emlrtRSI = {31, "xscal",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+blas\\xscal.m"};

emlrtRSInfo qb_emlrtRSI = {18, "xscal",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+refblas\\xscal.m"};

emlrtRSInfo sb_emlrtRSI = {
    467, "KalmanFilter/set.MeasurementModel",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\KalmanFilter.m"};

emlrtRSInfo oc_emlrtRSI = {
    6, "validateDataAttributes",
    "C:\\Program "
    "Files\\MATLAB\\R2025b\\toolbox\\shared\\tracking\\trackinglib\\+"
    "matlabshared\\+tracking\\+internal\\validateDataAttr"
    "ibutes.m"};

emlrtRSInfo pc_emlrtRSI = {93, "validateattributes",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\lib\\matlab\\l"
                           "ang\\validateattributes.m"};

emlrtRSInfo rd_emlrtRSI = {46, "xzgehrd",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+reflapack\\xzgehrd.m"};

emlrtRSInfo sd_emlrtRSI = {50, "xzgehrd",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+reflapack\\xzgehrd.m"};

emlrtRSInfo td_emlrtRSI = {58, "xzgehrd",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+reflapack\\xzgehrd.m"};

emlrtRSInfo ud_emlrtRSI = {84, "xzlarf",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+reflapack\\xzlarf.m"};

emlrtRSInfo vd_emlrtRSI = {91, "xzlarf",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+reflapack\\xzlarf.m"};

emlrtRSInfo wd_emlrtRSI = {86, "xgemv",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+blas\\xgemv.m"};

emlrtRSInfo yd_emlrtRSI = {37, "xgemv",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+refblas\\xgemv.m"};

emlrtRSInfo ae_emlrtRSI = {45, "xgerc",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+blas\\xgerc.m"};

emlrtRSInfo be_emlrtRSI = {45, "xger",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+blas\\xger.m"};

emlrtRSInfo ce_emlrtRSI = {15, "xger",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+refblas\\xger.m"};

emlrtRSInfo de_emlrtRSI = {41, "xgerx",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+refblas\\xgerx.m"};

emlrtRSInfo ee_emlrtRSI = {54, "xgerx",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+refblas\\xgerx.m"};

emlrtRSInfo ag_emlrtRSI = {30, "xswap",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+blas\\xswap.m"};

emlrtRSInfo bg_emlrtRSI = {20, "xswap",
                           "C:\\Program "
                           "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+coder\\+"
                           "internal\\+refblas\\xswap.m"};

omp_lock_t emlrtLockGlobal;

omp_nest_lock_t codegenTest_float_mex_nestLockGlobal;

emlrtRTEInfo f_emlrtRTEI = {14, 37, "validatefinite",
                            "C:\\Program "
                            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                            "coder\\+internal\\+valattr\\validatefinite.m"};

emlrtRTEInfo g_emlrtRTEI = {48, 13, "infocheck",
                            "C:\\Program "
                            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                            "coder\\+internal\\+lapack\\infocheck.m"};

emlrtRTEInfo h_emlrtRTEI = {45, 13, "infocheck",
                            "C:\\Program "
                            "Files\\MATLAB\\R2025b\\toolbox\\eml\\eml\\+"
                            "coder\\+internal\\+lapack\\infocheck.m"};

const int8_T iv[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

covrtInstance emlrtCoverageInstance;
