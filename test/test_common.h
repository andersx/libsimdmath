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


#ifndef LIB_SIMD_TEST_COMMON_H
#define LIB_SIMD_TEST_COMMON_H

#include <stdlib.h>
#include <cstdlib>

// Lowest guaranteed accuracy of a float in %.
const float FLOAT_ACCURACY = 0.00002f;


float rand_float(float min, float max) {

    return ((max-min)*((float)rand()/RAND_MAX))+min;

}


__m256 generate_vector(float min, float max) {

     return _mm256_set_ps(rand_float(min, max), rand_float(min, max),
                          rand_float(min, max), rand_float(min, max), 
                          rand_float(min, max), rand_float(min, max),
                          rand_float(min, max), rand_float(min, max));

}    


static float compare_results(__m256 input, __m256 approx, 
                             __m256 exact, float accuracy) {

    __m256 error = _mm256_mul_ps(_mm256_set1_ps(100.0f), _mm256_div_ps(approx, exact));


    std::cout << "Random input:" << std::endl; 
    _mm256_print_ps(input);

    std::cout << "Ratio deviation[%]:      Allowed error = " << accuracy << std::endl;
    _mm256_print_ps(error);

    if ((_mm256_maxelement_ps(error) > 100.0f + accuracy) ||
        (_mm256_minelement_ps(error) < 100.0f - accuracy)) {

        std::cout << "FAILED ..." << std::endl;
        std::cout << std::endl;
        _mm256_print_ps(approx);
        _mm256_print_ps(exact);
        return 1;

    } else {

        std::cout << "PASSED ..." << std::endl;
        std::cout << std::endl;
        return 0;

    }

}




#endif // LIB_SIMD_TEST_COMMON_H
