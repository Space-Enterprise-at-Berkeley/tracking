#include "xdlanv2.h"
#include "codegenTest_float_mex_data.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

real_T xdlanv2(real_T *a, real_T *b, real_T *c, real_T *d, real_T *rt1i,
               real_T *rt2r, real_T *rt2i, real_T *cs, real_T *sn)
{
  real_T rt1r;
  if (*c == 0.0) {
    *cs = 1.0;
    *sn = 0.0;
  } else if (*b == 0.0) {
    real_T temp;
    *cs = 0.0;
    *sn = 1.0;
    temp = *d;
    *d = *a;
    *a = temp;
    *b = -*c;
    *c = 0.0;
  } else {
    real_T temp;
    temp = *a - *d;
    if ((temp == 0.0) && ((*b < 0.0) != (*c < 0.0))) {
      *cs = 1.0;
      *sn = 0.0;
    } else {
      real_T bcmax;
      real_T bcmis;
      real_T p;
      real_T scale;
      int32_T count;
      int32_T i;
      p = 0.5 * temp;
      rt1r = muDoubleScalarAbs(*b);
      scale = muDoubleScalarAbs(*c);
      bcmax = muDoubleScalarMax(rt1r, scale);
      if (!(*b < 0.0)) {
        count = 1;
      } else {
        count = -1;
      }
      if (!(*c < 0.0)) {
        i = 1;
      } else {
        i = -1;
      }
      bcmis = muDoubleScalarMin(rt1r, scale) * (real_T)count * (real_T)i;
      scale = muDoubleScalarMax(muDoubleScalarAbs(p), bcmax);
      rt1r = p / scale * p + bcmax / scale * bcmis;
      if (rt1r >= 8.8817841970012523E-16) {
        rt1r = muDoubleScalarSqrt(scale) * muDoubleScalarSqrt(rt1r);
        if (p < 0.0) {
          rt1r = -rt1r;
        }
        rt1r += p;
        *a = *d + rt1r;
        *d -= bcmax / rt1r * bcmis;
        bcmax = muDoubleScalarHypot(*c, rt1r);
        *cs = rt1r / bcmax;
        *sn = *c / bcmax;
        *b -= *c;
        *c = 0.0;
      } else {
        rt1r = *b + *c;
        scale =
            muDoubleScalarMax(muDoubleScalarAbs(temp), muDoubleScalarAbs(rt1r));
        count = 0;
        while ((scale >= 7.4428285367870146E+137) && (count <= 20)) {
          rt1r *= 1.3435752215134178E-138;
          temp *= 1.3435752215134178E-138;
          scale = muDoubleScalarMax(muDoubleScalarAbs(temp),
                                    muDoubleScalarAbs(rt1r));
          count++;
        }
        while ((scale <= 1.3435752215134178E-138) && (count <= 20)) {
          rt1r *= 7.4428285367870146E+137;
          temp *= 7.4428285367870146E+137;
          scale = muDoubleScalarMax(muDoubleScalarAbs(temp),
                                    muDoubleScalarAbs(rt1r));
          count++;
        }
        bcmax = muDoubleScalarHypot(rt1r, temp);
        *cs = muDoubleScalarSqrt(0.5 * (muDoubleScalarAbs(rt1r) / bcmax + 1.0));
        if (!(rt1r < 0.0)) {
          count = 1;
        } else {
          count = -1;
        }
        *sn = -(0.5 * temp / (bcmax * *cs)) * (real_T)count;
        rt1r = *a * *cs + *b * *sn;
        scale = -*a * *sn + *b * *cs;
        bcmis = *c * *cs + *d * *sn;
        bcmax = -*c * *sn + *d * *cs;
        *b = scale * *cs + bcmax * *sn;
        *c = -rt1r * *sn + bcmis * *cs;
        temp =
            0.5 * ((rt1r * *cs + bcmis * *sn) + (-scale * *sn + bcmax * *cs));
        *a = temp;
        *d = temp;
        if (*c != 0.0) {
          if (*b != 0.0) {
            if ((*b < 0.0) == (*c < 0.0)) {
              rt1r = muDoubleScalarSqrt(muDoubleScalarAbs(*b));
              bcmis = muDoubleScalarSqrt(muDoubleScalarAbs(*c));
              p = rt1r * bcmis;
              if (*c < 0.0) {
                p = -p;
              }
              bcmax = 1.0 / muDoubleScalarSqrt(muDoubleScalarAbs(*b + *c));
              *a = temp + p;
              *d = temp - p;
              *b -= *c;
              *c = 0.0;
              scale = rt1r * bcmax;
              rt1r = bcmis * bcmax;
              temp = *cs * scale - *sn * rt1r;
              *sn = *cs * rt1r + *sn * scale;
              *cs = temp;
            }
          } else {
            *b = -*c;
            *c = 0.0;
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
  if (*c == 0.0) {
    *rt1i = 0.0;
    *rt2i = 0.0;
  } else {
    *rt1i = muDoubleScalarSqrt(muDoubleScalarAbs(*b)) *
            muDoubleScalarSqrt(muDoubleScalarAbs(*c));
    *rt2i = -*rt1i;
  }
  return rt1r;
}
