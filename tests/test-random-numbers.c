#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../src/mathematics.h"

#define MAX  40

int main( int argc, char* argv[] )
{
	srand( time(NULL) );

	for( int i = 0; i < 10; i++ )
	{
		float r = uniformf( );
		assert( r >= 0.0f && r <= 1.0f );
		printf( "uniform random = %.3f\n", r );
	}

	for( int i = 0; i < 10; i++ )
	{
		float r = guassianf( 0, 2.0 );
		printf( "guassian random = %.3f\n", r );
	}

	for( int i = 0; i < 10; i++ )
	{
		int r = uniform_rangei( 30, 100 );
		assert( r >= 30 && r <= 100 );
		printf( "random integer between 30 and 100 = %d\n", r );
	}


	printf( "done.\n" );
	return 0;
}
