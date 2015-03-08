GXX=g++
ICPC=icpc

GCC_AVX_FLAGS=-O3 -mavx2 -mfma -ffast-math
INTEL_AVX_FLAGS=-O3 -fma -march=core-avx2

all: test-gnu

test-gcc:
	mkdir -p bin/
	$(GXX) test/test.cpp -o bin/test $(GCC_AVX_FLAGS)
	bin/test

test-intel:
	mkdir -p bin/
	$(ICPC) test/test.cpp -o bin/test $(INTEL_AVX_FLAGS)
	bin/test

clean:
	@rm bin/test

