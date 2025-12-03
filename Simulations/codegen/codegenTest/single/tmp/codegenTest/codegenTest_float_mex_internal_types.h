#pragma once

#include "codegenTest_float_mex_types.h"
#include "rtwtypes.h"
#include "emlrt.h"

#ifndef typedef_trackingKF
#define typedef_trackingKF
typedef struct {
  real_T StateTransitionModel[81];
  real_T ProcessNoiseModel[27];
  real_T pN;
  real_T pV;
  real_T pState[9];
  real_T pStateCovariance[81];
  real_T pProcessNoise[9];
  real_T pMeasurementModel[27];
  real_T pMeasurementNoise[9];
  boolean_T pIsDistributionsSetup;
  boolean_T pIsInitialized;
  boolean_T IsLastJacobianInitialized;
  boolean_T pIsSmootherStateSizeInitialized;
  boolean_T pIsStateTransitionLocked;
} trackingKF;
#endif

#ifndef typedef_rtDesignRangeCheckInfo
#define typedef_rtDesignRangeCheckInfo
typedef struct {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
} rtDesignRangeCheckInfo;
#endif

#ifndef typedef_rtRunTimeErrorInfo
#define typedef_rtRunTimeErrorInfo
typedef struct {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
} rtRunTimeErrorInfo;
#endif
