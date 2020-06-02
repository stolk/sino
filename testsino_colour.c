
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sino.h"

#if !defined(BENCHMARK)
#	include "write_pgm.h"
#endif


static void do_frame( int nr, scalar*im, int sz )
{
	scalar* writer = im;

	// Set the frequency
#if 0
	const float f0 = 1.0f / sz * 3;
#else
	const float f0 = 1.0f / 256 * 3;
#endif

	// Pick a z-slice based on the framenr.
	const float z = nr * 0.90f / sz;

	// Generate a 2d image.
	for ( int y=0; y<sz; ++y )
		for ( int x=0; x<sz; ++x )
		{
#if 0
			scalar v = sino_3d_4o( x * f0, y * f0, z );	// -1 .. 1
#elif 0
			scalar ox = sino_3d_4o( x * f0, y * f0,  0 );	// -1 .. 1
			scalar oy = sino_3d_4o( x * f0, y * f0, 13 );	// -1 .. 1
			scalar xx = x + 40*ox;
			scalar yy = y + 40*oy;
			scalar oxx = sino_3d_4o( xx * f0, yy * f0, 26 );
			scalar oyy = sino_3d_4o( xx * f0, yy * f0, 39 );
			scalar xxx = xx + 40*oxx;
			scalar yyy = yy + 40*oyy;
			scalar v = sino_3d_4o( xxx * f0, yyy * f0, z );	// -1 .. 1
#else
			scalar ox = sino_3d( x * f0, y * f0,  0 );	// -1 .. 1
			scalar oy = sino_3d( x * f0, y * f0, 13 );	// -1 .. 1
			scalar xx = x + 40*ox;
			scalar yy = y + 40*oy;
			scalar oxx = sino_3d( xx * f0, yy * f0, 26 );
			scalar oyy = sino_3d( xx * f0, yy * f0, 39 );
			scalar xxx = xx + 40*oxx;
			scalar yyy = yy + 40*oyy;
			scalar v = sino_3d_4o( xxx * f0, yyy * f0, z );	// -1 .. 1
#endif
			*writer++ = ( v + 1.0f ) / ( 2.0f );		//  0 .. 1
		}
}


int main( int argc, char* argv[] )
{
	if ( argc != 2 )
	{
		fprintf( stderr, "Usage: %s imsize\n", argv[ 0 ] );
		exit( 1 );
	}
	int sz = atoi( argv[ 1 ] );
	assert( sz > 0 );
	sino_init();

	const size_t datasz = ( size_t ) ( sz * sz ) * sizeof( scalar );
	scalar* im = (scalar*) malloc( datasz );

	const int cnt = 16;

	for ( int frame=0; frame<cnt; ++frame )
	{
#if !defined(BENCHMARK)
		char fname[128];
		snprintf( fname, sizeof( fname ), "out%04d.ppm", frame );
		FILE* f = fopen( fname, "wb" );
		assert( f );
#endif
		do_frame( frame, im, sz );
#if !defined(BENCHMARK)
		write_ppm( f, im, sz );
		fclose( f );
#endif
	}

	sino_exit();
}

