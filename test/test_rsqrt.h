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


#ifndef LIB_SIMD_TEST_RSQRT_H
#define LIB_SIMD_TEST_RSQRT_H

#include <iostream>

#include "../include/libsimdrsqrt.h"
#include "../include/libsimdtools.h"
#include "test_common.h"


static int test_mm256_rsqrt_ps() {

    const __m256 ONE = _mm256_set1_ps(1.0f);

    const float accuracy = 0.03f;

    __m256 input = generate_vector(0.0f, 10000.0f);

    __m256 exact = _mm256_div_ps(ONE, _mm256_sqrt_ps(input));
    __m256 approx = _mm256_rsqrt_ps(input);

    std::cout << "Testing: _mm256_rsqrt_ps()      0.0 < x 10000.0" << std::endl;
    return compare_results(input, approx, exact, accuracy);

}



static int test_mm256_rsqrt1s_ps() {

    const __m256 ONE = _mm256_set1_ps(1.0f);

    const float accuracy = 0.00002f;

    __m256 input = generate_vector(0.0f, 10000.0f);

    __m256 exact = _mm256_div_ps(ONE, _mm256_sqrt_ps(input));
    __m256 approx = _mm256_rsqrt1s_ps(input);

    std::cout << "Testing: _mm256_rsqrt1s_ps()      0.0 < x 10000.0" << std::endl;
    return compare_results(input, approx, exact, accuracy);

}

#endif
