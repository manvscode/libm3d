#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <mathematics.h>
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
};

size_t math_test_suite_size( void )
{
	return sizeof(math_tests) / sizeof(math_tests[0]);
}


#ifdef TEST_MATHEMATICS_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "Math Functions", math_tests, math_test_suite_size() );
	return 0;
}
#endif

bool test_scaler_size( void )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
	return sizeof(scaler_t) == sizeof(long double);
	#elif defined(LIB3DMATH_USE_DOUBLE)
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
		float n = uniformf( );

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
		double n = uniformd( );

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
		long double n = uniformld( );

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
		int min = mini(a,b);
		int max = maxi(a,b);
		int n = uniform_rangei( min, max );

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
		long min = minl(a,b);
		long max = maxl(a,b);
		long n = uniform_rangel( min, max );

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
		float n = uniform_rangef( min, max );

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
		double n = uniform_ranged( min, max );

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
		float n = uniform_unitf( );

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
		double n = uniform_unitd( );

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
		long double n = uniform_unitd( );

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
			passed = is_even( i ) == true && is_odd( i ) == false;

		}
		else
		{
			passed = is_odd( i ) == true && is_even( i ) == false;
		}
	}

	return passed;
}

bool test_maxi( void )
{
	int a = maxi( -3, 5 );
	int b = maxi( 1003, 54 );
	int c = maxi( 120, 3 );
	int d = maxi( -1000, -99 );

	return (a == 5) &&
	       (b == 1003) &&
	       (c == 120) &&
	       (d == -99);
}

bool test_maxl( void )
{
	long a = maxl( -3L, 5L );
	long b = maxl( 1003L, 54L );
	long c = maxl( 120L, 3L );
	long d = maxl( 100L, -99L );

	return (a == 5L) &&
	       (b == 1003L) &&
	       (c == 120L) &&
	       (d == 100L);
}

bool test_maxf( void )
{
	float a = maxf( -3.3f, 5.1f );
	float b = maxf( 1003.0234f, 54.123f );
	float c = maxf( 3.0f, 3.00001f );
	float d = maxf( 100.0f, -99.5f );

	return float_equals(a, 5.1f) &&
	       float_equals(b, 1003.0234f) &&
	       float_equals(c, 3.00001f) &&
	       float_equals(d, 100.0f);
}

bool test_maxd( void )
{
	double a = maxd( -3.3, 5.1 );
	double b = maxd( 1003.0234, 54.123 );
	double c = maxd( 3.0, 3.00001 );
	double d = maxd( 100.0, -99.5 );

	return double_equals(a, 5.1) &&
	       double_equals(b, 1003.0234) &&
	       double_equals(c, 3.00001) &&
	       double_equals(d, 100.0);
}

bool test_maxld( void )
{
	long double a = maxld( -3.3, 5.1 );
	long double b = maxld( 1003.0234, 54.123 );
	long double c = maxld( 3.0, 3.00001 );
	long double d = maxld( 100.0, -99.5 );

	return long_double_equals(a, 5.1) &&
	       long_double_equals(b, 1003.0234) &&
	       long_double_equals(c, 3.00001) &&
	       long_double_equals(d, 100.0);
}

bool test_mini( void )
{
	int a = mini( -3, 5 );
	int b = mini( 1003, 54 );
	int c = mini( 120, 3 );
	int d = mini( 100, -99 );

	return (a == -3) &&
	       (b == 54) &&
	       (c == 3) &&
	       (d == -99);
}

bool test_minl( void )
{
	long a = minl( -3L, 5L );
	long b = minl( 1003L, 54L );
	long c = minl( 120L, 3L );
	long d = minl( 100L, -99L );

	return (a == -3L) &&
	       (b == 54L) &&
	       (c == 3L) &&
	       (d == -99L);
}

bool test_minf( void )
{
	float a = minf( -3.3f, 5.1f );
	float b = minf( 1003.0234f, 54.123f );
	float c = minf( 3.0f, 3.00001f );
	float d = minf( 100.0f, -99.5f );

	return float_equals(a, -3.3f) &&
	       float_equals(b, 54.123f) &&
	       float_equals(c, 3.0f) &&
	       float_equals(d, -99.5f);
}

