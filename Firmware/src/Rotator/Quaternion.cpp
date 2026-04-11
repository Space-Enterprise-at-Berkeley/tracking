#include "Quaternion.h"

namespace Quaternion {
    quat multiply(quat a, quat b) {
        return {
            a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z,
            a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
            a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
            a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w
        };
    }
    quat conjugate(quat a) {
        return {a.w, -a.x, -a.y, -a.z};
    }
    quat normalize(quat a) {
        float norm = sqrt(a.w*a.w + a.x*a.x + a.y*a.y + a.z*a.z);
        return {a.w/norm, a.x/norm, a.y/norm, a.z/norm};
    }
}