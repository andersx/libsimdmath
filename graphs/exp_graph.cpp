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

#include "../include/simdexp.h"
#include "../include/simdrsqrt.h"
#include "../include/simdtools.h"

int main() {


    __m256 ONE = _mm256_set1_ps(1.0f);
    __m256 ONE_HUNDRED = _mm256_set1_ps(100.0f);

    for (float i = -63.0f; i < 63.0f; i += 0.001f) {


        __m256 t = _mm256_set1_ps(i);

        __m256 rcp = _mm256_mul_ps(ONE_HUNDRED, _mm256_sub_ps(_mm256_div_ps(_mm256_rcp_ps(t), _mm256_div_ps(ONE, t)), ONE));
        __m256 rcp1s = _mm256_mul_ps(ONE_HUNDRED, _mm256_sub_ps(_mm256_div_ps(simdmath::_mm256_rcp1s_ps(t), _mm256_div_ps(ONE, t)), ONE));
        __m256 rsqrt = _mm256_mul_ps(ONE_HUNDRED, _mm256_sub_ps(_mm256_div_ps(_mm256_rsqrt_ps(t), _mm256_div_ps(ONE, _mm256_sqrt_ps(t))), ONE));
        __m256 rsqrt1s = _mm256_mul_ps(ONE_HUNDRED, _mm256_sub_ps(_mm256_div_ps(simdmath::_mm256_rsqrt1s_ps(t), _mm256_div_ps(ONE, _mm256_sqrt_ps(t))), ONE));
        __m256 expfast = _mm256_mul_ps(ONE_HUNDRED, _mm256_sub_ps(_mm256_div_ps(simdmath::_mm256_expfast_ps(t), _mm256_exp_ps(t)), ONE));
        __m256 expfast1s = _mm256_mul_ps(ONE_HUNDRED, _mm256_sub_ps(_mm256_div_ps(simdmath::_mm256_expfast1s_ps(t), _mm256_exp_ps(t)), ONE));
        __m256 expfaster = _mm256_mul_ps(ONE_HUNDRED, _mm256_sub_ps(_mm256_div_ps(simdmath::_mm256_expfaster_ps(t), _mm256_exp_ps(t)), ONE));

        float tvec[8];

        float frcp[8];
        float frcp1s[8];
        float frsqrt[8];
        float frsqrt1s[8];
        float fexpfast[8];
        float fexpfast1s[8];
        float fexpfaster[8];

        _mm256_store_ps(tvec, t); 
        _mm256_store_ps(frcp, rcp);
        _mm256_store_ps(frcp1s, rcp1s);
        _mm256_store_ps(frsqrt, rsqrt);
        _mm256_store_ps(frsqrt1s, rsqrt1s);
        _mm256_store_ps(fexpfast, expfast);
        _mm256_store_ps(fexpfast1s, expfast1s);
        _mm256_store_ps(fexpfaster, expfaster);



        printf("%16.10f %16.10f  %16.10f  %16.10f  %16.10f  %16.10f  %16.10f  %16.10f \n", tvec[0], frcp[0], frcp1s[0],
                frsqrt[0], frsqrt1s[0], fexpfast[0], fexpfast1s[0], fexpfaster[0]);


    }

    return 0;

}


