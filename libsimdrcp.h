// libsimdrcp -- Approximate RCP(x) implementations for SSE and AVX.
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

#ifndef LIB_SIMD_DIV
#define LIB_SIMD_DIV

#include <immintrin.h>


// Approximation for 1/x -- Newtons method to 1st order
// using an AVX2-intrinsic function as initial guess.
// Speed inbetween _mm256_rcp_ps(x) and _mm256_div_ps(ONE, x).
// Practically same accuracy as _mm256_div_ps(ONE, x).
// Probably the only useful function in this header.
static inline __m256 _mm256_rcp1s_ps(const __m256 &q) {

    const __m256 TWO = _mm256_set1_ps(2.0f);

    __m256 rcp = _mm256_rcp_ps(q);
    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));

    return rcp;

}

// Approximation for 1/x -- Newtons method to 0th order
// Same speed as _mm256_rcp_ps(), but not as accurate
static inline __m256 _mm256_rcp0_ps(const __m256 &q) {

    const __m256 TWO = _mm256_set1_ps(2.0f);
    const __m256i MAGIC_NUMBER = _mm256_set1_epi32(0x7EF311C2);

    __m256i x = _mm256_castps_si256(q);
    x = _mm256_sub_epi32(MAGIC_NUMBER, x);
    __m256 rcp = _mm256_castsi256_ps(x);

    return rcp;

}


// Approximation for 1/x -- Newtons method to 1th order
// Slightly slower than _mm256_rcp_ps(), but not as accurate
static inline __m256 _mm256_rcp1_ps(const __m256 &q) {

    const __m256 TWO = _mm256_set1_ps(2.0f);
    const __m256i MAGIC_NUMBER = _mm256_set1_epi32(0x7EF311C3);

    float temp[8];

    _mm256_store_ps(temp, q);
//    std::cout << "a: " << temp[1] << std::endl;

    __m256i x = _mm256_castps_si256(q);
    x = _mm256_sub_epi32(MAGIC_NUMBER, x);
    __m256 rcp = _mm256_castsi256_ps(x);

    _mm256_store_ps(temp, rcp);
//    std::cout << "b: " << temp[1] << std::endl;


    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));

    return rcp;

}


// Approximation for 1/x -- Newtons method to 2nd order
// Slightly faster than as _mm256_div_ps(ONE, x), but not as accurate
// More accurate than _mm256_rcp_ps()
static inline __m256 _mm256_rcp2_ps(const __m256 &q) {

    const __m256 TWO = _mm256_set1_ps(2.0f);
    const __m256i MAGIC_NUMBER = _mm256_set1_epi32(0x7EF312AC);

    __m256i x = _mm256_castps_si256(q);
    x = _mm256_sub_epi32(MAGIC_NUMBER, x);
    __m256 rcp = _mm256_castsi256_ps(x);

    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));
    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));

    return rcp;

}


// Approximation for 1/x -- Newtons method to 3rd order
// Slower than _mm256_div_ps(ONE, x), and just as accurate
static inline __m256 _mm256_rcp3_ps(const __m256 &q) {

    const __m256 TWO = _mm256_set1_ps(2.0f);
    const __m256i MAGIC_NUMBER = _mm256_set1_epi32(0x7EEEEBB3);

    __m256i x = _mm256_castps_si256(q);
    x = _mm256_sub_epi32(MAGIC_NUMBER, x);
    __m256 rcp = _mm256_castsi256_ps(x);

    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));
    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));
    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));

    return rcp;

}


// Approximation for 1/x -- Newtons method to 4th order
// Much slower than _mm256_div_ps(ONE, x), and just as accurate
static inline __m256 _mm256_rcp4_ps(const __m256 &q) {

    const __m256 TWO = _mm256_set1_ps(2.0f);
    const __m256i MAGIC_NUMBER = _mm256_set1_epi32(0x7EEEEEEE);

    __m256i x = _mm256_castps_si256(q);
    x = _mm256_sub_epi32(MAGIC_NUMBER, x);
    __m256 rcp = _mm256_castsi256_ps(x);

    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));
    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));
    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));
    rcp = _mm256_mul_ps(rcp, _mm256_fnmadd_ps(rcp, q, TWO));

    return rcp;

}


#endif
