#include "anyNonFinite.h"
#include "codegenTest_float_mex_data.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

boolean_T anyNonFinite(const real_T x[9])
{
  int32_T k;
  boolean_T p;
  p = true;
  for (k = 0; k < 9; k++) {
    if (p) {
      real_T d;
      d = x[k];
      if (muDoubleScalarIsInf(d) || muDoubleScalarIsNaN(d)) {
        p = false;
      }
    } else {
      p = false;
    }
  }
  return !p;
}
