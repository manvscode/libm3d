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
#include <float.h>
#include <assert.h>
#include "../src/numerical-methods.h"
#include "../src/mathematics.h"
#include "test.h"

static double f(double x);

bool test_bissection_method          ( void );
bool test_fixed_point_iteration      ( void );
bool test_secant_method              ( void );
bool test_least_squares_linear       ( void );
bool test_least_squares_quadratic    ( void );

const test_feature_t numerical_methods_tests[] = {
	{ "Testing Bissection Method for Root Finding",     test_bissection_method },
	{ "Testing Fixed Point Iteration for Root Finding", test_fixed_point_iteration },
	{ "Testing Secant Method for Root Finding",         test_secant_method },
	{ "Testing Least Squares for Linear",               test_least_squares_linear },
	{ "Testing Least Squares for Quadratic",            test_least_squares_quadratic },
};

size_t numerical_methods_test_suite_size( void )
{
	return sizeof(numerical_methods_tests) / sizeof(numerical_methods_tests[0]);
}


#ifdef TEST_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "Numerical Analysis Functions", numerical_methods_tests, numerical_methods_test_suite_size() );
	return 0;
}
#endif

double f(double x)
{
	return x*x*x + 4*x*x - 10;
}

bool test_bissection_method( void )
{
	double root = 0.0;
	bool result = m3d_bissection_method( 1.0, 2.0, DBL_EPSILON, 100, f, &root );
	return result && m3d_relative_errord(1.36523, root) < 0.001;
}

double g(double x)
{
	return sin(0.5 * x + M_PI / 8.0) + x;
}

bool test_fixed_point_iteration( void )
{
	double root = 0.0;

	// To find the root of sin(0.5x + pi/8) = 0, we set
	// g(x) = sin(0.5x + pi/8) - x
	bool result = m3d_fixed_point_iteration( 3.0, DBL_EPSILON, 1000, g, &root );

	return result && m3d_relative_errord(5.49778, root) < 0.001;
}

bool test_secant_method( void )
{
	double root = 0.0;
	bool result = m3d_secant_method( 1.0, 2.0, DBL_EPSILON, 100, f, &root );
	return result && m3d_relative_errord(1.36523, root) < 0.001;
}

bool test_least_squares_linear( void )
{
	double x1[] = {
		 6,  7,  8,
		10, 12, 14,
		15, 16
	};
	double y1[] = {
		4,  5, 7,
		6,  8, 8,
		7, 10
	};

	double m1 = 0.0;
	double b1 = 0.0;
	m3d_least_squares_linear( x1, y1, 8, &m1, &b1 );

	bool test1 = m3d_relative_errord( 0.421569, m1 ) < 0.001 &&
		         m3d_relative_errord( 2.237745, b1 ) < 0.001;

	double x2[] = {
		 1,  2,  8
	};
	double y2[] = {
		3, 5, 17
	};
	double m2 = 0.0;
	double b2 = 0.0;
	m3d_least_squares_linear( x2, y2, 3, &m2, &b2 );
	bool test2 = m3d_relative_errord( 2.0, m2 ) < 0.001 &&
		         m3d_relative_errord( 1.0, b2 ) < 0.001;

	return test1 && test2;
}

bool test_least_squares_quadratic( void )
{
	double x[] = {
		 0.0,  0.25,  0.5, 0.75, 1.0
	};
	double y[] = {
		1.0, 1.2840, 1.6487, 2.1170, 2.7183
	};

	double a = 0.0;
	double b = 0.0;
	double c = 0.0;
	m3d_least_squares_quadratic( x, y, 5, &a, &b, &c );

	double err = m3d_least_squares_quadratic_error( x, y, 5, a, b, c );

	bool test1 = m3d_relative_errord( 0.843, a ) < 0.001 &&
	             m3d_relative_errord( 0.864, b ) < 0.001 &&
		         m3d_relative_errord( 1.005, c ) < 0.001;

	return test1;
}
