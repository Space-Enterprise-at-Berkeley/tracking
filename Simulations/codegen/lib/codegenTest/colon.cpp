//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: colon.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "colon.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : int b
//                int y_data[]
//                int y_size[2]
// Return Type  : void
//
namespace coder {
void eml_integer_colon_dispatcher(int b, int y_data[], int y_size[2])
{
  int n;
  if (b < 1) {
    n = 0;
  } else {
    n = static_cast<unsigned char>(b - 1) + 1;
  }
  y_size[0] = 1;
  y_size[1] = n;
  if (n > 0) {
    int yk;
    y_data[0] = 1;
    yk = 1;
    for (int k{2}; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
  }
}

} // namespace coder

//
// File trailer for colon.cpp
//
// [EOF]
//
