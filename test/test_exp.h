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


#include <iostream>

#include "../include/libsimdexp.h"
#include "../include/libsimdtools.h"
#include "test_common.h"


static int test_mm256_expfaster_ps() {

    const float accuracy = 4.0f;

    __m256 input = generate_vector(-63.0f, 63.0f);

    __m256 approx = _mm256_expfaster_ps(input);
    __m256 exact = _mm256_exp_ps(input);

    std::cout << "Testing: _mm256_expfaster_ps()     -63.0f < x < 63.0" << std::endl;
    return compare_results(input, approx, exact, accuracy);

}


static int test_mm256_expfast_ps() {

    const float accuracy = 0.2;

    __m256 input = generate_vector(-63.0f, 63.0f);

    __m256 approx = _mm256_expfast_ps(input);
    __m256 exact = _mm256_exp_ps(input);

    std::cout << "Testing: _mm256_expfastnegsmall_ps()     -63.0f < x < 63.0" << std::endl;
    return compare_results(input, approx, exact, accuracy);

}


static int test_mm256_expfast1s_ps() {

    const float accuracy = 0.005f;

    __m256 input = generate_vector(-63.0f, 63.0f);

    __m256 approx = _mm256_expfast1s_ps(input);
    __m256 exact = _mm256_exp_ps(input);

    std::cout << "Testing: _mm256_expfastnegsmall1s_ps()     -63.0f < x < 63.0" << std::endl;
    return compare_results(input, approx, exact, accuracy);

}
