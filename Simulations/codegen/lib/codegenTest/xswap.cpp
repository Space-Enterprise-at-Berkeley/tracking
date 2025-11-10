//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xswap.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xswap.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : int n
//                double x_data[]
//                int ix0
//                int iy0
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void xswap(int n, double x_data[], int ix0, int iy0)
{
  int i;
  i = static_cast<unsigned char>(n);
  for (int k{0}; k < i; k++) {
    double temp;
    int i1;
    int temp_tmp;
    temp_tmp = (ix0 + k) - 1;
    temp = x_data[temp_tmp];
    i1 = (iy0 + k) - 1;
    x_data[temp_tmp] = x_data[i1];
    x_data[i1] = temp;
  }
}

//
// Arguments    : int n
//                double x_data[]
//                int ix0
//                int incx
//                int iy0
//                int incy
// Return Type  : void
//
void xswap(int n, double x_data[], int ix0, int incx, int iy0, int incy)
{
  int i;
  i = static_cast<unsigned char>(n);
  for (int k{0}; k < i; k++) {
    double temp;
    int i1;
    int temp_tmp;
    temp_tmp = (ix0 + k * incx) - 1;
    temp = x_data[temp_tmp];
    i1 = (iy0 + k * incy) - 1;
    x_data[temp_tmp] = x_data[i1];
    x_data[i1] = temp;
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for xswap.cpp
//
// [EOF]
//
