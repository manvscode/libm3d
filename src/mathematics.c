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

long double uniformld( void )
{
	return ((long double)rand( )) / RAND_MAX;
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
	return 2 * (((float)rand()) / RAND_MAX) - 1;
}

double uniform_unitd( void )
{
	return 2 * (((double)rand()) / RAND_MAX) - 1;
}

long double uniform_unitld( void )
{
	return 2 * (((long double)rand()) / RAND_MAX) - 1;
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

long double guassianld( long double mean, long double stddev )
{
	long double ux;
	long double uy;
	long double s;
	static long double spare;
	static bool spare_ready = false;

	if( spare_ready )
	{
		spare_ready = false;
		return mean + stddev * spare;
	}
	else
	{
		do {
			ux = uniformld( ) * 2.0 - 1;
			uy = uniformld( ) * 2.0 - 1;
			s = ux * ux + uy * uy;
		} while( s >= 1.0f || s <= 0.0f );

		long double mul = sqrtl( -2.0f * log(s) / s );

		spare = uy * mul;
		spare_ready = true;

		return mean + stddev * ux * mul;
	}
}

int maxi( int x, int y )
{
	return integer_max( x, y );
}

long maxl( long x, long y )
{
	return integer_max( x, y );
}

float maxf( float x, float y )
{
	return x > y ? x : y;
}

double maxd( double x, double y )
{
	return x > y ? x : y;
}

long double maxld( long double x, long double y )
{
	return x > y ? x : y;
}

int mini( int x, int y )
{
	return integer_min( x, y );
}

long minl( long x, long y )
{
	return integer_min( x, y );
}

float minf( float x, float y )
{
	return x < y ? x : y;
}

double mind( double x, double y )
{
	return x < y ? x : y;
}

long double minld( long double x, long double y )
{
	return x < y ? x : y;
}

int clampi( int value, int min, int max )
{
	value = integer_max( max, value );
	return integer_min( value, min );
}

long clampl( int value, int min, int max )
{
	value = integer_max( max, value );
	return integer_min( value, min );
}

float clampf( float value, float min, float max )
{
	if( value > max )
	{
		return max;
	}
	else if( value < min )
	{
		return min;
	}

	return value;
}

double clampd( double value, double min, double max )
{
	if( value > max )
	{
		return max;
	}
	else if( value < min )
	{
		return min;
	}

	return value;
}

long double clampld( long double value, long double min, long double max )
{
	if( value > max )
	{
		return max;
	}
	else if( value < min )
	{
		return min;
	}

	return value;
}

bool is_power_of_2( int x )
{
	return (x & (x - 1)) == 0;
}

int next_power_of_2( int v )
{
	int r = v;
	r--;
	r |= r >> 1;
	r |= r >> 2;
	r |= r >> 4;
	r |= r >> 8;
	r |= r >> 16;
	r++;
	return r;
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
