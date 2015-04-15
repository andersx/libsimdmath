// libsimdrsqrt -- Approximate RSQRT(x) implementations for Intel AVX.
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


#ifndef INCLUDE_SIMD_RSQRT_H
#define INCLUDE_SIMD_RSQRT_H

#include <immintrin.h>


namespace simdmath {


    // Approximation to 1/sqrt(x) -- accurate to 32-bit precision,
    // but faster than the exact _mm256_div_ps(ONE, _mm256_sqrt_ps(x)).
    // Error is about 0.00002%
    static inline __m256 _mm256_rsqrt1s_ps(const __m256 &q) {

        const __m256 HALF = _mm256_set1_ps(0.5f);
        const __m256 THREE = _mm256_set1_ps(3.0f);

        // Initial guess from intrinsic rsqrt.
        __m256 rsqrt = _mm256_rsqrt_ps(q);

        // Add one iteration of Newton-Raphson.
        return _mm256_mul_ps(HALF, _mm256_mul_ps(rsqrt, 
                    _mm256_fnmadd_ps( _mm256_mul_ps(rsqrt, rsqrt), q, THREE)));

    }


}


#endif // INCLUDE_SIMD_EXP_H
