/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xhseqr.c
 *
 * Code generation for function 'xhseqr'
 *
 */

/* Include files */
#include "xhseqr.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xzlarfg.h"
#include "mwmathutil.h"
#include <xmmintrin.h>

/* Function Definitions */
int32_T xhseqr(real32_T h[9])
{
  int32_T b_k;
  int32_T c_k;
  int32_T i;
  int32_T info;
  int32_T kdefl;
  real32_T h12;
  real32_T h21;
  real32_T h22;
  real32_T rt1r;
  real32_T rt2r;
  real32_T s;
  real32_T sum;
  real32_T temp;
  boolean_T exitg1;
  info = 0;
  h[2] = 0.0F;
  kdefl = 0;
  i = 2;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    int32_T its;
    int32_T ix_tmp;
    int32_T iy;
    int32_T k;
    int32_T scalarLB;
    int32_T temp_tmp_tmp;
    boolean_T converged;
    boolean_T exitg2;
    k = -1;
    converged = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      boolean_T exitg3;
      k = i - 1;
      exitg3 = false;
      while ((!exitg3) && (k + 2 > 1)) {
        iy = k + 3 * k;
        rt1r = muSingleScalarAbs(h[iy + 1]);
        if (rt1r <= 2.95822839E-31F) {
          exitg3 = true;
        } else {
          ix_tmp = 3 * (k + 1);
          temp_tmp_tmp = k + ix_tmp;
          h12 = muSingleScalarAbs(h[temp_tmp_tmp + 1]);
          temp = muSingleScalarAbs(h[iy]) + h12;
          if (temp == 0.0F) {
            if (k >= 1) {
              temp = muSingleScalarAbs(h[k]);
            }
            if (k + 3 <= 3) {
              temp += muSingleScalarAbs(h[ix_tmp + 2]);
            }
          }
          if (rt1r <= 1.1920929E-7F * temp) {
            h21 = muSingleScalarAbs(h[temp_tmp_tmp]);
            temp = muSingleScalarAbs(h[iy] - h[temp_tmp_tmp + 1]);
            rt2r = muSingleScalarMax(h12, temp);
            temp = muSingleScalarMin(h12, temp);
            s = rt2r + temp;
            if (muSingleScalarMin(rt1r, h21) *
                    (muSingleScalarMax(rt1r, h21) / s) <=
                muSingleScalarMax(2.95822839E-31F,
                                  1.1920929E-7F * (temp * (rt2r / s)))) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }
      if (k + 2 > 1) {
        h[(k + 3 * k) + 1] = 0.0F;
      }
      if (k + 2 >= i) {
        converged = true;
        exitg2 = true;
      } else {
        int32_T m;
        real32_T v[3];
        kdefl++;
        if (kdefl - kdefl / 20 * 20 == 0) {
          s = muSingleScalarAbs(h[i + 3 * (i - 1)]) +
              muSingleScalarAbs(h[i - 1]);
          temp = 0.75F * s + h[i + 3 * i];
          h12 = -0.4375F * s;
          h21 = s;
          h22 = temp;
        } else if (kdefl - kdefl / 10 * 10 == 0) {
          s = muSingleScalarAbs(h[1]) + muSingleScalarAbs(h[5]);
          temp = 0.75F * s + h[0];
          h12 = -0.4375F * s;
          h21 = s;
          h22 = temp;
        } else {
          iy = i + 3 * (i - 1);
          temp = h[iy - 1];
          h21 = h[iy];
          iy = i + 3 * i;
          h12 = h[iy - 1];
          h22 = h[iy];
        }
        s = ((muSingleScalarAbs(temp) + muSingleScalarAbs(h12)) +
             muSingleScalarAbs(h21)) +
            muSingleScalarAbs(h22);
        if (s == 0.0F) {
          rt1r = 0.0F;
          temp = 0.0F;
          rt2r = 0.0F;
          h12 = 0.0F;
        } else {
          temp /= s;
          h21 /= s;
          h12 /= s;
          h22 /= s;
          sum = (temp + h22) / 2.0F;
          temp = (temp - sum) * (h22 - sum) - h12 * h21;
          h12 = muSingleScalarSqrt(muSingleScalarAbs(temp));
          if (temp >= 0.0F) {
            rt1r = sum * s;
            rt2r = rt1r;
            temp = h12 * s;
            h12 = -temp;
          } else {
            rt1r = sum + h12;
            rt2r = sum - h12;
            if (muSingleScalarAbs(rt1r - h22) <=
                muSingleScalarAbs(rt2r - h22)) {
              rt1r *= s;
              rt2r = rt1r;
            } else {
              rt2r *= s;
              rt1r = rt2r;
            }
            temp = 0.0F;
            h12 = 0.0F;
          }
        }
        m = i - 1;
        if (i - 1 >= 1) {
          s = (muSingleScalarAbs(h[0] - rt2r) + muSingleScalarAbs(h12)) +
              muSingleScalarAbs(h[1]);
          h21 = h[1] / s;
          v[0] = (h21 * h[3] + (h[0] - rt1r) * ((h[0] - rt2r) / s)) -
                 temp * (h12 / s);
          v[1] = h21 * (((h[0] + h[4]) - rt1r) - rt2r);
          v[2] = h21 * h[5];
          temp = (muSingleScalarAbs(v[0]) + muSingleScalarAbs(v[1])) +
                 muSingleScalarAbs(v[2]);
          v[0] /= temp;
          v[1] /= temp;
          v[2] /= temp;
        }
        for (c_k = m; c_k <= i; c_k++) {
          iy = (i - c_k) + 2;
          iy = muIntScalarMin_sint32(3, iy);
          if (c_k > i - 1) {
            ix_tmp = ((c_k - 2) * 3 + c_k) - 1;
            for (b_k = 0; b_k < iy; b_k++) {
              v[b_k] = h[ix_tmp + b_k];
            }
          }
          temp = v[0];
          h22 = b_xzlarfg(iy, &temp, v);
          if (c_k > i - 1) {
            h[c_k - 1] = temp;
            h[c_k] = 0.0F;
            if (c_k < i) {
              /* Check node always fails. would cause program termination and
               * was eliminated */
            }
          }
          rt2r = v[1];
          rt1r = h22 * v[1];
          if (iy == 3) {
            int32_T b_scalarLB;
            h12 = v[2];
            h21 = h22 * v[2];
            for (b_k = c_k; b_k < 4; b_k++) {
              iy = 3 * (b_k - 1);
              ix_tmp = c_k + iy;
              temp = h[ix_tmp - 1];
              sum = (temp + rt2r * h[ix_tmp]) + h12 * h[iy + 2];
              h[ix_tmp - 1] = temp - sum * h22;
              h[ix_tmp] -= sum * rt1r;
              h[iy + 2] -= sum * h21;
            }
            iy = c_k + 3;
            ix_tmp = i + 1;
            scalarLB = muIntScalarMin_sint32(iy, ix_tmp);
            b_scalarLB = (scalarLB / 4) << 2;
            iy = b_scalarLB - 4;
            for (b_k = 0; b_k <= iy; b_k += 4) {
              __m128 r;
              __m128 r1;
              __m128 r2;
              ix_tmp = b_k + 3 * c_k;
              r = _mm_loadu_ps(&h[ix_tmp]);
              temp_tmp_tmp = b_k + 3 * (c_k - 1);
              r1 = _mm_loadu_ps(&h[temp_tmp_tmp]);
              r2 = _mm_loadu_ps(&h[b_k + 6]);
              r1 = _mm_add_ps(_mm_add_ps(r1, _mm_mul_ps(_mm_set1_ps(rt2r), r)),
                              _mm_mul_ps(_mm_set1_ps(h12), r2));
              r = _mm_loadu_ps(&h[temp_tmp_tmp]);
              _mm_storeu_ps(&h[temp_tmp_tmp],
                            _mm_sub_ps(r, _mm_mul_ps(r1, _mm_set1_ps(h22))));
              r = _mm_loadu_ps(&h[ix_tmp]);
              _mm_storeu_ps(&h[ix_tmp],
                            _mm_sub_ps(r, _mm_mul_ps(r1, _mm_set1_ps(rt1r))));
              r = _mm_loadu_ps(&h[b_k + 6]);
              _mm_storeu_ps(&h[b_k + 6],
                            _mm_sub_ps(r, _mm_mul_ps(r1, _mm_set1_ps(h21))));
            }
            for (b_k = b_scalarLB; b_k < scalarLB; b_k++) {
              iy = b_k + 3 * (c_k - 1);
              temp = h[iy];
              ix_tmp = b_k + 3 * c_k;
              sum = (temp + rt2r * h[ix_tmp]) + h12 * h[b_k + 6];
              h[iy] = temp - sum * h22;
              h[ix_tmp] -= sum * rt1r;
              h[b_k + 6] -= sum * h21;
            }
          } else if (iy == 2) {
            for (b_k = c_k; b_k < 4; b_k++) {
              iy = c_k + 3 * (b_k - 1);
              temp = h[iy - 1];
              h12 = h[iy];
              sum = temp + rt2r * h12;
              temp -= sum * h22;
              h[iy - 1] = temp;
              h12 -= sum * rt1r;
              h[iy] = h12;
            }
            scalarLB = ((i + 1) / 4) << 2;
            iy = scalarLB - 4;
            for (b_k = 0; b_k <= iy; b_k += 4) {
              __m128 r;
              __m128 r1;
              __m128 r2;
              ix_tmp = b_k + 3 * c_k;
              r = _mm_loadu_ps(&h[ix_tmp]);
              temp_tmp_tmp = b_k + 3 * (c_k - 1);
              r1 = _mm_loadu_ps(&h[temp_tmp_tmp]);
              r2 = _mm_add_ps(r1, _mm_mul_ps(_mm_set1_ps(rt2r), r));
              _mm_storeu_ps(&h[temp_tmp_tmp],
                            _mm_sub_ps(r1, _mm_mul_ps(r2, _mm_set1_ps(h22))));
              _mm_storeu_ps(&h[ix_tmp],
                            _mm_sub_ps(r, _mm_mul_ps(r2, _mm_set1_ps(rt1r))));
            }
            for (b_k = scalarLB; b_k <= i; b_k++) {
              iy = b_k + 3 * (c_k - 1);
              temp = h[iy];
              ix_tmp = b_k + 3 * c_k;
              h12 = h[ix_tmp];
              sum = temp + rt2r * h12;
              temp -= sum * h22;
              h[iy] = temp;
              h12 -= sum * rt1r;
              h[ix_tmp] = h12;
            }
          }
        }
        its++;
      }
    }
    if (!converged) {
      info = i + 1;
      exitg1 = true;
    } else {
      if ((k + 2 != i + 1) && (k + 2 == i)) {
        iy = i + 3 * i;
        temp = h[iy - 1];
        scalarLB = 3 * (i - 1);
        ix_tmp = i + scalarLB;
        h12 = h[ix_tmp];
        h21 = h[iy];
        xdlanv2(&h[ix_tmp - 1], &temp, &h12, &h21, &rt2r, &rt1r, &sum, &h22,
                &s);
        h[iy - 1] = temp;
        h[ix_tmp] = h12;
        h[iy] = h21;
        if (i + 1 < 3) {
          iy = 1 - i;
          ix_tmp = (i + 1) * 3 + i;
          for (b_k = 0; b_k <= iy; b_k++) {
            temp_tmp_tmp = ix_tmp + b_k * 3;
            temp = h[temp_tmp_tmp];
            h12 = h[temp_tmp_tmp - 1];
            h[temp_tmp_tmp] = h22 * temp - s * h12;
            h[temp_tmp_tmp - 1] = h22 * h12 + s * temp;
          }
        }
        if (i - 1 >= 1) {
          iy = i * 3;
          temp = h22 * h[scalarLB] + s * h[iy];
          h[iy] = h22 * h[iy] - s * h[scalarLB];
          h[scalarLB] = temp;
        }
      }
      kdefl = 0;
      i = k;
    }
  }
  h[2] = 0.0F;
  return info;
}

/* End of code generation (xhseqr.c) */
