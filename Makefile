GXX=g++
ICPC=icpc

GNU_AVX_FLAGS=-O3 -mavx2 -mfma -ffast-math
INTEL_AVX_FLAGS=-O3 -fma -march=core-avx2

all: test-gnu

test-gnu:
	$(GXX) test/test.cpp -o bin/test $(GNU_AVX_FLAGS)
	bin/test

test-intel:
	$(ICPC) test/test.cpp -o bin/test $(INTEL_AVX_FLAGS)
	bin/test

clean:
	@rm bin/test

