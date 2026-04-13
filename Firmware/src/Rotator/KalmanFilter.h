#include <ArduinoEigen.h>

namespace KalmanFilter {
    void init();
    std::array<float, 9> extrapolate(float t);
    void predict(float t);
    void accelUpdate(float t, std::array<float, 3> accel);
    void GPSUpdate(float t, std::array<float, 3> GPS);
    void baroUpdate(float t, float baro);
}
