#pragma once

#include <cmath>
namespace Quaternion {
    struct quat {
        float w, x, y, z;
    };
    quat multiply(quat a, quat b);
    quat conjugate(quat a);
    quat normalize(quat a);
}