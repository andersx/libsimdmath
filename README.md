libsimd.h
----------

C++ library of fast, approximate math function for Intel AVX.

How to use?
----------
Include the relevant header in your file, e.g.:

    #include "libsimdrcp.h"

You need to enable the relevant compiler flags, see below for GCC and Intel compilers.

To compile with gcc, use e.g.

    g++ my_source.cpp -o my_exec -O3 -mfma -mavx2 -ffast-math

To compile with icpc, use e.g.

    icpc my_source.cpp -o my_exec -O3 -march=core-avx2 -fma


Currently supported functions:
----------

Calculates 1/x, using one Newton-Raphson iterations on the start guess from the approximate AVX intrinsic _mm256_rcp_ps 

    #include "libsimdrcp.h"
    __m256 _mm256_rcp1s_ps(const __m256 &q)
    
Calculates exp(x) using a bit shifting technique. Extremely fast, but has an error of about 10%.

    #include "libsimdexp.h"
    __m256 _mm256_expfaster_ps(const __m256 &q)
    
Only valid for -126 < x < 0.0.  Calculates exp(x) bit shifting techniques and the Newton-Raphson approximation. Not very fast, but has an error of about 0.0001% or 0.001%, depending on which approximation is used for the reciprocal 1/x. If high accuracy is desired, use _mm256_rcp1s_ps() instead of _mm256_rcp_ps().
    
    #include "libsimdexp.h"
    __m256 _mm256_expfastsmallneg_ps(const __m256 &q)

Prints a __m256 vector to std. out.

    #include "libsimdtools.h"
    void _mm256_print_ps(const __m256 &q)
