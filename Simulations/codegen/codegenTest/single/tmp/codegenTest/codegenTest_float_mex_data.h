#pragma once

#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern emlrtLocationLoggingDataType emlrtLocationLoggingDataTables[24];
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;
extern emlrtRSInfo k_emlrtRSI;
extern emlrtRSInfo l_emlrtRSI;
extern emlrtRSInfo db_emlrtRSI;
extern emlrtRSInfo fb_emlrtRSI;
extern emlrtRSInfo pb_emlrtRSI;
extern emlrtRSInfo qb_emlrtRSI;
extern emlrtRSInfo sb_emlrtRSI;
extern emlrtRSInfo oc_emlrtRSI;
extern emlrtRSInfo pc_emlrtRSI;
extern emlrtRSInfo rd_emlrtRSI;
extern emlrtRSInfo sd_emlrtRSI;
extern emlrtRSInfo td_emlrtRSI;
extern emlrtRSInfo ud_emlrtRSI;
extern emlrtRSInfo vd_emlrtRSI;
extern emlrtRSInfo wd_emlrtRSI;
extern emlrtRSInfo yd_emlrtRSI;
extern emlrtRSInfo ae_emlrtRSI;
extern emlrtRSInfo be_emlrtRSI;
extern emlrtRSInfo ce_emlrtRSI;
extern emlrtRSInfo de_emlrtRSI;
extern emlrtRSInfo ee_emlrtRSI;
extern emlrtRSInfo ag_emlrtRSI;
extern emlrtRSInfo bg_emlrtRSI;
extern omp_lock_t emlrtLockGlobal;
extern omp_nest_lock_t codegenTest_float_mex_nestLockGlobal;
extern emlrtRTEInfo f_emlrtRTEI;
extern emlrtRTEInfo g_emlrtRTEI;
extern emlrtRTEInfo h_emlrtRTEI;
extern const int8_T iv[9];
extern covrtInstance emlrtCoverageInstance;
