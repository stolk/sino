#sino - a Simplex Noise implementation in C.

This is a C-port of the [OpenSimplex.java code by Stefan Gustavson](http://webstaff.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java).

In sino.h you can typedef scalar to float or double.
For me, the double version is significantly faster, I am not sure why. (64 bit clang on x86 linux.)

![Slice to 3d noise field with 4 octaves.](images/anim.gif "Slice through 3d noise field with 4 octaves.")

