/*
 * A speed-improved simplex noise algorithm for 2D, 3D and 4D in C.
 * Ported to C by Bram Stolk.
 *
 * Based on SimplexNoise.java from Stefan Guvstavson, which was:
 * Based on example code by Stefan Gustavson (stegu@itn.liu.se).
 *   Optimisations by Peter Eastman (peastman@drizzle.stanford.edu).
 *   Better rank ordering method by Stefan Gustavson in 2012.
 *
 * This code was placed in the public domain by its original author,
 * Stefan Gustavson. You may use it as you see fit, but
 * attribution is appreciated.
 */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(USEDOUBLES)
typedef double scalar;
#else
typedef float scalar;
#endif

extern void sino_init( void );
extern void sino_exit( void );
extern scalar sino_2d( scalar xin, scalar yin );
extern scalar sino_3d( scalar xin, scalar yin, scalar zin );
extern scalar sino_4d( scalar x, scalar y, scalar z, scalar w );

// two octave version.
extern scalar sino_2d_2o( scalar xin, scalar yin );

// four octave versions.
extern scalar sino_2d_4o( scalar xin, scalar yin );
extern scalar sino_3d_4o( scalar xin, scalar yin, scalar zin );

// Cyclical version for looped animations.
extern int sino_cycle_len;
extern void sino_next_cycle( void );
extern scalar sino_2d_cyclic_2o( scalar xx, scalar yy );
extern scalar sino_3d_cyclic_2o( scalar xx, scalar yy, scalar zz );


#ifdef __cplusplus
}
#endif

