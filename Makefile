CC=clang-8
#CC=gcc

testsino: sino.c testsino.c write_pgm.h
	$(CC) -O3 -Weverything -Wno-missing-braces -ffast-math -std=gnu99 sino.c testsino.c -o testsino -lm

testsino_colour: sino.c testsino_colour.c write_pgm.h
	$(CC) -O3 -Weverything -Wno-missing-braces -ffast-math -std=gnu99 sino.c testsino_colour.c -o testsino_colour -lm

# Test run produces 512 frames of 512x512 pixels that are assembled into an animated gif.
# Each frame is a z-slice through a 3D noise volume.
run: testsino_colour
	perf stat ./testsino_colour 192
	convert -delay 3 -loop -1 out00??.pgm images/anim.gif
	rm -f out????.pgm

images/combined.gif:
	convert -delay 3 -loop -1 combined/out*ppm images/combined.gif


testsimd: testsimd.c sino_3d.ispc sino.c
	ispc -O2 --arch=x86-64 --target=avx2 sino_3d.ispc -o sino_3d_simd.o -h sino_3d_simd.h
	$(CC) -o testsimd testsimd.c sino_3d_simd.o sino.c

runsimd: testsimd
	time ./testsimd 256

clean:
	rm -f *.o
	rm -f sino_3d_simd.h
	rm -f testsino
	rm -f testsimd

