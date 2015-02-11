# simd-exp
C++ library of approximations to exp(x) for SSE and AVX2.

To compile with gcc, use e.g.

    g++ my_source.cpp -o my_exec -O3 -mfma -mavx -ffast-math


To compile with icpc, use e.g.

    g++ my_source.cpp -o my_exec -O3 -avx

