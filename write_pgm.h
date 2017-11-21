
static void write_pgm( FILE*f, scalar* im, int sz )
{
	const size_t datasz = (size_t) ( sz * sz );
	unsigned char* data = ( unsigned char* ) malloc( datasz );
	scalar* reader = im;
	unsigned char* writer = data;
	for ( int y=0; y<sz; ++y )
		for ( int x=0; x<sz; ++x )
		{
			const int v = (int) ( 255.99999f * (*reader++) );
			*writer++ = (unsigned char) v;
		}
	fprintf( f, "P5\n%d %d\n255\n", sz, sz );
	fwrite( data, datasz, 1, f );
}

