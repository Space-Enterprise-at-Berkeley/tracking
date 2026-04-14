#include "KalmanFilter.h"

using Eigen::Matrix;
using Eigen::Vector;

namespace KalmanFilter {
    float time;
    Vector<float, 9> state; // Xpos, Xvel, Xacc, Ypos, ...
    Matrix<float, 9, 9> stateCov;

    Matrix<float, 3, 9> accelObservation {{0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1}};
    Matrix<float, 3, 3> accelNoiseCov {{5, 0, 0}, {0, 5, 0}, {0, 0, 5}};

    Matrix<float, 3, 9> GPSObservation {{1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 0}};
    Matrix<float, 3, 3> GPSNoiseCov {{5, 0, 0}, {0, 5, 0}, {0, 0, 5}};

    Matrix<float, 1, 9> baroObservation {{0, 0, 0, 0, 0, 0, 1, 0, 0}};
    Matrix<float, 1, 1> baroNoiseCov {{5}};

    Matrix<float, 9, 9> processNoiseCovRate = accelObservation.transpose() * Matrix<float, 3, 3>{{5, 0, 0}, {0, 5, 0}, {0, 0, 20}} * accelObservation; // Variance per second caused by changing forces

    Matrix<float, 9, 9> stateTransition(float dt) {
        Matrix<float, 9, 9> out;
        Matrix<float, 3, 3> block {{1, dt, 0.5F*dt*dt}, {0, 1, dt}, {0, 0, 1}};
        Matrix<float, 3, 3> zero = Matrix<float, 3, 3>::Zero();
        out << block, zero, zero, zero, block, zero, zero, zero, block;
        return out;
    }

    void init() {
        time = 0;
        state = Vector<float, 9>::Zero();
        stateCov = Matrix<float, 9, 9>::Zero();
    }

    Vector<float, 9> extrapolate(float t) {
        float dt = t - time;
        return stateTransition(dt) * state;
    }

    Vector<float, 9> predict(float t) {
        float dt = t - time;
        Matrix<float, 9, 9> A = stateTransition(dt);
        state = A * state;
        stateCov = A * stateCov * A.transpose() + dt * processNoiseCovRate;
        time = t;
        return state;
    }

    void accelUpdate(float t, Vector<float, 3> accel) {
        predict(t);
        Matrix<float, 9, 3> K = stateCov * accelObservation.transpose() * (accelObservation * stateCov * accelObservation.transpose() + accelNoiseCov).inverse();
        state = state + K * (accel - accelObservation * state);
        stateCov = (Matrix<float, 9, 9>::Identity() - K * accelObservation) * stateCov * (Matrix<float, 9, 9>::Identity() - K * accelObservation).transpose() + K * accelNoiseCov * K.transpose();
    }

    void GPSUpdate(float t, Vector<float, 3> GPS) {
        predict(t);
        Matrix<float, 9, 3> K = stateCov * GPSObservation.transpose() * (GPSObservation * stateCov * GPSObservation.transpose() + GPSNoiseCov).inverse();
        state = state + K * (GPS - GPSObservation * state);
        stateCov = (Matrix<float, 9, 9>::Identity() - K * GPSObservation) * stateCov * (Matrix<float, 9, 9>::Identity() - K * GPSObservation).transpose() + K * GPSNoiseCov * K.transpose();
    }

    void baroUpdate(float t, float baro) {
        predict(t);
        Matrix<float, 9, 1> K = stateCov * baroObservation.transpose() * (baroObservation * stateCov * baroObservation.transpose() + baroNoiseCov).inverse();
        state = state + K * (baro - baroObservation * state);
        stateCov = (Matrix<float, 9, 9>::Identity() - K * baroObservation) * stateCov * (Matrix<float, 9, 9>::Identity() - K * baroObservation).transpose() + K * baroNoiseCov * K.transpose();
    }
}