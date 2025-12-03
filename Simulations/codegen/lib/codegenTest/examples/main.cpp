//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 02-Dec-2025 17:03:31
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "codegenTest.h"
#include "codegenTest_initialize.h"
#include "codegenTest_terminate.h"
#include "rt_nonfinite.h"

// Function Declarations
static void argInit_1x3_real32_T(float result[3]);

static void argInit_3x3_real32_T(float result[9]);

static float argInit_real32_T();

// Function Definitions
//
// Arguments    : float result[3]
// Return Type  : void
//
static void argInit_1x3_real32_T(float result[3])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 3; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real32_T();
  }
}

//
// Arguments    : float result[9]
// Return Type  : void
//
static void argInit_3x3_real32_T(float result[9])
{
  // Loop over the array to initialize each element.
  for (int i{0}; i < 9; i++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[i] = argInit_real32_T();
  }
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  // Initialize the application.
  // You do not need to do this more than one time.
  codegenTest_initialize();
  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_codegenTest();
  // Terminate the application.
  // You do not need to do this more than one time.
  codegenTest_terminate();
  return 0;
}

//
// Arguments    : void
// Return Type  : void
//
void main_codegenTest()
{
  float state[9];
  float testProcessNoise_tmp[9];
  float testGPS_tmp[3];
  float testGPStime_tmp;
  // Initialize function 'codegenTest' input arguments.
  // Initialize function input argument 'testGPS'.
  argInit_1x3_real32_T(testGPS_tmp);
  testGPStime_tmp = argInit_real32_T();
  // Initialize function input argument 'testAccel'.
  // Initialize function input argument 'testProcessNoise'.
  argInit_3x3_real32_T(testProcessNoise_tmp);
  // Initialize function input argument 'testGPSNoise'.
  // Initialize function input argument 'testAccelNoise'.
  // Call the entry-point 'codegenTest'.
  codegenTest(testGPS_tmp, testGPStime_tmp, testGPS_tmp, testGPStime_tmp,
              testGPStime_tmp, testProcessNoise_tmp, testProcessNoise_tmp,
              testProcessNoise_tmp, state);
}

//
// File trailer for main.cpp
//
// [EOF]
//
