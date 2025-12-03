#include "xhseqr.h"
#include "codegenTest_float_mex_data.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xzlarfg.h"
#include "mwmathutil.h"
#include <emmintrin.h>

int32_T xhseqr(real_T h[9])
{
  real_T v[3];
  real_T h12;
  real_T h21;
  real_T h22;
  real_T rt1r;
  real_T rt2r;
  real_T s;
  real_T sum;
  real_T temp;
  int32_T b_k;
  int32_T c_k;
  int32_T i;
  int32_T info;
  int32_T kdefl;
  boolean_T exitg1;
  info = 0;
  h[2] = 0.0;
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
        rt1r = muDoubleScalarAbs(h[iy + 1]);
        if (rt1r <= 3.0062525400134592E-292) {
          exitg3 = true;
        } else {
          ix_tmp = 3 * (k + 1);
          temp_tmp_tmp = k + ix_tmp;
          h12 = muDoubleScalarAbs(h[temp_tmp_tmp + 1]);
          temp = muDoubleScalarAbs(h[iy]) + h12;
          if (temp == 0.0) {
            if (k >= 1) {
              temp = muDoubleScalarAbs(h[k]);
            }
            if (k + 3 <= 3) {
              temp += muDoubleScalarAbs(h[ix_tmp + 2]);
            }
          }
          if (rt1r <= 2.2204460492503131E-16 * temp) {
            h21 = muDoubleScalarAbs(h[temp_tmp_tmp]);
            temp = muDoubleScalarAbs(h[iy] - h[temp_tmp_tmp + 1]);
            rt2r = muDoubleScalarMax(h12, temp);
            temp = muDoubleScalarMin(h12, temp);
            s = rt2r + temp;
            if (muDoubleScalarMin(rt1r, h21) *
                    (muDoubleScalarMax(rt1r, h21) / s) <=
                muDoubleScalarMax(3.0062525400134592E-292,
                                  2.2204460492503131E-16 *
                                      (temp * (rt2r / s)))) {
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
        h[(k + 3 * k) + 1] = 0.0;
      }
      if (k + 2 >= i) {
        converged = true;
        exitg2 = true;
      } else {
        __m128d r;
        int32_T m;
        kdefl++;
        if (kdefl - kdefl / 20 * 20 == 0) {
          s = muDoubleScalarAbs(h[i + 3 * (i - 1)]) +
              muDoubleScalarAbs(h[i - 1]);
          temp = 0.75 * s + h[i + 3 * i];
          h12 = -0.4375 * s;
          h21 = s;
          h22 = temp;
        } else if (kdefl - kdefl / 10 * 10 == 0) {
          s = muDoubleScalarAbs(h[1]) + muDoubleScalarAbs(h[5]);
          temp = 0.75 * s + h[0];
          h12 = -0.4375 * s;
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
        s = ((muDoubleScalarAbs(temp) + muDoubleScalarAbs(h12)) +
             muDoubleScalarAbs(h21)) +
            muDoubleScalarAbs(h22);
        if (s == 0.0) {
          rt1r = 0.0;
          temp = 0.0;
          rt2r = 0.0;
          h12 = 0.0;
        } else {
          temp /= s;
          h21 /= s;
          h12 /= s;
          h22 /= s;
          sum = (temp + h22) / 2.0;
          temp = (temp - sum) * (h22 - sum) - h12 * h21;
          h12 = muDoubleScalarSqrt(muDoubleScalarAbs(temp));
          if (temp >= 0.0) {
            rt1r = sum * s;
            rt2r = rt1r;
            temp = h12 * s;
            h12 = -temp;
          } else {
            rt1r = sum + h12;
            rt2r = sum - h12;
            if (muDoubleScalarAbs(rt1r - h22) <=
                muDoubleScalarAbs(rt2r - h22)) {
              rt1r *= s;
              rt2r = rt1r;
            } else {
              rt2r *= s;
              rt1r = rt2r;
            }
            temp = 0.0;
            h12 = 0.0;
          }
        }
        m = i - 1;
        if (i - 1 >= 1) {
          s = (muDoubleScalarAbs(h[0] - rt2r) + muDoubleScalarAbs(h12)) +
              muDoubleScalarAbs(h[1]);
          h21 = h[1] / s;
          v[0] = (h21 * h[3] + (h[0] - rt1r) * ((h[0] - rt2r) / s)) -
                 temp * (h12 / s);
          v[1] = h21 * (((h[0] + h[4]) - rt1r) - rt2r);
          v[2] = h21 * h[5];
          s = (muDoubleScalarAbs(v[0]) + muDoubleScalarAbs(v[1])) +
              muDoubleScalarAbs(v[2]);
          r = _mm_loadu_pd(&v[0]);
          _mm_storeu_pd(&v[0], _mm_div_pd(r, _mm_set1_pd(s)));
          v[2] /= s;
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
            h[c_k] = 0.0;
            if (c_k < i) {
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
            b_scalarLB = (scalarLB / 2) << 1;
            iy = b_scalarLB - 2;
            for (b_k = 0; b_k <= iy; b_k += 2) {
              __m128d r1;
              __m128d r2;
              ix_tmp = b_k + 3 * c_k;
              r = _mm_loadu_pd(&h[ix_tmp]);
              temp_tmp_tmp = b_k + 3 * (c_k - 1);
              r1 = _mm_loadu_pd(&h[temp_tmp_tmp]);
              r2 = _mm_loadu_pd(&h[b_k + 6]);
              r1 = _mm_add_pd(_mm_add_pd(r1, _mm_mul_pd(_mm_set1_pd(rt2r), r)),
                              _mm_mul_pd(_mm_set1_pd(h12), r2));
              r = _mm_loadu_pd(&h[temp_tmp_tmp]);
              _mm_storeu_pd(&h[temp_tmp_tmp],
                            _mm_sub_pd(r, _mm_mul_pd(r1, _mm_set1_pd(h22))));
              r = _mm_loadu_pd(&h[ix_tmp]);
              _mm_storeu_pd(&h[ix_tmp],
                            _mm_sub_pd(r, _mm_mul_pd(r1, _mm_set1_pd(rt1r))));
              r = _mm_loadu_pd(&h[b_k + 6]);
              _mm_storeu_pd(&h[b_k + 6],
                            _mm_sub_pd(r, _mm_mul_pd(r1, _mm_set1_pd(h21))));
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
            scalarLB = ((i + 1) / 2) << 1;
            iy = scalarLB - 2;
            for (b_k = 0; b_k <= iy; b_k += 2) {
              __m128d r1;
              __m128d r2;
              ix_tmp = b_k + 3 * c_k;
              r = _mm_loadu_pd(&h[ix_tmp]);
              temp_tmp_tmp = b_k + 3 * (c_k - 1);
              r1 = _mm_loadu_pd(&h[temp_tmp_tmp]);
              r2 = _mm_add_pd(r1, _mm_mul_pd(_mm_set1_pd(rt2r), r));
              _mm_storeu_pd(&h[temp_tmp_tmp],
                            _mm_sub_pd(r1, _mm_mul_pd(r2, _mm_set1_pd(h22))));
              _mm_storeu_pd(&h[ix_tmp],
                            _mm_sub_pd(r, _mm_mul_pd(r2, _mm_set1_pd(rt1r))));
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
  h[2] = 0.0;
  return info;
}
