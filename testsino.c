
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sino.h"

void write_pgm( FILE*f, scalar* im, int sz )
{
	unsigned char* data = ( unsigned char* ) malloc( sz * sz );
	scalar* reader = im;
	unsigned char* writer = data;
	for ( int y=0; y<sz; ++y )
		for ( int x=0; x<sz; ++x )
		{
			const int v = 255.99999f * (*reader++);
			*writer++ = (unsigned char) v;
		}
	fprintf( f, "P5\n%d %d\n255\n", sz, sz );
	fwrite( data, sz*sz, 1, f );
}


static void do_frame( int nr, scalar*im, int sz )
{
	scalar* writer = im;
	// Set the frequencies and amplitudes for the four octaves.
	const float f0 = 1.0f / sz * 3;
	const float f1 = 2.0f / sz * 3;
	const float f2 = 4.0f / sz * 3;
	const float f3 = 8.0f / sz * 3;
	const float a0 = 1.0f;
	const float a1 = 0.5f;
	const float a2 = 0.25f;
	const float a3 = 0.125f;
	// Pick a z-slice based on the framenr.
	const float z = nr * 2.0f / sz;
	// Generate a 2d image.
	for ( int y=0; y<sz; ++y )
		for ( int x=0; x<sz; ++x )
		{
			const scalar v0 = a0 * sino_3d( x * f0 , y * f0, z );
			const scalar v1 = a1 * sino_3d( x * f1 , y * f1, z );
			const scalar v2 = a2 * sino_3d( x * f2 , y * f2, z );
			const scalar v3 = a3 * sino_3d( x * f3 , y * f3, z );
			const scalar v = ( v0 + v1 + v2 + v3 ); 		// -1.875 .. 1.875
			*writer++ = ( v + 1.875f ) / ( 2 * 1.875 );
		}
}


int main( int argc, char* argv[] )
{
	if ( argc != 2 )
	{
		fprintf( stderr, "Usage: %s imsize", argv[ 0 ] );
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

