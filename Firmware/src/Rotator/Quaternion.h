#include <cmath>
struct Quaternion {
    float w, x, y, z;

    // Normalize quaternion
    void normalize() {
        float norm = sqrt(w*w + x*x + y*y + z*z);
        w /= norm;
        x /= norm;
        y /= norm;
        z /= norm;
    }

    // Conjugate
    Quaternion conjugate() const {
        return {w, -x, -y, -z};
    }
};
Quaternion multiply(const Quaternion& a, const Quaternion& b) {
    return {
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z,
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w
    };
}
Quaternion q = {1, 0, 0, 0}; // initial orientation
