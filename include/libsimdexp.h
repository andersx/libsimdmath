// libsimdexp -- Approximate EXP(x) implementations for SSE and AVX.
// Copyright (C) 2015 Anders S. Christensen
// Report bugs, etc at: https://github.com/andersx/simd-exp
//
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org>

#ifndef LIB_SIMD_EXP
#define LIB_SIMD_EXP

#include <immintrin.h>
#include <math.h>
#include "libsimdrcp.h"


// Approximation for EXP(x) -- Taylor expansion to order N
static inline __m256 _mm256_exptaylorn_ps(const __m256 &q,
                                          const unsigned int n) {

    const __m256 ONE = _mm256_set1_ps(1.0f);
    const __m256 ONE_OVER_EXP2N = _mm256_set1_ps(1.0f/exp2(n));

    __m256 p = _mm256_fmadd_ps(q, ONE_OVER_EXP2N, ONE);

    for (unsigned int i = 0; i < n; i++) {

        p = _mm256_mul_ps(p, p);

    }

    return p;
}


// Approximation for EXP(x) -- Taylor expansion to order 2
static inline __m256 _mm256_exptaylor2_ps(const __m256 &q) {

    const __m256 ONE = _mm256_set1_ps(1.0f);
    const __m256 ONE_OVER_4 = _mm256_set1_ps(0.25f);

    __m256 p = _mm256_fmadd_ps(q, ONE_OVER_4, ONE);

    p = _mm256_mul_ps(p, p);

    return _mm256_mul_ps(p, p);
}


// Approximation for EXP(x) -- Taylor expansion to order 4
static inline __m256 _mm256_exptaylor4_ps(const __m256 &q) {

    const __m256 ONE = _mm256_set1_ps(1.0f);
    const __m256 ONE_OVER_16 = _mm256_set1_ps(0.0625f);

    __m256 p = _mm256_fmadd_ps(q, ONE_OVER_16, ONE);

    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);

    return _mm256_mul_ps(p, p);
}


// Approximation for EXP(x) -- Taylor expansion to order 6
static inline __m256 _mm256_exptaylor6_ps(const __m256 &q) {

    const __m256 ONE = _mm256_set1_ps(1.0f);
    const __m256 ONE_OVER_64 = _mm256_set1_ps(0.0156250f);

    __m256 p = _mm256_fmadd_ps(q, ONE_OVER_64, ONE);

    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);

    return _mm256_mul_ps(p, p);
}


// Approximation for EXP(x) -- Taylor expansion to order 8
static inline __m256 _mm256_exptaylor8_ps(const __m256 &q) {

    const __m256 ONE = _mm256_set1_ps(1.0f);
    const __m256 ONE_OVER_256 = _mm256_set1_ps(0.00390625f);

    __m256 p = _mm256_fmadd_ps(q, ONE_OVER_256, ONE);

    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);

    return _mm256_mul_ps(p, p);
}


// Approximation for EXP(x) -- very fast, but not super accurate
// Error is about 
static inline __m256 _mm256_expfaster_ps(const __m256 &q) {

    const __m256 C1 = _mm256_set1_ps(1064872507.1541044f);
    const __m256 C2 = _mm256_set1_ps(12102203.161561485f);

    return _mm256_castsi256_ps(_mm256_cvttps_epi32(_mm256_fmadd_ps(C2, q, C1)));
}


// Approximation for EXP(x), only valid for -126.0f < x < 0.0f.
// Error is about 0.05%
static inline __m256 _mm256_expfast_ps(const __m256 &q) {

    const __m256 INVLOG_2 = _mm256_set1_ps(1.442695040f);
    const __m256 BIT_SHIFT = _mm256_set1_ps(8388608);

    const __m256 C1 = _mm256_set1_ps(121.2740838f);
    const __m256 C2 = _mm256_set1_ps(27.7280233f);
    const __m256 C3 = _mm256_set1_ps(4.84252568f);
    const __m256 C4 = _mm256_set1_ps(1.49012907f);

    const __m256 p = _mm256_mul_ps(INVLOG_2, q);
    const __m256 z = _mm256_sub_ps(p, _mm256_floor_ps(p));

    __m256 rcp = _mm256_rcp_ps(_mm256_sub_ps(C3, z));
    rcp = _mm256_fmadd_ps(rcp, C2, _mm256_add_ps(C1, p));
    rcp = _mm256_fnmadd_ps(C4, z, rcp);

    return _mm256_castsi256_ps(_mm256_cvttps_epi32(_mm256_mul_ps(BIT_SHIFT, rcp)));

}


// Approximation for EXP(x), only valid for -126.0f < x < 0.0f.
// Error is about 0.001%
static inline __m256 _mm256_expfast1s_ps(const __m256 &q) {

    const __m256 INVLOG_2 = _mm256_set1_ps(1.442695040f);
    const __m256 BIT_SHIFT = _mm256_set1_ps(8388608);

    const __m256 C1 = _mm256_set1_ps(121.2740838f);
    const __m256 C2 = _mm256_set1_ps(27.7280233f);
    const __m256 C3 = _mm256_set1_ps(4.84252568f);
    const __m256 C4 = _mm256_set1_ps(1.49012907f);

    const __m256 p = _mm256_mul_ps(INVLOG_2, q);
    const __m256 z = _mm256_sub_ps(p, _mm256_floor_ps(p));

    __m256 rcp = _mm256_rcp1s_ps(_mm256_sub_ps(C3, z));
    rcp = _mm256_fmadd_ps(rcp, C2, _mm256_add_ps(C1, p));
    rcp = _mm256_fnmadd_ps(C4, z, rcp);

    return _mm256_castsi256_ps(_mm256_cvttps_epi32(_mm256_mul_ps(BIT_SHIFT, rcp)));

}


#endif
