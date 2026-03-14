// Custom KF skeleton implementation.

#include "trackingKF.h"

#include <algorithm>
#include <cstring>

namespace {
void SetIdentity(float *mat, int n)
{
  const int count = n * n;
  std::fill(mat, mat + count, 0.0F);
  for (int i = 0; i < n; ++i) {
    mat[i + n * i] = 1.0F;
  }
}

void SetDefaultMeasurementModel(float model[27])
{
  std::fill(model, model + 27, 0.0F);
  model[0] = 1.0F;   // row 0, col 0  -> measure x
  model[10] = 1.0F;  // row 1, col 3  -> measure y
  model[20] = 1.0F;  // row 2, col 6  -> measure z
}

void PropagateState(float state[9], float dt)
{
  const float half_dt2 = 0.5F * dt * dt;
  for (int axis = 0; axis < 3; ++axis) {
    const int idx = axis * 3;
    state[idx + 0] += state[idx + 1] * dt + state[idx + 2] * half_dt2;
    state[idx + 1] += state[idx + 2] * dt;
  }
}

// Standard inversion algorithm for 3x3 matricies -- used for the KF algorithm. Maybe replace with faster impl. 
bool Invert3x3(const float m[9], float inv[9])
{
  const float a = m[0];
  const float b = m[3];
  const float c = m[6];
  const float d = m[1];
  const float e = m[4];
  const float f = m[7];
  const float g = m[2];
  const float h = m[5];
  const float i = m[8];

  const float A = (e * i - f * h);
  const float B = (d * i - f * g);
  const float C = (d * h - e * g);
  const float det = a * A - b * B + c * C;

  const float eps = 1.0e-6F;
  if (det > -eps && det < eps) {
    return false;
  }
  const float inv_det = 1.0F / det;

  const float inv00 = A * inv_det;
  const float inv01 = (c * h - b * i) * inv_det;
  const float inv02 = (b * f - c * e) * inv_det;
  const float inv10 = (f * g - d * i) * inv_det;
  const float inv11 = (a * i - c * g) * inv_det;
  const float inv12 = (c * d - a * f) * inv_det;
  const float inv20 = C * inv_det;
  const float inv21 = (b * g - a * h) * inv_det;
  const float inv22 = (a * e - b * d) * inv_det;

  inv[0] = inv00;
  inv[3] = inv01;
  inv[6] = inv02;
  inv[1] = inv10;
  inv[4] = inv11;
  inv[7] = inv12;
  inv[2] = inv20;
  inv[5] = inv21;
  inv[8] = inv22;
  return true;
}
} // namespace

