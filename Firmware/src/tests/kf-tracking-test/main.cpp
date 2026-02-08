#include <Arduino.h>
#include <Common.h>
#include <algorithm>
#include <cmath>
#include <cstring>

#include "Util/codegen_KF/trackingKF.h"
#include "Util/custom_KF/trackingKF.h"

namespace {
uint32_t LcgNext(uint32_t &state)
{
  state = state * 1664525u + 1013904223u;
  return state;
}

float RandRange(uint32_t &state, float min_val, float max_val)
{
  const float t = static_cast<float>(LcgNext(state)) / 4294967295.0F;
  return min_val + (max_val - min_val) * t;
}

void FillState(uint32_t &rng, float scale, float state[9])
{
  for (int i = 0; i < 9; ++i) {
    state[i] = RandRange(rng, -scale, scale);
  }
}

void FillDiagNoise(uint32_t &rng, float min_val, float max_val, float noise[9])
{
  std::memset(noise, 0, 9 * sizeof(float));
  noise[0] = RandRange(rng, min_val, max_val);
  noise[4] = RandRange(rng, min_val, max_val);
  noise[8] = RandRange(rng, min_val, max_val);
}

bool CompareArrays(const float *a, const float *b, int count, float tol,
                   float &max_err)
{
  max_err = 0.0F;
  for (int i = 0; i < count; ++i) {
    const float err = std::fabs(a[i] - b[i]);
    if (err > max_err) {
      max_err = err;
    }
    if (err > tol) {
      return false;
    }
  }
  return true;
}

bool RunRandomizedTest(int cases, uint32_t seed, float tol_state,
                       float tol_cov, float &worst_state, float &worst_cov)
{
  worst_state = 0.0F;
  worst_cov = 0.0F;
  for (int c = 0; c < cases; ++c) {
    uint32_t rng = seed + static_cast<uint32_t>(c) * 17u;
    float init_state[9];
    FillState(rng, 200.0F, init_state);

    coder::trackingKF ref;
    kalman_filter::trackingKF dut;
    ref.init(init_state);
    dut.init(init_state);

    float process_noise[9];
    float meas_noise[9];
    FillDiagNoise(rng, 1.0e-4F, 5.0F, process_noise);
    FillDiagNoise(rng, 1.0e-4F, 5.0F, meas_noise);

    ref.set_ProcessNoise(process_noise);
    dut.set_ProcessNoise(process_noise);
    ref.set_MeasurementNoise(meas_noise);
    dut.set_MeasurementNoise(meas_noise);

    for (int step = 0; step < 5; ++step) {
      const float dt = RandRange(rng, 0.0F, 2.0F);
      ref.predict(dt);
      dut.predict(dt);

      float meas[3];
      meas[0] = RandRange(rng, -300.0F, 300.0F);
      meas[1] = RandRange(rng, -300.0F, 300.0F);
      meas[2] = RandRange(rng, -300.0F, 300.0F);
      ref.correct(meas);
      dut.correct(meas);
    }

    float max_err = 0.0F;
    if (!CompareArrays(ref.pState, dut.pState, 9, tol_state, max_err)) {
      worst_state = std::max(worst_state, max_err);
      Serial.print("State mismatch case ");
      Serial.println(c);
      return false;
    }
    worst_state = std::max(worst_state, max_err);

    if (!CompareArrays(ref.pStateCovariance, dut.pStateCovariance, 81, tol_cov,
                       max_err)) {
      worst_cov = std::max(worst_cov, max_err);
      Serial.print("Cov mismatch case ");
      Serial.println(c);
      return false;
    }
    worst_cov = std::max(worst_cov, max_err);
  }
  return true;
}

bool RunEdgeCase(const char *name, float dt, float state_scale,
                 float noise_scale, float tol_state, float tol_cov)
{
  uint32_t rng = 0xC0FFEEu;
  float init_state[9];
  FillState(rng, state_scale, init_state);

  coder::trackingKF ref;
  kalman_filter::trackingKF dut;
  ref.init(init_state);
  dut.init(init_state);

  float process_noise[9] = {noise_scale, 0.0F, 0.0F,
                            0.0F, noise_scale, 0.0F,
                            0.0F, 0.0F, noise_scale};
  float meas_noise[9] = {noise_scale, 0.0F, 0.0F,
                         0.0F, noise_scale, 0.0F,
                         0.0F, 0.0F, noise_scale};
  ref.set_ProcessNoise(process_noise);
  dut.set_ProcessNoise(process_noise);
  ref.set_MeasurementNoise(meas_noise);
  dut.set_MeasurementNoise(meas_noise);

  ref.predict(dt);
  dut.predict(dt);

  float meas[3] = {state_scale * 0.25F, -state_scale * 0.5F,
                   state_scale * 0.75F};
  ref.correct(meas);
  dut.correct(meas);

  float max_err = 0.0F;
  if (!CompareArrays(ref.pState, dut.pState, 9, tol_state, max_err)) {
    Serial.print("Edge state mismatch: ");
    Serial.println(name);
    return false;
  }
  if (!CompareArrays(ref.pStateCovariance, dut.pStateCovariance, 81, tol_cov,
                     max_err)) {
    Serial.print("Edge cov mismatch: ");
    Serial.println(name);
    return false;
  }
  return true;
}
} // namespace

void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {
    delay(10);
  }

  Serial.println("KF compare tests");

  float worst_state = 0.0F;
  float worst_cov = 0.0F;
  bool ok = true;

  ok &= RunRandomizedTest(200, 0x12345678u, 1.0e-2F, 1.0e-2F, worst_state,
                          worst_cov);
  ok &= RunEdgeCase("dt=0", 0.0F, 100.0F, 1.0F, 1.0e-3F, 1.0e-3F);
  ok &= RunEdgeCase("dt=1e-4", 1.0e-4F, 100.0F, 1.0F, 1.0e-3F, 1.0e-3F);
  ok &= RunEdgeCase("dt=-0.05", -0.05F, 100.0F, 1.0F, 1.0e-3F, 1.0e-3F);
  ok &= RunEdgeCase("dt=25", 25.0F, 100.0F, 5.0F, 1.0e-1F, 1.0e-1F);
  ok &= RunEdgeCase("large state", 0.5F, 10000.0F, 10.0F, 1.0e-1F, 1.0e-1F);
  ok &= RunEdgeCase("small noise", 0.5F, 100.0F, 1.0e-5F, 1.0e-2F, 1.0e-2F);

  if (ok) {
    Serial.println("ALL TESTS PASSED");
  } else {
    Serial.println("TESTS FAILED");
  }

  Serial.print("Worst state error: ");
  Serial.println(worst_state, 6);
  Serial.print("Worst cov error: ");
  Serial.println(worst_cov, 6);
}

void loop()
{
  delay(1000);
}
