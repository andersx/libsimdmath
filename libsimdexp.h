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


// Approximation for EXP(x) -- Taylor expansion to order 6
static inline __m256 _mm256_exptaylor6_ps(const __m256 &q) {

    const __m256 INVLOG_2 = _mm256_set1_ps(1.442695040f);
    const __m256 ONE = _mm256_set1_ps(1.0f);
    const __m256 ONE_OVER_64 = _mm256_set1_ps(0.0156250f);

    p = INVLOG_2 * q;
    p = _mm256_fmadd_ps(p, ONE_OVER_64, ONE);

    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);
    p = _mm256_mul_ps(p, p);

    return _mm256_mul_ps(p, p);
}


// Approximation for EXP(x) -- Taylor expansion to order 8
static inline __m256 _mm256_exptaylor8_ps(const __m256 &q) {

    const __m256 INVLOG_2 = _mm256_set1_ps(1.442695040f);
    const __m256 ONE = _mm256_set1_ps(1.0f);
    const __m256 ONE_OVER_256 = _mm256_set1_ps(0.00390625f);

    p = INVLOG_2 * q;
    p = _mm256_fmadd_ps(p, ONE_OVER_256, ONE);

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
static inline __m256 _mm256_expfaster_ps(const __m256 &q) {

    const __m256 INVLOG_2 = _mm256_set1_ps(1.442695040f);
    const __m256 BIT_SHIFT = _mm256_set1_ps(8388608);

    const __m256 C1 = _mm256_set1_ps(126.94269504f);

    __m256 p = _mm256_fmadd_ps(INVLOG_2, q, C1);
    return _mm256_castsi256_ps(_mm256_cvttps_epi32(_mm256_mul_ps(BIT_SHIFT, p)));
}


// Approximation for EXP(x), only valid for -126.0f < x < 0.0f.
static inline __m256 _mm256_expfastnegsmall_ps(const __m256 &q) {
     
    const __m256 INVLOG_2 = _mm256_set1_ps(1.442695040f);
    const __m256 BIT_SHIFT = _mm256_set1_ps(8388608);
    const __m256 ONE = _mm256_set1_ps(1.0f);
     
    const __m256 C1 = _mm256_set1_ps(121.2740838f);
    const __m256 C2 = _mm256_set1_ps(27.7280233f);
    const __m256 C3 = _mm256_set1_ps(4.84252568f);
    const __m256 C4 = _mm256_set1_ps(1.49012907f);
     
    const __m256 p = _mm256_mul_ps(INVLOG_2, q);
    const __m256 z = _mm256_sub_ps(p, _mm256_floor_ps(p));

    __m256 rcp = _mm256_rcp_ps(_mm256_sub_ps(C3, z));
    // __m256 rcp = _mm256_div_ps(ONE, _mm256_sub_ps(C3, z));
    rcp = _mm256_fmadd_ps(rcp, C2, _mm256_add_ps(C1, p));
    rcp = _mm256_fnmadd_ps(C4, z, rcp);
     
    return _mm256_castsi256_ps(_mm256_cvttps_epi32(_mm256_mul_ps(BIT_SHIFT, rcp)));
     
} 

#endif
