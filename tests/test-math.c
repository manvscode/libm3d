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
#include <limits.h>
#include <string.h>
#include <time.h>
#include "../src/mathematics.h"
#include "test.h"

bool test_scaler_size      ( void );
bool test_uniformf         ( void );
bool test_uniformd         ( void );
bool test_uniformld        ( void );
bool test_uniform_rangei   ( void );
bool test_uniform_rangel   ( void );
bool test_uniform_rangef   ( void );
bool test_uniform_ranged   ( void );
bool test_uniform_unitf    ( void );
bool test_uniform_unitd    ( void );
bool test_uniform_unitld   ( void );
bool test_even_and_odd     ( void );
bool test_maxi             ( void );
bool test_maxl             ( void );
bool test_maxf             ( void );
bool test_maxd             ( void );
bool test_maxld            ( void );
bool test_mini             ( void );
bool test_minl             ( void );
bool test_minf             ( void );
bool test_mind             ( void );
bool test_minld            ( void );
bool test_clampui          ( void );
bool test_clampul          ( void );
bool test_clampi           ( void );
bool test_clampl           ( void );
bool test_clampf           ( void );
bool test_clampd           ( void );
bool test_clampld          ( void );
bool test_powi             ( void );
bool test_powli            ( void );

const test_feature_t math_tests[] = {
	{ "Testing scaler_t size", test_scaler_size },
	{ "Testing uniformf()", test_uniformf },
	{ "Testing uniformd()", test_uniformd },
	{ "Testing uniformld()", test_uniformld },
	{ "Testing uniform_rangei()", test_uniform_rangei },
	{ "Testing uniform_rangel()", test_uniform_rangel },
	{ "Testing uniform_rangef()", test_uniform_rangef },
	{ "Testing uniform_ranged()", test_uniform_ranged },
	{ "Testing uniform_unitf()", test_uniform_unitf },
	{ "Testing uniform_unitd()", test_uniform_unitd },
	{ "Testing uniform_unitld()", test_uniform_unitld },
	{ "Testing is_even() and is_odd()", test_even_and_odd },
	{ "Testing maxi()", test_maxi },
	{ "Testing maxl()", test_maxl },
	{ "Testing maxf()", test_maxf },
	{ "Testing maxd()", test_maxd },
	{ "Testing maxld()", test_maxld },
	{ "Testing mini()", test_mini },
	{ "Testing minl()", test_minl },
	{ "Testing minf()", test_minf },
	{ "Testing mind()", test_mind },
	{ "Testing minld()", test_minld },
	{ "Testing clampui()", test_clampui },
	{ "Testing clampul()", test_clampul },
	{ "Testing clampi()", test_clampi },
	{ "Testing clampl()", test_clampl },
	{ "Testing clampf()", test_clampf },
	{ "Testing clampd()", test_clampd },
	{ "Testing clampld()", test_clampld },
	{ "Testing powi()", test_powi },
	{ "Testing powli()", test_powli },
};

size_t math_test_suite_size( void )
{
	return sizeof(math_tests) / sizeof(math_tests[0]);
}


#ifdef TEST_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "Math Functions", math_tests, math_test_suite_size() );
	return 0;
}
#endif

bool test_scaler_size( void )
{
	#if defined(LIBM3D_USE_LONG_DOUBLE)
	return sizeof(scaler_t) == sizeof(long double);
	#elif defined(LIBM3D_USE_DOUBLE)
	return sizeof(scaler_t) == sizeof(double);
	#else /* default: use float */
	return sizeof(scaler_t) == sizeof(float);
	#endif
}

