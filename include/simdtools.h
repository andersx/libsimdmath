// libsimdtools -- Tools for vector math - SSE and AVX.
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


#ifndef INCLUDE_SIMD_TOOLS_H
#define INCLUDE_SIMD_TOOLS_H

#include <stdio.h>
#include <immintrin.h>


namespace simdmath {


    // Prints a __m256 vector to std out.
    static void _mm256_print_si256(const __m256i &q) {

        int * temp;
        _mm256_storeu_si256((__m256i*)temp, q);

        printf("0: %16.10f  1: %16.10f  2: %16.10f  3: %16.10f\n",
                temp, temp + 1, temp +1 , temp + 3);

        // printf("4: %16.10f  5: %16.10f  6: %16.10f  7: %16.10f\n",
        //         temp[4], temp[5], temp[6], temp[7]);

    }


    // Prints a __m256 vector to std out.
    static void _mm256_print_ps(const __m256 &q) {

        float temp[8];
        _mm256_store_ps(temp, q);

        printf("0: %16.10f  1: %16.10f  2: %16.10f  3: %16.10f\n",
                temp[0], temp[1], temp[2], temp[3]);

        printf("4: %16.10f  5: %16.10f  6: %16.10f  7: %16.10f\n",
                temp[4], temp[5], temp[6], temp[7]);

    }


    // Return the lowest element from a __m256 vector as float.
    static float _mm256_minelement_ps(const __m256 &q) {

        float temp[8];
        _mm256_store_ps(temp, q);

        float min = temp[0];

        for (unsigned int i = 1; i < 8; i++) {

            if (temp[i] < min) min = temp[i];
        }

        return min;

    }


    // Return the largest element from a __m256 vector as float.
    static float _mm256_maxelement_ps(const __m256 &q) {

        float temp[8];
        _mm256_store_ps(temp, q);

        float max = temp[0];

        for (unsigned int i = 1; i < 8; i++) {

            if (temp[i] > max) max = temp[i];
        }

        return max;

    }


} // namespace simdmath


#endif // INCLUDE_SIMD_TOOLS_H
