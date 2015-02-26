libsimd.h
==========

C++ library of fast, approximate math function for Intel AVX.

To compile with gcc, use e.g.

    g++ my_source.cpp -o my_exec -O3 -mfma -mavx -ffast-math


To compile with icpc, use e.g.

    icpc my_source.cpp -o my_exec -O3 -march=core-avx2 -fma


Currently supported functions:
----------


Calculate exp(x) using a bit shifting technique. Extremely fast, but has an error of about 10%.
    __m256 _mm256_expfastsmallneg_psconst __m256 &q()



Calculate exp(x) bit shifting techniques and the Newton-Raphson approximation. Not very fast, but has an error of about 0.0001% or 0.001%, depending on which approximation is used for the reciprocal 1/x.
    __m256 _mm256_expfaster_ps(const __m256 &q)

Calculate 1/x, using one Newton-Raphson iterations on the start guess from the approximate AVX intrinsic _mm256_rcp_ps 
    __m256 _mm256_rcp1s_ps(const __m256 &q)

    __m256 _mm256_print_ps(const __m256 &q)