bool test_uniformf( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		float n = m3d_uniformf( );

		if( n < 0.0f || n > 1.0f )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_uniformd( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		double n = m3d_uniformd( );

		if( n < 0.0 || n > 1.0 )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_uniformld( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		long double n = m3d_uniformld( );

		if( n < 0.0 || n > 1.0 )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_uniform_rangei( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		int a = rand();
		int b = rand();
		int min = m3d_mini(a,b);
		int max = m3d_maxi(a,b);
		int n = m3d_uniform_rangei( min, max );

		if( n < min || n > max )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_uniform_rangel( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		long a = rand();
		long b = rand();
		long min = m3d_minl(a,b);
		long max = m3d_maxl(a,b);
		long n = m3d_uniform_rangel( min, max );

		if( n < min || n > max )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_uniform_rangef( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		float a = (float) rand();
		float b = (float) rand();
		float min = fmin(a,b);
		float max = fmax(a,b);
		float n = m3d_uniform_rangef( min, max );

		if( n < min || n > max )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_uniform_ranged( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		double a = (double) rand();
		double b = (double) rand();
		double min = fmin(a,b);
		double max = fmax(a,b);
		double n = m3d_uniform_ranged( min, max );

		if( n < min || n > max )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_uniform_unitf( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		float n = m3d_uniform_unitf( );

		if( n < -1.0f || n > 1.0f )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_uniform_unitd( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		double n = m3d_uniform_unitd( );

		if( n < -1.0 || n > 1.0 )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_uniform_unitld( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		long double n = m3d_uniform_unitd( );

		if( n < -1.0 || n > 1.0 )
		{
			passed = false;
		}
	}

	return passed;
}

bool test_even_and_odd( void )
{
	bool passed = true;

	for( size_t i = 0; passed && i < 10000; i++ )
	{
		if( i % 2 == 0 )
		{
			passed = m3d_is_even( i ) == true && m3d_is_odd( i ) == false;

		}
		else
		{
			passed = m3d_is_odd( i ) == true && m3d_is_even( i ) == false;
		}
	}

	return passed;
}

bool test_maxi( void )
{
	int a = m3d_maxi( -3, 5 );
	int b = m3d_maxi( 1003, 54 );
	int c = m3d_maxi( 120, 3 );
	int d = m3d_maxi( -1000, -99 );

	return (a == 5) &&
	       (b == 1003) &&
	       (c == 120) &&
	       (d == -99);
}

bool test_maxl( void )
{
	long a = m3d_maxl( -3L, 5L );
	long b = m3d_maxl( 1003L, 54L );
	long c = m3d_maxl( 120L, 3L );
	long d = m3d_maxl( 100L, -99L );

	return (a == 5L) &&
	       (b == 1003L) &&
	       (c == 120L) &&
	       (d == 100L);
}

bool test_maxf( void )
{
	float a = m3d_maxf( -3.3f, 5.1f );
	float b = m3d_maxf( 1003.0234f, 54.123f );
	float c = m3d_maxf( 3.0f, 3.00001f );
	float d = m3d_maxf( 100.0f, -99.5f );

	return float_equals(a, 5.1f) &&
	       float_equals(b, 1003.0234f) &&
	       float_equals(c, 3.00001f) &&
	       float_equals(d, 100.0f);
}

bool test_maxd( void )
{
	double a = m3d_maxd( -3.3, 5.1 );
	double b = m3d_maxd( 1003.0234, 54.123 );
	double c = m3d_maxd( 3.0, 3.00001 );
	double d = m3d_maxd( 100.0, -99.5 );

	return double_equals(a, 5.1) &&
	       double_equals(b, 1003.0234) &&
	       double_equals(c, 3.00001) &&
	       double_equals(d, 100.0);
}

bool test_maxld( void )
{
	long double a = m3d_maxld( -3.3, 5.1 );
	long double b = m3d_maxld( 1003.0234, 54.123 );
	long double c = m3d_maxld( 3.0, 3.00001 );
	long double d = m3d_maxld( 100.0, -99.5 );

	return long_double_equals(a, 5.1) &&
	       long_double_equals(b, 1003.0234) &&
	       long_double_equals(c, 3.00001) &&
	       long_double_equals(d, 100.0);
}

bool test_mini( void )
{
	int a = m3d_mini( -3, 5 );
	int b = m3d_mini( 1003, 54 );
	int c = m3d_mini( 120, 3 );
	int d = m3d_mini( 100, -99 );

	return (a == -3) &&
	       (b == 54) &&
	       (c == 3) &&
	       (d == -99);
}

bool test_minl( void )
{
	long a = m3d_minl( -3L, 5L );
	long b = m3d_minl( 1003L, 54L );
	long c = m3d_minl( 120L, 3L );
	long d = m3d_minl( 100L, -99L );

	return (a == -3L) &&
	       (b == 54L) &&
	       (c == 3L) &&
	       (d == -99L);
}

bool test_minf( void )
{
	float a = m3d_minf( -3.3f, 5.1f );
	float b = m3d_minf( 1003.0234f, 54.123f );
	float c = m3d_minf( 3.0f, 3.00001f );
	float d = m3d_minf( 100.0f, -99.5f );

	return float_equals(a, -3.3f) &&
	       float_equals(b, 54.123f) &&
	       float_equals(c, 3.0f) &&
	       float_equals(d, -99.5f);
}

bool test_mind( void )
{
	double a = m3d_mind( -3.3, 5.1 );
	double b = m3d_mind( 1003.0234, 54.123 );
	double c = m3d_mind( 3.0, 3.00001 );
	double d = m3d_mind( 100.0, -99.5 );

	return double_equals(a, -3.3) &&
	       double_equals(b, 54.123) &&
	       double_equals(c, 3.0) &&
	       double_equals(d, -99.5);
}

bool test_minld( void )
{
	long double a = m3d_mind( -3.3, 5.1 );
	long double b = m3d_mind( 1003.0234, 54.123 );
	long double c = m3d_mind( 3.0, 3.00001 );
	long double d = m3d_mind( 100.0, -99.5 );

	return long_double_equals(a, -3.3) &&
	       long_double_equals(b, 54.123) &&
	       long_double_equals(c, 3.0) &&
	       long_double_equals(d, -99.5);
}

bool test_clampui( void )
{
	int a = m3d_clampui( 4, 1, 10 );
	int b = m3d_clampui( 124234, 0, 6003450 );
	int c = m3d_clampui( 16, 10, 30 );
	int d = m3d_clampui( 35, 10, 30 );
	int e = m3d_clampui( 8, 10, 30 );

	return (a == 4) &&
	       (b == 124234) &&
	       (c == 16) &&
	       (d == 30) &&
	       (e == 10);
}

bool test_clampul( void )
{
	long a = m3d_clampul( 4L, 1L, 10L );
	long b = m3d_clampul( 124234L, 0L, 6003450L );
	long c = m3d_clampul( 16L, 10L, 30L );
	long d = m3d_clampul( 35L, 10L, 30L );
	long e = m3d_clampul( 8L, 10L, 30L );

	return (a == 4L) &&
	       (b == 124234L) &&
	       (c == 16L) &&
	       (d == 30L) &&
	       (e == 10L);

}

bool test_clampi( void )
{
	int a = m3d_clampi( -4, 1, 10 );
	int b = m3d_clampi( 5, 50, 100 );
	int c = m3d_clampi( -5, -10, 0 );
	int d = m3d_clampi( 5, -10, 0 );
	int e = m3d_clampi( -99, -40, -4 );
	int f = m3d_clampi( 99, 4, 40 );

	return (a == 1) &&
	       (b == 50) &&
	       (c == -5) &&
	       (d == 0) &&
	       (e == -40) &&
	       (f == 40);
}

bool test_clampl( void )
{
	long a = m3d_clampl( -4L, 1L, 10L );
	long b = m3d_clampl( 5L, 50L, 100L );
	long c = m3d_clampl( -5L, -10L, 0L );
	long d = m3d_clampl( 5L, -10L, 0L );

	return (a == 1L) &&
	       (b == 50L) &&
	       (c == -5L) &&
	       (d == 0L);
}

bool test_clampf( void )
{
	float a = m3d_clampf( -4.0f, 1.0f, 10.0f );
	float b = m3d_clampf( 5.0f, 50.0f, 100.0f );
	float c = m3d_clampf( -5.0f, -10.0f, 0.0f );
	float d = m3d_clampf( 5.0f, -10.0f, 0.0f );

	return float_equals( a, 1.0f ) &&
	       float_equals( b, 50.0f ) &&
	       float_equals( c, -5.0f ) &&
	       float_equals( d, 0.0f );
}

bool test_clampd( void )
{
	double a = m3d_clampd( -4.0, 1.0, 10.0 );
	double b = m3d_clampd( 5.0, 50.0, 100.0 );
	double c = m3d_clampd( -5.0, -10.0, 0.0 );
	double d = m3d_clampd( 5.0, -10.0, 0.0 );

	return double_equals( a, 1.0 ) &&
	       double_equals( b, 50.0 ) &&
	       double_equals( c, -5.0 ) &&
	       double_equals( d, 0.0 );
}

bool test_clampld( void )
{
	long double a = m3d_clampld( -4.0, 1.0, 10.0 );
	long double b = m3d_clampld( 5.0, 50.0, 100.0 );
	long double c = m3d_clampld( -5.0, -10.0, 0.0 );
	long double d = m3d_clampld( 5.0, -10.0, 0.0 );

	return long_double_equals( a, 1.0 ) &&
	       long_double_equals( b, 50.0 ) &&
	       long_double_equals( c, -5.0 ) &&
	       long_double_equals( d, 0.0 );
}

bool test_powi( void )
{
	int a = m3d_powi(2, 3);
	int b = m3d_powi(11, 7);

	return integer_equals( a, 8 ) &&
	       integer_equals( b, 19487171 );
}

bool test_powli( void )
{
	long a = m3d_powli(3, 7);
	long b = m3d_powli(17, 5);

	return integer_equals( a, 2187L ) &&
	       integer_equals( b, 1419857L );
}
