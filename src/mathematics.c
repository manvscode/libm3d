/* Copyright (C) 2013-2014 by Joseph A. Marrero, http://www.manvscode.com/
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
	//return x > y ? x : y;
	return fmaxf( x, y );
}

double maxd( double x, double y )
{
	//return x > y ? x : y;
	return fmax( x, y );
}

long double maxld( long double x, long double y )
{
	//return x > y ? x : y;
	return fmaxl( x, y );
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
	//return x < y ? x : y;
	return fminf( x, y );
}

double mind( double x, double y )
{
	//return x < y ? x : y;
	return fmin( x, y );
}

long double minld( long double x, long double y )
{
	//return x < y ? x : y;
	return fminl( x, y );
}

unsigned int clampui( unsigned int value, unsigned int min, unsigned int max )
{
	value = integer_min( value, max );
	return integer_max( value, min );
}

unsigned long clampul( unsigned long value, unsigned long min, unsigned long max )
{
	value = integer_min( value, max );
	return integer_max( value, min );
}

int clampi( int value, int min, int max )
{
	#ifdef SAFE_CLAMP
	return value > max ? max : (value < min ? min : value);
	#else
	value = integer_min( value, max );
	return integer_max( value, min );
	#endif
}

long clampl( long value, long min, long max )
{
	#ifdef SAFE_CLAMP
	return value > max ? max : (value < min ? min : value);
	#else
	value = integer_min( value, max );
	return integer_max( value, min );
	#endif
}

float clampf( float value, float min, float max )
{
	return value > max ? max : (value < min ? min : value);
}

double clampd( double value, double min, double max )
{
	return value > max ? max : (value < min ? min : value);
}

long double clampld( long double value, long double min, long double max )
{
	return value > max ? max : (value < min ? min : value);
}


