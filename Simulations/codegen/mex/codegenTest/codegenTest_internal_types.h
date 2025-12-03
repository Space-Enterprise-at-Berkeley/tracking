/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * codegenTest_internal_types.h
 *
 * Code generation for function 'codegenTest'
 *
 */

#pragma once

/* Include files */
#include "codegenTest_types.h"
#include "rtwtypes.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef typedef_trackingKF
#define typedef_trackingKF
typedef struct {
  real32_T StateTransitionModel[81];
  real32_T ProcessNoiseModel[27];
  real32_T pN;
  real32_T pV;
  real32_T pState[9];
  real32_T pStateCovariance[81];
  real32_T pProcessNoise[9];
  real32_T pMeasurementModel[27];
  real32_T pMeasurementNoise[9];
  boolean_T pIsDistributionsSetup;
  boolean_T pIsInitialized;
  boolean_T IsLastJacobianInitialized;
  boolean_T pIsSmootherStateSizeInitialized;
  boolean_T pIsStateTransitionLocked;
} trackingKF;
#endif /* typedef_trackingKF */

#ifndef typedef_rtDesignRangeCheckInfo
#define typedef_rtDesignRangeCheckInfo
typedef struct {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
} rtDesignRangeCheckInfo;
#endif /* typedef_rtDesignRangeCheckInfo */

#ifndef typedef_rtRunTimeErrorInfo
#define typedef_rtRunTimeErrorInfo
typedef struct {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
} rtRunTimeErrorInfo;
#endif /* typedef_rtRunTimeErrorInfo */

/* End of code generation (codegenTest_internal_types.h) */
