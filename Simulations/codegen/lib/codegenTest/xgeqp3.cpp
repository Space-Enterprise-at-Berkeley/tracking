//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgeqp3.cpp
//
// MATLAB Coder version            : 25.2
// C/C++ source code generated on  : 03-Dec-2025 20:32:31
//

// Include Files
#include "xgeqp3.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : float A_data[]
//                const int A_size[2]
//                float tau_data[]
//                int jpvt_data[]
//                int jpvt_size[2]
// Return Type  : int
//
namespace coder {
namespace internal {
namespace lapack {
int xgeqp3(float A_data[], const int A_size[2], float tau_data[],
           int jpvt_data[], int jpvt_size[2])
{
  float vn1_data[3];
  float vn2_data[3];
  float work_data[3];
  int knt;
  int m;
  int n;
  int tau_size;
  bool guard1;
  m = A_size[0];
  n = A_size[1] - 1;
  knt = A_size[0];
  tau_size = A_size[1];
  if (knt <= tau_size) {
    tau_size = knt;
  }
  if (tau_size - 1 >= 0) {
    std::memset(&tau_data[0], 0,
                static_cast<unsigned int>(tau_size) * sizeof(float));
  }
  guard1 = false;
  if ((A_size[0] == 0) || (A_size[1] == 0)) {
    guard1 = true;
  } else {
    int ix;
    ix = A_size[1];
    if (knt <= ix) {
      ix = knt;
    }
    if (ix < 1) {
      guard1 = true;
    } else {
      float temp;
      int u1;
      ix = A_size[1];
      jpvt_size[0] = 1;
      jpvt_size[1] = ix;
      if (ix - 1 >= 0) {
        std::memset(&jpvt_data[0], 0,
                    static_cast<unsigned int>(ix) * sizeof(int));
      }
      for (int j{0}; j <= n; j++) {
        jpvt_data[j] = j + 1;
      }
      u1 = A_size[1];
      if (knt <= u1) {
        u1 = knt;
      }
      if (ix - 1 >= 0) {
        std::memset(&work_data[0], 0,
                    static_cast<unsigned int>(ix) * sizeof(float));
        std::memset(&vn1_data[0], 0,
                    static_cast<unsigned int>(ix) * sizeof(float));
        std::memset(&vn2_data[0], 0,
                    static_cast<unsigned int>(ix) * sizeof(float));
      }
      for (int j{0}; j <= n; j++) {
        temp = blas::xnrm2(m, A_data, j * m + 1);
        vn1_data[j] = temp;
        vn2_data[j] = temp;
      }
      for (int i{0}; i < u1; i++) {
        float atmp;
        float beta1;
        int ii;
        int ip1;
        int jA;
        int lastc;
        int mmi;
        int nmi;
        int pvt;
        ip1 = i + 2;
        jA = i * m;
        ii = jA + i;
        nmi = n - i;
        mmi = m - i;
        ix = nmi + 1;
        if (nmi < 0) {
          knt = -1;
        } else {
          knt = 0;
          if (nmi > 0) {
            temp = std::abs(vn1_data[i]);
            for (int j{2}; j <= ix; j++) {
              beta1 = std::abs(vn1_data[(i + j) - 1]);
              if (beta1 > temp) {
                knt = j - 1;
                temp = beta1;
              }
            }
          }
        }
        pvt = i + knt;
        if (pvt != i) {
          ix = pvt * m;
          for (int j{0}; j < m; j++) {
            knt = ix + j;
            temp = A_data[knt];
            lastc = jA + j;
            A_data[knt] = A_data[lastc];
            A_data[lastc] = temp;
          }
          ix = jpvt_data[pvt];
          jpvt_data[pvt] = jpvt_data[i];
          jpvt_data[i] = ix;
          vn1_data[pvt] = vn1_data[i];
          vn2_data[pvt] = vn2_data[i];
        }
        if (i + 1 < m) {
          atmp = A_data[ii];
          lastc = ii + 2;
          tau_data[i] = 0.0F;
          if (mmi > 0) {
            temp = blas::xnrm2(mmi - 1, A_data, ii + 2);
            if (temp != 0.0F) {
              beta1 = std::abs(A_data[ii]);
              temp = std::abs(temp);
              if (beta1 < temp) {
                beta1 /= temp;
                beta1 = temp * std::sqrt(beta1 * beta1 + 1.0F);
              } else if (beta1 > temp) {
                temp /= beta1;
                beta1 *= std::sqrt(temp * temp + 1.0F);
              } else if (std::isnan(temp)) {
                beta1 = rtNaNF;
              } else {
                beta1 *= 1.41421354F;
              }
              if (A_data[ii] >= 0.0F) {
                beta1 = -beta1;
              }
              if (std::abs(beta1) < 9.86076132E-32F) {
                knt = 0;
                ix = ii + mmi;
                do {
                  knt++;
                  for (int j{lastc}; j <= ix; j++) {
                    A_data[j - 1] *= 1.01412048E+31F;
                  }
                  beta1 *= 1.01412048E+31F;
                  atmp *= 1.01412048E+31F;
                } while ((std::abs(beta1) < 9.86076132E-32F) && (knt < 20));
                temp = std::abs(atmp);
                beta1 = std::abs(blas::xnrm2(mmi - 1, A_data, ii + 2));
                if (temp < beta1) {
                  temp /= beta1;
                  beta1 *= std::sqrt(temp * temp + 1.0F);
                } else if (temp > beta1) {
                  beta1 /= temp;
                  beta1 = temp * std::sqrt(beta1 * beta1 + 1.0F);
                } else if (std::isnan(beta1)) {
                  beta1 = rtNaNF;
                } else {
                  beta1 = temp * 1.41421354F;
                }
                if (atmp >= 0.0F) {
                  beta1 = -beta1;
                }
                tau_data[i] = (beta1 - atmp) / beta1;
                temp = 1.0F / (atmp - beta1);
                for (int j{lastc}; j <= ix; j++) {
                  A_data[j - 1] *= temp;
                }
                for (int j{0}; j < knt; j++) {
                  beta1 *= 9.86076132E-32F;
                }
                atmp = beta1;
              } else {
                tau_data[i] = (beta1 - A_data[ii]) / beta1;
                temp = 1.0F / (A_data[ii] - beta1);
                ix = ii + mmi;
                for (int j{lastc}; j <= ix; j++) {
                  A_data[j - 1] *= temp;
                }
                atmp = beta1;
              }
            }
          }
          A_data[ii] = atmp;
        } else {
          tau_data[i] = 0.0F;
        }
        if (i < n) {
          int lastv;
          atmp = A_data[ii];
          A_data[ii] = 1.0F;
          jA = (ii + m) + 1;
          if (tau_data[i] != 0.0F) {
            bool exitg2;
            lastv = mmi - 1;
            knt = (ii + mmi) - 1;
            while ((lastv + 1 > 0) && (A_data[knt] == 0.0F)) {
              lastv--;
              knt--;
            }
            lastc = nmi - 1;
            exitg2 = false;
            while ((!exitg2) && (lastc + 1 > 0)) {
              int exitg1;
              ix = jA + lastc * m;
              knt = ix;
              do {
                exitg1 = 0;
                if (knt <= ix + lastv) {
                  if (A_data[knt - 1] != 0.0F) {
                    exitg1 = 1;
                  } else {
                    knt++;
                  }
                } else {
                  lastc--;
                  exitg1 = 2;
                }
              } while (exitg1 == 0);
              if (exitg1 == 1) {
                exitg2 = true;
              }
            }
          } else {
            lastv = -1;
            lastc = -1;
          }
          if (lastv + 1 > 0) {
            if (lastc + 1 != 0) {
              if (lastc >= 0) {
                std::memset(&work_data[0], 0,
                            static_cast<unsigned int>(lastc + 1) *
                                sizeof(float));
              }
              ix = 0;
              knt = jA + m * lastc;
              for (int j{jA}; m < 0 ? j >= knt : j <= knt; j += m) {
                temp = 0.0F;
                pvt = j + lastv;
                for (int ia{j}; ia <= pvt; ia++) {
                  temp += A_data[ia - 1] * A_data[(ii + ia) - j];
                }
                work_data[ix] += temp;
                ix++;
              }
            }
            if (!(-tau_data[i] == 0.0F)) {
              for (int j{0}; j <= lastc; j++) {
                temp = work_data[j];
                if (temp != 0.0F) {
                  temp *= -tau_data[i];
                  ix = lastv + jA;
                  for (int ia{jA}; ia <= ix; ia++) {
                    A_data[ia - 1] += A_data[(ii + ia) - jA] * temp;
                  }
                }
                jA += m;
              }
            }
          }
          A_data[ii] = atmp;
        }
        for (int j{ip1}; j <= n + 1; j++) {
          knt = i + (j - 1) * m;
          temp = vn1_data[j - 1];
          if (temp != 0.0F) {
            beta1 = std::abs(A_data[knt]) / temp;
            beta1 = 1.0F - beta1 * beta1;
            if (beta1 < 0.0F) {
              beta1 = 0.0F;
            }
            atmp = temp / vn2_data[j - 1];
            atmp = beta1 * (atmp * atmp);
            if (atmp <= 0.000345266977F) {
              if (i + 1 < m) {
                temp = blas::xnrm2(mmi - 1, A_data, knt + 2);
                vn1_data[j - 1] = temp;
                vn2_data[j - 1] = temp;
              } else {
                vn1_data[j - 1] = 0.0F;
                vn2_data[j - 1] = 0.0F;
              }
            } else {
              vn1_data[j - 1] = temp * std::sqrt(beta1);
            }
          }
        }
      }
    }
  }
  if (guard1) {
    knt = A_size[1];
    jpvt_size[0] = 1;
    jpvt_size[1] = knt;
    if (knt - 1 >= 0) {
      std::memset(&jpvt_data[0], 0,
                  static_cast<unsigned int>(knt) * sizeof(int));
    }
    for (int j{0}; j <= n; j++) {
      jpvt_data[j] = j + 1;
    }
  }
  return tau_size;
}

} // namespace lapack
} // namespace internal
} // namespace coder

//
// File trailer for xgeqp3.cpp
//
// [EOF]
//
