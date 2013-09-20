/* Copyright (C) 2013 by Joseph A. Marrero, http://www.manvscode.com/
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
#include <stdlib.h>
#include <math.h>
#include "mathematics.h"

float uniformi( void )
{
	return rand( );
}

float uniformf( void )
{
	return ((float)rand( )) / RAND_MAX;
}

double uniformd( void )
{
	return ((double)rand( )) / RAND_MAX;
}

int uniform_rangei( int min, int max )
{
	int diff = max - min;
	return min + rand() % (diff + 1);
}

long uniform_rangel( long min, long max )
{
	long diff = max - min;
	return min + rand() % (diff + 1);
}

float uniform_rangef( float min, float max )
{
	float diff = max - min;
	return min + uniformf() * diff;
}

double uniform_ranged( double min, double max )
{
	double diff = max - min;
	return min + uniformd() * diff;
}

float uniform_unitf( void )
{
	return ((float)((rand( ) << 1) - RAND_MAX)) / RAND_MAX; // (2.0f * rand() - RAND_MAX) / RAND_MAX
}

double uniform_unitd( void )
{
	return ((double)((rand( ) << 1) - RAND_MAX)) / RAND_MAX; // (2.0f * rand() - RAND_MAX) / RAND_MAX
}

float guassianf( float mean, float stddev )
{
	float ux;
	float uy;
	float s;
	static float spare;
	static bool spare_ready = false;

	if( spare_ready )
	{
		spare_ready = false;
		return mean + stddev * spare;
	}
	else
	{
		do {
			ux = uniformf( ) * 2.0f - 1;
			uy = uniformf( ) * 2.0f - 1;
			s = ux * ux + uy * uy;
		} while( s >= 1.0f || s <= 0.0f );

		float mul = sqrtf( -2.0f * logf(s) / s );

		spare = uy * mul;
		spare_ready = true;

		return mean + stddev * ux * mul;
	}
}

double guassiand( double mean, double stddev )
{
	double ux;
	double uy;
	double s;
	static double spare;
	static bool spare_ready = false;

	if( spare_ready )
	{
		spare_ready = false;
		return mean + stddev * spare;
	}
	else
	{
		do {
			ux = uniformd( ) * 2.0 - 1;
			uy = uniformd( ) * 2.0 - 1;
			s = ux * ux + uy * uy;
		} while( s >= 1.0f || s <= 0.0f );

		double mul = sqrt( -2.0f * log(s) / s );

		spare = uy * mul;
		spare_ready = true;

		return mean + stddev * ux * mul;
	}
}

float fast_inverse_sqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * (long *) &y;                         /* evil floating point bit level hacking */
	i  = 0x5f3759df - ( i >> 1 );               /* what the fuck? */
	y  = * (float *) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   /* 1st iteration */
	#if 0
	y  = y * ( threehalfs - ( x2 * y * y ) );   /* 2nd iteration, this can be removed */
	#endif

	return y;
}
