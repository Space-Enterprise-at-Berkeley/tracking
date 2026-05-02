#include <ArduinoEigen.h>

using Eigen::Matrix;
using Eigen::Vector;

namespace KalmanFilter {
    void CVmode(bool enable);
    void reset();
    Vector<float, 9> extrapolate(float t);
    Vector<float, 9> predict(float t);
    void accelUpdate(float t, Vector<float, 3> accel);
    void GPSUpdate(float t, Vector<float, 3> GPS);
    void baroUpdate(float t, float baro);
}
