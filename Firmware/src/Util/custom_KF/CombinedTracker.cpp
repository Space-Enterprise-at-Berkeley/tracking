// Custom KF skeleton implementation.

#include "CombinedTracker.h"

#include <cstring>

namespace {
constexpr float kDefaultNoise[9] = {5.0F, 0.0F, 0.0F, 0.0F, 5.0F,
                                    0.0F, 0.0F, 0.0F, 5.0F};

constexpr float kDefaultGPSModel[27] = {
    1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
};

constexpr float kDefaultAccelModel[27] = {
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F,
};

void PropagateConstAccel(float state[9], float dt)
{
  const float half_dt2 = 0.5F * dt * dt;
  for (int axis = 0; axis < 3; ++axis) {
    const int idx = axis * 3;
    state[idx + 0] += state[idx + 1] * dt + state[idx + 2] * half_dt2;
    state[idx + 1] += state[idx + 2] * dt;
  }
}
} // namespace

namespace kalman_filter {
CombinedTracker *CombinedTracker::init()
{
  Time = 0.0F;
  std::memset(State, 0, sizeof(State));
  std::memcpy(GPSModel, kDefaultGPSModel, sizeof(GPSModel));
  std::memcpy(GPSNoise, kDefaultNoise, sizeof(GPSNoise));
  std::memcpy(AccelModel, kDefaultAccelModel, sizeof(AccelModel));
  std::memcpy(AccelNoise, kDefaultNoise, sizeof(AccelNoise));

  Filter = coder_buffer_pobj0.init(State);
  return this;
}

void CombinedTracker::setNoises(const float ProcessNoise[9],
                                const float b_GPSNoise[9],
                                const float b_AccelNoise[9])
{
  if (Filter != nullptr) {
    Filter->set_ProcessNoise(ProcessNoise);
  }
  std::memcpy(GPSNoise, b_GPSNoise, sizeof(GPSNoise));
  std::memcpy(AccelNoise, b_AccelNoise, sizeof(AccelNoise));
}

void CombinedTracker::GPSUpdate(float b_time, const float b_value[3])
{
  if (Filter == nullptr) {
    return;
  }

  std::memcpy(Filter->pMeasurementModel, GPSModel,
              sizeof(Filter->pMeasurementModel));
  Filter->set_MeasurementNoise(GPSNoise);
  Filter->predict(b_time - Time);
  Filter->correct(b_value);
  Time = b_time;
  std::memcpy(State, Filter->pState, sizeof(State));
}

void CombinedTracker::accelUpdate(float b_time, const float b_value[3])
{
  if (Filter == nullptr) {
    return;
  }

  std::memcpy(Filter->pMeasurementModel, AccelModel,
              sizeof(Filter->pMeasurementModel));
  Filter->set_MeasurementNoise(AccelNoise);
  Filter->predict(b_time - Time);
  Filter->correct(b_value);
  Time = b_time;
  std::memcpy(State, Filter->pState, sizeof(State));
}

void CombinedTracker::extrapolate(float b_time, float state[9]) const
{
  std::memcpy(state, State, sizeof(State));
  PropagateConstAccel(state, b_time - Time);
}
} // namespace kalman_filter
