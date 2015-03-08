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

#include "test_rcp.h"
#include "test_exp.h"
#include "test_rsqrt.h"


int main() {

    srand(time(NULL));

    int failed_tests = 0;

    failed_tests += test_mm256_rcp_ps();
    failed_tests += test_mm256_rcp1s_ps();
    failed_tests += test_mm256_expfaster_ps();
    failed_tests += test_mm256_expfast_ps();
    failed_tests += test_mm256_expfast1s_ps();
    failed_tests += test_mm256_rsqrt_ps();
    failed_tests += test_mm256_rsqrt1s_ps();

    std::cout << "Number of failed tests: " << failed_tests << std::endl;

    return 0;

}



