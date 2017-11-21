
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sino.h"
#include "write_pgm.h"


static void do_frame( int nr, scalar*im, int sz )
{
	scalar* writer = im;

	// Set the frequency
	const float f0 = 1.0f / sz * 3;

	// Pick a z-slice based on the framenr.
	const float z = nr * 0.90f / sz;

	// Generate a 2d image.
	for ( int y=0; y<sz; ++y )
		for ( int x=0; x<sz; ++x )
		{
			scalar v = sino_3d_4o( x * f0, y * f0, z );	// -1 .. 1
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

	scalar* im = (scalar*) malloc( sz * sz * sizeof( scalar ) );

	for ( int frame=0; frame<sz; ++frame )
	{
#if !defined(BENCHMARK)
		char fname[128];
		snprintf( fname, sizeof( fname ), "out%04d.pgm", frame );
		FILE* f = fopen( fname, "wb" );
		assert( f );
#endif
		do_frame( frame, im, sz );
#if !defined(BENCHMARK)
		write_pgm( f, im, sz );
		fclose( f );
#endif
	}

	sino_exit();
}

