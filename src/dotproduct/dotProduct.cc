#include <iostream>
#include <math.h>
#include <omp.h>
#if defined (__aarch64__)
#include <arm_neon.h>
#endif
#include "dotProduct.h"

float CPP::dotProduct(const std::vector<float> &v1,
                      const std::vector<float> &v2) {
  size_t size = v1.size();
  float mac = 0.0;

  for (size_t i = 0; i < size; i++) {
    mac += v1[i] * v2[i];
  }

  return mac;
}

float OpenMP::dotProduct(const std::vector<float> &v1,
                         const std::vector<float> &v2) {
  int size = v1.size();
  float mac = 0.0;

  #pragma omp parallel for reduction(+:mac)
  for (int i = 0; i < size; i++) {
    mac += v1[i] * v2[i];
  }

  return mac;
}

#if defined (__aarch64__)
float NEONIntrinsic::dotProduct(const std::vector<float> &v1,
                                const std::vector<float> &v2) {
  float mac = 0;
  size_t size = v1.size();
  float32x4_t v = vdupq_n_f32(0);

  size_t counter = size / 4;
  size_t idx = 0;
  for (size_t i = 0; i < counter; i++) {
    idx = i << 2;
    v = vmlaq_f32(v, vld1q_f32(&v1[idx]), vld1q_f32(&v2[idx]));
  }

  mac += vgetq_lane_f32(v, 0);
  mac += vgetq_lane_f32(v, 1);
  mac += vgetq_lane_f32(v, 2);
  mac += vgetq_lane_f32(v, 3);

  size_t leftover = size % 4;
  for(size_t i = size - leftover; i < size; i++) {
    mac += v1[i] * v2[i];
  }

  return mac;
}

extern "C" {
float dotProductImpl(const std::vector<float> &v1,
                     const std::vector<float> &v2);
}

float NEONAsm::dotProduct(const std::vector<float> &v1,
                          const std::vector<float> &v2) {
  return dotProductImpl(v1, v2);
}

#endif
