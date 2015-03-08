// Test cases for libsimdrsqrt
// Report bugs, etc at: https://github.com/andersx/simd-exp
//
// The MIT License (MIT)
// 
// Copyright (C) 2015 Anders S. Christensen
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#ifndef LIB_SIMD_TEST_RSQRT_H
#define LIB_SIMD_TEST_RSQRT_H

#include <iostream>

#include "../include/libsimdrsqrt.h"
#include "../include/libsimdtools.h"
#include "test_common.h"


// Test case for the intrinsic function _mm256_rsqrt_ps()
static int test_mm256_rsqrt_ps() {

    // Target accuracy
    const float accuracy = 0.03f;

    // Random input data
    __m256 input = generate_vector(0.0f, 10000.0f);

    // Exact value of 1/sqrt(x)
    __m256 exact = _mm256_div_ps(_mm256_set1_ps(1.0f), _mm256_sqrt_ps(input));

    // Approximate value of 1/sqrt(x)
    __m256 approx = _mm256_rsqrt_ps(input);

    // Print and run test
    std::cout << "Testing: _mm256_rsqrt_ps()      0.0 < x 10000.0" << std::endl;
    return compare_results(input, approx, exact, accuracy);

}


// Test case for the function _mm256_rsqrt1s_ps()
static int test_mm256_rsqrt1s_ps() {

    // Target accuracy
    const float accuracy = FLOAT_ACCURACY;

    // Random input data
    __m256 input = generate_vector(0.0f, 10000.0f);

    // Exact value of 1/sqrt(x)
    __m256 exact = _mm256_div_ps(_mm256_set1_ps(1.0f), _mm256_sqrt_ps(input));

    // Approximate value of 1/sqrt(x)
    __m256 approx = _mm256_rsqrt1s_ps(input);

    // Print and run test
    std::cout << "Testing: _mm256_rsqrt1s_ps()      0.0 < x 10000.0" << std::endl;
    return compare_results(input, approx, exact, accuracy);

}


#endif // LIB_SIMD_TEST_COMMON_H
