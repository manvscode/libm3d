/* Copyright (C) 2013-2015 by Joseph A. Marrero, http://www.manvscode.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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
		float r = m3d_uniform_unitf( );
		assert( r >= -1.0f && r <= 1.0f );
		printf( "uniform random = %.3f\n", r );
	}

	for( int i = 0; i < 10; i++ )
	{
		float r = m3d_guassianf( 0, 2.0 );
		printf( "guassian random = %.3f\n", r );
	}

	for( int i = 0; i < 10; i++ )
	{
		int r = m3d_uniform_rangei( 30, 100 );
		assert( r >= 30 && r <= 100 );
		printf( "random integer between 30 and 100 = %d\n", r );
	}


	printf( "done.\n" );
	return 0;
}