namespace kalman_filter {

trackingKF *trackingKF::init(const float varargin_4[9])
{

  SetIdentity(StateTransitionModel, 9);
  std::memcpy(pState, varargin_4, sizeof(pState));
  SetIdentity(pStateCovariance, 9);

  std::fill(ProcessNoiseModel, ProcessNoiseModel + 27, 0.0F);
  pN = 3.0F;
  pV = 3.0F;
  std::fill(pProcessNoise, pProcessNoise + 9, 0.0F);
  std::fill(pMeasurementNoise, pMeasurementNoise + 9, 0.0F);
  SetDefaultMeasurementModel(pMeasurementModel);

  return this;
}

void trackingKF::set_ProcessNoise(const float b_value[9])
{
  std::memcpy(pProcessNoise, b_value, sizeof(pProcessNoise));
}

void trackingKF::set_MeasurementNoise(const float b_value[9])
{
  std::memcpy(pMeasurementNoise, b_value, sizeof(pMeasurementNoise));
}

void trackingKF::predict(float varargin_1)
{
  const float dt = varargin_1;
  const float half_dt2 = 0.5F * dt * dt;

  // 3x3 constant-acceleration block (column-major).
  float A1[9] = {
      1.0F, 0.0F, 0.0F,
      dt,   1.0F, 0.0F,
      half_dt2, dt, 1.0F,
  };
  float G1[3] = {half_dt2, dt, 1.0F};

  // Build block-diagonal state transition and process-noise model.
  std::fill(StateTransitionModel, StateTransitionModel + 81, 0.0F);
  std::fill(ProcessNoiseModel, ProcessNoiseModel + 27, 0.0F);
  for (int axis = 0; axis < 3; ++axis) {
    const int block = 3 * axis;
    for (int col = 0; col < 3; ++col) {
      for (int row = 0; row < 3; ++row) {
        StateTransitionModel[(row + block) + 9 * (col + block)] =
            A1[row + 3 * col];
      }
    }
    for (int row = 0; row < 3; ++row) {
      ProcessNoiseModel[(row + block) + 9 * axis] = G1[row];
    }
  }

  // AP = A * P
  float AP[81];
  std::fill(AP, AP + 81, 0.0F);
  for (int col = 0; col < 9; ++col) {
    for (int k = 0; k < 9; ++k) {
      const float p = pStateCovariance[k + 9 * col];
      for (int row = 0; row < 9; ++row) {
        AP[row + 9 * col] += StateTransitionModel[row + 9 * k] * p;
      }
    }
  }

  // P = AP * A^T
  float P[81];
  std::fill(P, P + 81, 0.0F);
  for (int col = 0; col < 9; ++col) {
    for (int k = 0; k < 9; ++k) {
      const float a = StateTransitionModel[col + 9 * k];
      for (int row = 0; row < 9; ++row) {
        P[row + 9 * col] += AP[row + 9 * k] * a;
      }
    }
  }

  // GQ = G * Q
  float GQ[27];
  std::fill(GQ, GQ + 27, 0.0F);
  for (int col = 0; col < 3; ++col) {
    for (int k = 0; k < 3; ++k) {
      const float q = pProcessNoise[k + 3 * col];
      for (int row = 0; row < 9; ++row) {
        GQ[row + 9 * col] += ProcessNoiseModel[row + 9 * k] * q;
      }
    }
  }

  // GQG^T
  float GQGt[81];
  std::fill(GQGt, GQGt + 81, 0.0F);
  for (int col = 0; col < 9; ++col) {
    for (int k = 0; k < 3; ++k) {
      const float g = ProcessNoiseModel[col + 9 * k];
      for (int row = 0; row < 9; ++row) {
        GQGt[row + 9 * col] += GQ[row + 9 * k] * g;
      }
    }
  }

  for (int i = 0; i < 81; ++i) {
    P[i] += GQGt[i];
  }

  // x = A * x
  float new_state[9] = {0.0F};
  for (int col = 0; col < 9; ++col) {
    const float s = pState[col];
    for (int row = 0; row < 9; ++row) {
      new_state[row] += StateTransitionModel[row + 9 * col] * s;
    }
  }

  for (int i = 0; i < 9; ++i) {
    pState[i] = new_state[i];
  }
  for (int col = 0; col < 9; ++col) {
    for (int row = 0; row < 9; ++row) {
      pStateCovariance[row + 9 * col] =
          0.5F * (P[row + 9 * col] + P[col + 9 * row]);
    }
  }

}

void trackingKF::correct(const float z[3])
{
  // Innovation y = z - Hx
  float hx[3] = {0.0F, 0.0F, 0.0F};
  for (int col = 0; col < 9; ++col) {
    const float x = pState[col];
    for (int row = 0; row < 3; ++row) {
      hx[row] += pMeasurementModel[row + 3 * col] * x;
    }
  }
  float y[3] = {z[0] - hx[0], z[1] - hx[1], z[2] - hx[2]};

  // PHt = P * H^T (9x3)
  float PHt[27];
  std::fill(PHt, PHt + 27, 0.0F);
  for (int col = 0; col < 3; ++col) {
    for (int k = 0; k < 9; ++k) {
      const float h = pMeasurementModel[col + 3 * k];
      for (int row = 0; row < 9; ++row) {
        PHt[row + 9 * col] += pStateCovariance[row + 9 * k] * h;
      }
    }
  }

  // S = H * PHt + R (3x3)
  float S[9];
  std::fill(S, S + 9, 0.0F);
  for (int col = 0; col < 3; ++col) {
    for (int k = 0; k < 9; ++k) {
      for (int row = 0; row < 3; ++row) {
        S[row + 3 * col] += pMeasurementModel[row + 3 * k] * PHt[k + 9 * col];
      }
    }
  }
  for (int i = 0; i < 9; ++i) {
    S[i] += pMeasurementNoise[i];
  }

  float invS[9];
  if (!Invert3x3(S, invS)) {
    return;
  }

  // K = PHt * invS (9x3)
  float K[27];
  std::fill(K, K + 27, 0.0F);
  for (int col = 0; col < 3; ++col) {
    for (int k = 0; k < 3; ++k) {
      const float s = invS[k + 3 * col];
      for (int row = 0; row < 9; ++row) {
        K[row + 9 * col] += PHt[row + 9 * k] * s;
      }
    }
  }

  // x = x + K * y
  for (int row = 0; row < 9; ++row) {
    pState[row] += K[row] * y[0] + K[row + 9] * y[1] + K[row + 18] * y[2];
  }

  // HP = H * P (3x9)
  float HP[27];
  std::fill(HP, HP + 27, 0.0F);
  for (int col = 0; col < 9; ++col) {
    for (int k = 0; k < 9; ++k) {
      const float p = pStateCovariance[k + 9 * col];
      for (int row = 0; row < 3; ++row) {
        HP[row + 3 * col] += pMeasurementModel[row + 3 * k] * p;
      }
    }
  }

  // P = P - K * HP
  for (int col = 0; col < 9; ++col) {
    for (int row = 0; row < 9; ++row) {
      float corr = 0.0F;
      for (int k = 0; k < 3; ++k) {
        corr += K[row + 9 * k] * HP[k + 3 * col];
      }
      pStateCovariance[row + 9 * col] -= corr;
    }
  }

  // Symmetrize covariance.
  for (int col = 0; col < 9; ++col) {
    for (int row = 0; row < 9; ++row) {
      const float v =
          0.5F * (pStateCovariance[row + 9 * col] +
                  pStateCovariance[col + 9 * row]);
      pStateCovariance[row + 9 * col] = v;
    }
  }

}

} // namespace kalman_filter
