#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../src/mathematics.h"

#define MAX  40

int main( int argc, char* argv[] )
{
	srand( time(NULL) );

	#if 1
	for( int i = 0; i < 10; i++ )
	{
		float r = MAX * uniformf( );
		assert( r >= 0.0f && r <= 1.0f );
		printf( "uniform random = %.3f\n", r );
	}
	#endif


	for( int i = 0; i < 10; i++ )
	{
		float r = guassianf( 0, 2.0 );
		printf( "guassian random = %.3f\n", r );
	}


	return 0;
}