bool test_mind( void )
{
	double a = mind( -3.3, 5.1 );
	double b = mind( 1003.0234, 54.123 );
	double c = mind( 3.0, 3.00001 );
	double d = mind( 100.0, -99.5 );

	return double_equals(a, -3.3) &&
	       double_equals(b, 54.123) &&
	       double_equals(c, 3.0) &&
	       double_equals(d, -99.5);
}

bool test_minld( void )
{
	long double a = mind( -3.3, 5.1 );
	long double b = mind( 1003.0234, 54.123 );
	long double c = mind( 3.0, 3.00001 );
	long double d = mind( 100.0, -99.5 );

	return long_double_equals(a, -3.3) &&
	       long_double_equals(b, 54.123) &&
	       long_double_equals(c, 3.0) &&
	       long_double_equals(d, -99.5);
}

bool test_clampui( void )
{
	int a = clampui( 4, 1, 10 );
	int b = clampui( 124234, 0, 6003450 );
	int c = clampui( 16, 10, 30 );
	int d = clampui( 35, 10, 30 );
	int e = clampui( 8, 10, 30 );

	return (a == 4) &&
	       (b == 124234) &&
	       (c == 16) &&
	       (d == 30) &&
	       (e == 10);
}

bool test_clampul( void )
{
	long a = clampul( 4L, 1L, 10L );
	long b = clampul( 124234L, 0L, 6003450L );
	long c = clampul( 16L, 10L, 30L );
	long d = clampul( 35L, 10L, 30L );
	long e = clampul( 8L, 10L, 30L );

	return (a == 4L) &&
	       (b == 124234L) &&
	       (c == 16L) &&
	       (d == 30L) &&
	       (e == 10L);

}

bool test_clampi( void )
{
	int a = clampi( -4, 1, 10 );
	int b = clampi( 5, 50, 100 );
	int c = clampi( -5, -10, 0 );
	int d = clampi( 5, -10, 0 );
	int e = clampi( -99, -40, -4 );
	int f = clampi( 99, 4, 40 );

	return (a == 1) &&
	       (b == 50) &&
	       (c == -5) &&
	       (d == 0) &&
	       (e == -40) &&
	       (f == 40);
}

bool test_clampl( void )
{
	long a = clampl( -4L, 1L, 10L );
	long b = clampl( 5L, 50L, 100L );
	long c = clampl( -5L, -10L, 0L );
	long d = clampl( 5L, -10L, 0L );

	return (a == 1L) &&
	       (b == 50L) &&
	       (c == -5L) &&
	       (d == 0L);
}

bool test_clampf( void )
{
	float a = clampf( -4.0f, 1.0f, 10.0f );
	float b = clampf( 5.0f, 50.0f, 100.0f );
	float c = clampf( -5.0f, -10.0f, 0.0f );
	float d = clampf( 5.0f, -10.0f, 0.0f );

	return float_equals( a, 1.0f ) &&
	       float_equals( b, 50.0f ) &&
	       float_equals( c, -5.0f ) &&
	       float_equals( d, 0.0f );
}

bool test_clampd( void )
{
	double a = clampd( -4.0, 1.0, 10.0 );
	double b = clampd( 5.0, 50.0, 100.0 );
	double c = clampd( -5.0, -10.0, 0.0 );
	double d = clampd( 5.0, -10.0, 0.0 );

	return double_equals( a, 1.0 ) &&
	       double_equals( b, 50.0 ) &&
	       double_equals( c, -5.0 ) &&
	       double_equals( d, 0.0 );
}

bool test_clampld( void )
{
	long double a = clampld( -4.0, 1.0, 10.0 );
	long double b = clampld( 5.0, 50.0, 100.0 );
	long double c = clampld( -5.0, -10.0, 0.0 );
	long double d = clampld( 5.0, -10.0, 0.0 );

	return long_double_equals( a, 1.0 ) &&
	       long_double_equals( b, 50.0 ) &&
	       long_double_equals( c, -5.0 ) &&
	       long_double_equals( d, 0.0 );
}

