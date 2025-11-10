//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzgeqp3.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 08-Nov-2025 17:08:58
//

// Include Files
#include "xzgeqp3.h"
#include "ixamax.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xswap.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : double A_data[]
//                const int A_size[2]
//                int m
//                int n
//                double tau_data[]
//                int jpvt_data[]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace reflapack {
void qrpf(double A_data[], const int A_size[2], int m, int n, double tau_data[],
          int jpvt_data[])
{
  double vn1_data[3];
  double vn2_data[3];
  double work_data[3];
  double atmp;
  int i;
  int itemp;
  int ma;
  ma = A_size[0];
  itemp = A_size[1];
  if (itemp - 1 >= 0) {
    std::memset(&work_data[0], 0,
                static_cast<unsigned int>(itemp) * sizeof(double));
    std::memset(&vn1_data[0], 0,
                static_cast<unsigned int>(itemp) * sizeof(double));
    std::memset(&vn2_data[0], 0,
                static_cast<unsigned int>(itemp) * sizeof(double));
  }
  itemp = static_cast<unsigned char>(n);
  for (int j{0}; j < itemp; j++) {
    atmp = blas::xnrm2(m, A_data, j * ma + 1);
    vn1_data[j] = atmp;
    vn2_data[j] = atmp;
  }
  if (m <= n) {
    itemp = m;
  } else {
    itemp = n;
  }
  i = static_cast<unsigned char>(itemp);
  for (int b_i{0}; b_i < i; b_i++) {
    double temp1;
    int ii;
    int ip1;
    int mmi;
    int nmi;
    int pvt;
    ip1 = b_i + 2;
    itemp = b_i * ma;
    ii = itemp + b_i;
    nmi = n - b_i;
    mmi = m - b_i;
    pvt = (b_i + blas::ixamax(nmi, vn1_data, b_i + 1)) - 1;
    if (pvt + 1 != b_i + 1) {
      blas::xswap(m, A_data, pvt * ma + 1, itemp + 1);
      itemp = jpvt_data[pvt];
      jpvt_data[pvt] = jpvt_data[b_i];
      jpvt_data[b_i] = itemp;
      vn1_data[pvt] = vn1_data[b_i];
      vn2_data[pvt] = vn2_data[b_i];
    }
    if (b_i + 1 < m) {
      atmp = A_data[ii];
      temp1 = xzlarfg(mmi, atmp, A_data, ii + 2);
      tau_data[b_i] = temp1;
      A_data[ii] = atmp;
    } else {
      temp1 = 0.0;
      tau_data[b_i] = 0.0;
    }
    if (b_i + 1 < n) {
      atmp = A_data[ii];
      A_data[ii] = 1.0;
      xzlarf(mmi, nmi - 1, ii + 1, temp1, A_data, (ii + ma) + 1, ma, work_data);
      A_data[ii] = atmp;
    }
    for (int j{ip1}; j <= n; j++) {
      itemp = b_i + (j - 1) * ma;
      atmp = vn1_data[j - 1];
      if (atmp != 0.0) {
        double temp2;
        temp1 = std::abs(A_data[itemp]) / atmp;
        temp1 = 1.0 - temp1 * temp1;
        if (temp1 < 0.0) {
          temp1 = 0.0;
        }
        temp2 = atmp / vn2_data[j - 1];
        temp2 = temp1 * (temp2 * temp2);
        if (temp2 <= 1.4901161193847656E-8) {
          if (b_i + 1 < m) {
            atmp = blas::xnrm2(mmi - 1, A_data, itemp + 2);
            vn1_data[j - 1] = atmp;
            vn2_data[j - 1] = atmp;
          } else {
            vn1_data[j - 1] = 0.0;
            vn2_data[j - 1] = 0.0;
          }
        } else {
          vn1_data[j - 1] = atmp * std::sqrt(temp1);
        }
      }
    }
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzgeqp3.cpp
//
// [EOF]
//
