

testsino: sino.c testsino.c
	clang-3.5 -O3 -Wall -Wno-missing-braces -ffast-math -std=gnu99 sino.c testsino.c -o testsino


# Test run produces 512 frames of 512x512 pixels that are assembled into an animated gif.
# Each frame is a z-slice through a 3D noise volume.
run: testsino
	time ./testsino 200
	convert -delay 3 -loop 0 out????.pgm images/anim.gif


