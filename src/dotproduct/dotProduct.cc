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

float CPPOMP::dotProduct(const std::vector<float> &v1,
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
   size_t leftover = size % 4;
   float32x4_t ret = vdupq_n_f32(0);

   // NEON optimization: handle 4 float numbers at a time
   for (size_t i = 0; i < size / 4; ++i) {
       float32x4_t tmp1 = vld1q_f32(&v1[4 * i]);
       float32x4_t tmp2 = vld1q_f32(&v2[4 * i]);
       ret = vmlaq_f32(ret, tmp1, tmp2);
   }

   mac += vgetq_lane_f32(ret, 0);
   mac += vgetq_lane_f32(ret, 1);
   mac += vgetq_lane_f32(ret, 2);
   mac += vgetq_lane_f32(ret, 3);

   // handle the leftover in the vectors
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
