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
#include <stdlib.h>
#include <math.h>
#include "mathematics.h"

int m3d_uniformi( void )
{
	return rand( );
}

float m3d_uniformf( void )
{
	return ((float)rand( )) / RAND_MAX;
}

double m3d_uniformd( void )
{
	return ((double)rand( )) / RAND_MAX;
}

long double m3d_uniformld( void )
{
	return ((long double)rand( )) / RAND_MAX;
}

int m3d_uniform_rangei( int min, int max )
{
	int diff = max - min;
	return min + rand() % (diff + 1);
}

long m3d_uniform_rangel( long min, long max )
{
	long diff = max - min;
	return min + rand() % (diff + 1);
}

float m3d_uniform_rangef( float min, float max )
{
	float diff = max - min;
	return min + m3d_uniformf() * diff;
}

double m3d_uniform_ranged( double min, double max )
{
	double diff = max - min;
	return min + m3d_uniformd() * diff;
}

float m3d_uniform_unitf( void )
{
	return 2 * (((float)rand()) / RAND_MAX) - 1;
}

double m3d_uniform_unitd( void )
{
	return 2 * (((double)rand()) / RAND_MAX) - 1;
}

long double m3d_uniform_unitld( void )
{
	return 2 * (((long double)rand()) / RAND_MAX) - 1;
}

float m3d_guassianf( float mean, float stddev )
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
			ux = m3d_uniformf( ) * 2.0f - 1;
			uy = m3d_uniformf( ) * 2.0f - 1;
			s = ux * ux + uy * uy;
		} while( s >= 1.0f || s <= 0.0f );

		float mul = sqrtf( -2.0f * logf(s) / s );

		spare = uy * mul;
		spare_ready = true;

		return mean + stddev * ux * mul;
	}
}

double m3d_guassiand( double mean, double stddev )
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
			ux = m3d_uniformd( ) * 2.0 - 1;
			uy = m3d_uniformd( ) * 2.0 - 1;
			s = ux * ux + uy * uy;
		} while( s >= 1.0f || s <= 0.0f );

		double mul = sqrt( -2.0f * log(s) / s );

		spare = uy * mul;
		spare_ready = true;

		return mean + stddev * ux * mul;
	}
}

long double m3d_guassianld( long double mean, long double stddev )
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
			ux = m3d_uniformld( ) * 2.0 - 1;
			uy = m3d_uniformld( ) * 2.0 - 1;
			s = ux * ux + uy * uy;
		} while( s >= 1.0f || s <= 0.0f );

		long double mul = sqrtl( -2.0f * log(s) / s );

		spare = uy * mul;
		spare_ready = true;

		return mean + stddev * ux * mul;
	}
}

int m3d_maxi( int x, int y )
{
	return m3d_integer_max( x, y );
}

long m3d_maxl( long x, long y )
{
	return m3d_integer_max( x, y );
}

float m3d_maxf( float x, float y )
{
	return fmaxf( x, y );
}

double m3d_maxd( double x, double y )
{
	return fmax( x, y );
}

long double m3d_maxld( long double x, long double y )
{
	return fmaxl( x, y );
}

int m3d_mini( int x, int y )
{
	return m3d_integer_min( x, y );
}

long m3d_minl( long x, long y )
{
	return m3d_integer_min( x, y );
}

float m3d_minf( float x, float y )
{
	return fminf( x, y );
}

double m3d_mind( double x, double y )
{
	return fmin( x, y );
}

long double m3d_minld( long double x, long double y )
{
	return fminl( x, y );
}

unsigned int m3d_clampui( unsigned int value, unsigned int min, unsigned int max )
{
	#if 0
	return value > max ? max : (value < min ? min : value);
	#else
	value = m3d_integer_max( value, min );
	return m3d_integer_min( value, max );
	#endif
}

unsigned long m3d_clampul( unsigned long value, unsigned long min, unsigned long max )
{
	#if 0
	return value > max ? max : (value < min ? min : value);
	#else
	value = m3d_integer_max( value, min );
	return m3d_integer_min( value, max );
	#endif
}

int m3d_clampi( int value, int min, int max )
{
	#if 0
	return value > max ? max : (value < min ? min : value);
	#else
	value = m3d_integer_max( value, min );
	return m3d_integer_min( value, max );
	#endif
}

long m3d_clampl( long value, long min, long max )
{
	#if 0
	return value > max ? max : (value < min ? min : value);
	#else
	value = m3d_integer_max( value, min );
	return m3d_integer_min( value, max );
	#endif
}

float m3d_clampf( float value, float min, float max )
{
	#if 0
	return value > max ? max : (value < min ? min : value);
	#else
	return m3d_minf( m3d_maxf(value, min), max );
	#endif
}

double m3d_clampd( double value, double min, double max )
{
	#if 0
	return value > max ? max : (value < min ? min : value);
	#else
	return m3d_mind( m3d_maxd(value, min), max );
	#endif
}

long double m3d_clampld( long double value, long double min, long double max )
{
	#if 0
	return value > max ? max : (value < min ? min : value);
	#else
	return m3d_minld( m3d_maxld(value, min), max );
	#endif
}

int m3d_powi( int b, unsigned int e )
{
	int result = 1;

	while( e > 0 )
	{
		result *= b;
		e -= 1;
	}

	return result;
}

long int m3d_powli( long b, unsigned long e )
{
	long result = 1L;

	while( e > 0L )
	{
		result *= b;
		e -= 1L;
	}

	return result;
}

