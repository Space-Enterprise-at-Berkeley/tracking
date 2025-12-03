/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdlanv2.c
 *
 * Code generation for function 'xdlanv2'
 *
 */

/* Include files */
#include "xdlanv2.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

/* Function Definitions */
real32_T xdlanv2(real32_T *a, real32_T *b, real32_T *c, real32_T *d,
                 real32_T *rt1i, real32_T *rt2r, real32_T *rt2i, real32_T *cs,
                 real32_T *sn)
{
  real32_T rt1r;
  if (*c == 0.0F) {
    *cs = 1.0F;
    *sn = 0.0F;
  } else if (*b == 0.0F) {
    real32_T temp;
    *cs = 0.0F;
    *sn = 1.0F;
    temp = *d;
    *d = *a;
    *a = temp;
    *b = -*c;
    *c = 0.0F;
  } else {
    real32_T temp;
    temp = *a - *d;
    if ((temp == 0.0F) && ((*b < 0.0F) != (*c < 0.0F))) {
      *cs = 1.0F;
      *sn = 0.0F;
    } else {
      int32_T count;
      int32_T i;
      real32_T bcmax;
      real32_T bcmis;
      real32_T p;
      real32_T scale;
      p = 0.5F * temp;
      rt1r = muSingleScalarAbs(*b);
      scale = muSingleScalarAbs(*c);
      bcmax = muSingleScalarMax(rt1r, scale);
      if (!(*b < 0.0F)) {
        count = 1;
      } else {
        count = -1;
      }
      if (!(*c < 0.0F)) {
        i = 1;
      } else {
        i = -1;
      }
      bcmis = muSingleScalarMin(rt1r, scale) * (real32_T)count * (real32_T)i;
      scale = muSingleScalarMax(muSingleScalarAbs(p), bcmax);
      rt1r = p / scale * p + bcmax / scale * bcmis;
      if (rt1r >= 4.76837158E-7F) {
        rt1r = muSingleScalarSqrt(scale) * muSingleScalarSqrt(rt1r);
        if (p < 0.0F) {
          rt1r = -rt1r;
        }
        rt1r += p;
        *a = *d + rt1r;
        *d -= bcmax / rt1r * bcmis;
        bcmax = muSingleScalarHypot(*c, rt1r);
        *cs = rt1r / bcmax;
        *sn = *c / bcmax;
        *b -= *c;
        *c = 0.0F;
      } else {
        rt1r = *b + *c;
        scale =
            muSingleScalarMax(muSingleScalarAbs(temp), muSingleScalarAbs(rt1r));
        count = 0;
        while ((scale >= 5.49755814E+11F) && (count <= 20)) {
          rt1r *= 1.8189894E-12F;
          temp *= 1.8189894E-12F;
          scale = muSingleScalarMax(muSingleScalarAbs(temp),
                                    muSingleScalarAbs(rt1r));
          count++;
        }
        while ((scale <= 1.8189894E-12F) && (count <= 20)) {
          rt1r *= 5.49755814E+11F;
          temp *= 5.49755814E+11F;
          scale = muSingleScalarMax(muSingleScalarAbs(temp),
                                    muSingleScalarAbs(rt1r));
          count++;
        }
        bcmax = muSingleScalarHypot(rt1r, temp);
        *cs =
            muSingleScalarSqrt(0.5F * (muSingleScalarAbs(rt1r) / bcmax + 1.0F));
        if (!(rt1r < 0.0F)) {
          count = 1;
        } else {
          count = -1;
        }
        *sn = -(0.5F * temp / (bcmax * *cs)) * (real32_T)count;
        rt1r = *a * *cs + *b * *sn;
        scale = -*a * *sn + *b * *cs;
        bcmis = *c * *cs + *d * *sn;
        bcmax = -*c * *sn + *d * *cs;
        *b = scale * *cs + bcmax * *sn;
        *c = -rt1r * *sn + bcmis * *cs;
        temp =
            0.5F * ((rt1r * *cs + bcmis * *sn) + (-scale * *sn + bcmax * *cs));
        *a = temp;
        *d = temp;
        if (*c != 0.0F) {
          if (*b != 0.0F) {
            if ((*b < 0.0F) == (*c < 0.0F)) {
              rt1r = muSingleScalarSqrt(muSingleScalarAbs(*b));
              bcmis = muSingleScalarSqrt(muSingleScalarAbs(*c));
              p = rt1r * bcmis;
              if (*c < 0.0F) {
                p = -p;
              }
              bcmax = 1.0F / muSingleScalarSqrt(muSingleScalarAbs(*b + *c));
              *a = temp + p;
              *d = temp - p;
              *b -= *c;
              *c = 0.0F;
              scale = rt1r * bcmax;
              rt1r = bcmis * bcmax;
              temp = *cs * scale - *sn * rt1r;
              *sn = *cs * rt1r + *sn * scale;
              *cs = temp;
            }
          } else {
            *b = -*c;
            *c = 0.0F;
            temp = *cs;
            *cs = -*sn;
            *sn = temp;
          }
        }
      }
    }
  }
  rt1r = *a;
  *rt2r = *d;
  if (*c == 0.0F) {
    *rt1i = 0.0F;
    *rt2i = 0.0F;
  } else {
    *rt1i = muSingleScalarSqrt(muSingleScalarAbs(*b)) *
            muSingleScalarSqrt(muSingleScalarAbs(*c));
    *rt2i = -*rt1i;
  }
  return rt1r;
}

/* End of code generation (xdlanv2.c) */
