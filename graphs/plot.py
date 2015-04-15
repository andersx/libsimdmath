from matplotlib import pyplot
import numpy

f = open("data.txt", "r")
lines = f.readlines()
f.close()


n = len(lines)

tvec = numpy.empty(n)
rcp = numpy.empty(n)
rcp1s = numpy.empty(n)
rsqrt = numpy.empty(n)
rsqrt1s = numpy.empty(n)
fast = numpy.empty(n)
fast1s = numpy.empty(n)
faster = numpy.empty(n)


for i, line in enumerate(lines):

    tokens = line.split()

    tvec[i] = float(tokens[0])

    rcp[i] = float(tokens[1])
    rcp1s[i] = float(tokens[2])
    rsqrt[i] = float(tokens[3])
    rsqrt1s[i] = float(tokens[4])
    fast[i] = float(tokens[5])
    fast1s[i] = float(tokens[6])
    faster[i] = float(tokens[7])


x_min = -4.0
x_max = 4.0

pyplot.figure(figsize=[24,13.5])

cols = 4
rows = 2

pyplot.subplot(rows,cols,1)
pyplot.plot(tvec, rcp)
pyplot.xlim([x_min, x_max])
pyplot.title("_mm256_rcp_ps()")
pyplot.xlabel("x")
pyplot.ylabel("1.0f/x error [%]")
pyplot.grid(True)


pyplot.subplot(rows,cols,2)
pyplot.plot(tvec, rcp1s)
pyplot.xlim([x_min, x_max])
pyplot.title("simdmath::_mm256_rcp1s_ps()")
pyplot.xlabel("x")
pyplot.ylabel("1.0f/x error [%]")
pyplot.grid(True)


pyplot.subplot(rows,cols,3)
pyplot.plot(tvec, rsqrt)
pyplot.xlim([0.0, x_max*2])
pyplot.title("_mm256_rsqrt_ps()")
pyplot.xlabel("x")
pyplot.ylabel("1.0f/sqrt(x) error [%]")
pyplot.grid(True)


pyplot.subplot(rows,cols,4)
pyplot.plot(tvec, rsqrt1s)
pyplot.xlim([0.0, x_max*2])
pyplot.title("simdmath::_mm256_rsqrt1s_ps()")
pyplot.xlabel("x")
pyplot.ylabel("1.0f/sqrt(x) error [%]")
pyplot.grid(True)


pyplot.subplot(rows,cols,5)
pyplot.plot(tvec, fast)
pyplot.xlim([x_min, x_max])
pyplot.title("simdmath::_mm256_expfast_ps()")
pyplot.xlabel("x")
pyplot.ylabel("exp(x) error [%]")
pyplot.grid(True)


pyplot.subplot(rows,cols,6)
pyplot.plot(tvec, fast1s)
pyplot.xlim([x_min, x_max])
pyplot.title("simdmath::_mm256_expfast1s_ps()")
pyplot.xlabel("x")
pyplot.ylabel("exp(x) error [%]")
pyplot.grid(True)


pyplot.subplot(rows,cols,7)
pyplot.plot(tvec, faster)
pyplot.xlim([x_min, x_max])
pyplot.title("simdmath::_mm256_expfaster_ps()")
pyplot.xlabel("x")
pyplot.ylabel("exp(x) error [%]")
pyplot.grid(True)


pyplot.savefig("graph.png")
