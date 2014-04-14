#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <mathematics.h>
#include "test.h"




bool test_uniformf( void );
bool test_uniformd( void );
bool test_uniformld( void );
bool test_uniform_rangei( void );
bool test_uniform_rangel( void );
bool test_uniform_rangef( void );
bool test_uniform_ranged( void );
bool test_uniform_unitf( void );
bool test_uniform_unitd( void );
bool test_uniform_unitld( void );
bool test_even_and_odd( void );

const test_feature_t generic_math_functions[] = {
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
	{ "Testing is_even() and is_odd()", test_even_and_odd }
};


int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_eval_features( "Generic Math Functions", generic_math_functions, sizeof(generic_math_functions) / sizeof(generic_math_functions[0]) );

	return 0;
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

