
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
	const float f0 = 1.0f / sz;

	sino_next_cycle();

	// Generate a 2d image.
	for ( int y=-sz/2; y<sz/2; ++y )
		for ( int x=-sz/2; x<sz/2; ++x )
		{
			const float ws = sz / 3.0f;
			const scalar warpx = ws * sino_2d_cyclic_2o( 1.5f + x * f0, y * f0 + 3.12345f );
			const scalar warpy = ws * sino_2d_cyclic_2o( 1.5f + x * f0, y * f0 - 4.98765f );
			scalar v = sino_2d_cyclic_2o( 1.5f + (x+warpx) * f0, (y+warpy) * f0 );
			assert(v>=-1 && v<=1);
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

	const int cnt = 300;
	sino_cycle_len = cnt;

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

