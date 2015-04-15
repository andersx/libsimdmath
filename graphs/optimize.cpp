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


#include <stdio.h>
#include <immintrin.h>
#include <iostream>
#include <math.h> 
#include <time.h> 

#include "../include/simdexp.h"
#include "../include/simdtools.h"
#include "../test/test_common.h"

int main() {

    srand (time(NULL));

    __m256 ONE = _mm256_set1_ps(1.0f);
    __m256 ONE_HUNDRED = _mm256_set1_ps(100.0f);


    // float C1 = 1064872507.1541044f;
    // float C2 = 12102203.161561485f;

    float C1 = 1064870507.1541044f;
    float C2 = 12102000.161561485f;

    unsigned int steps = 100

    for (unsigned int n = 0.0; n < steps; 



    __m256 C1v = _mm256_set1_ps(C1);
    __m256 C2v = _mm256_set1_ps(C2);


    __m256 error_sum = _mm256_set1_ps(0.0f);

    __m256 c = _mm256_set1_ps(0.0f);
    
    for (unsigned int i = 0; i < 10000000; i++) {

        __m256 q = generate_vector(-63.0f, 63.0f);
    
        __m256 approx = _mm256_castsi256_ps(_mm256_cvttps_epi32(_mm256_fmadd_ps(C2v, q, C1v)));
        __m256 exact = _mm256_exp_ps(q);
        
        __m256 error =_mm256_sub_ps(ONE_HUNDRED, _mm256_mul_ps(ONE_HUNDRED, _mm256_div_ps(approx, exact)));
        error = _mm256_mul_ps(error, error);
       
       __m256 y = _mm256_sub_ps(error, c);
       __m256 t = _mm256_add_ps(error_sum, y);
       c =  _mm256_sub_ps(_mm256_sub_ps(t, error_sum), y);
       error_sum = t;


    }

        float tvec[8];
        _mm256_store_ps(tvec, error_sum); 

        float e = tvec[0] + tvec[1] + tvec[2] + tvec[3] + tvec[4] + tvec[5] + tvec[6] + tvec[7];

        std::cout << e << std::endl;


    return 0;

}


