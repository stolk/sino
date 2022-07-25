CC=clang-13
#CC=gcc


testsino: sino.c testsino.c write_pgm.h
	$(CC) -O2 -Wall -Wno-missing-braces -ffast-math -std=gnu99 sino.c testsino.c -o testsino -lm

flowtest: sino.c flowtest.c
	$(CC) -O2 -Wall -Wno-missing-braces -ffast-math -std=gnu99 sino.c flowtest.c -o flowtest -lm

flowtest3d: sino.c flowtest3d.c
	$(CC) -O2 -Wall -Wno-missing-braces -ffast-math -std=gnu99 sino.c flowtest3d.c -o flowtest3d -lm


testsino_colour: sino.c testsino_colour.c write_pgm.h
	$(CC) -O2 -Wall -Wno-missing-braces -ffast-math -std=gnu99 sino.c testsino_colour.c -o testsino_colour -lm

testsino_cyclic: sino.c testsino_cyclic.c write_pgm.h
	$(CC) -O2 -Wall -Wno-missing-braces -ffast-math -std=gnu99 sino.c testsino_cyclic.c -o testsino_cyclic -lm

run: testsino_cyclic
	./testsino_cyclic 192
	convert -delay 3 -loop -1 out00??.ppm images/cyclic.gif

# Test run produces 512 frames of 512x512 pixels that are assembled into an animated gif.
# Each frame is a z-slice through a 3D noise volume.
runcolour: testsino_colour
	perf stat ./testsino_colour 192
	convert -delay 3 -loop -1 out00??.ppm images/anim.gif
	rm -f out????.pgm

images/combined.gif:
	convert -delay 3 -loop -1 combined/out*ppm images/combined.gif


testsimd: testsimd.c sino_3d.ispc sino.c
	ispc -O2 --arch=x86-64 --target=avx2 sino_3d.ispc -o sino_3d_simd.o -h sino_3d_simd.h
	$(CC) -o testsimd testsimd.c sino_3d_simd.o sino.c

runsimd: testsimd
	time ./testsimd 256

flow: flowtest
	./flowtest out.svg
	inkscape out.svg

flow3d: flowtest3d
	./flowtest3d lines.bin
	cp lines.bin $(HOME)/apps/GIB/viewer/data/

clean:
	rm -f *.o
	rm -f sino_3d_simd.h
	rm -f testsino
	rm -f testsimd

