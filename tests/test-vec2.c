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
#include <stdbool.h>
#include "../src/vec2.h"
#include "test.h"

bool test_vec2_literals        ( void );
bool test_vec2_addition        ( void );
bool test_vec2_subtraction     ( void );
bool test_vec2_scaler_multiply ( void );
bool test_vec2_magnitude       ( void );
bool test_vec2_dot_product     ( void );
bool test_vec2_cross_product   ( void );
bool test_vec2_distance        ( void );
bool test_vec2_angle           ( void );
bool test_vec2_normalize       ( void );
bool test_vec2_is_normalized   ( void );
bool test_vec2_negate          ( void );
bool test_vec2_zero            ( void );

const test_feature_t vec2_tests[] = {
	{ "Testing vec2 literals",                 test_vec2_literals },
	{ "Testing vec2 addition",                 test_vec2_addition },
	{ "Testing vec2 subtraction",              test_vec2_subtraction },
	{ "Testing vec2 scaler multiply",          test_vec2_scaler_multiply },
	{ "Testing vec2 magnitude (i.e. length)",  test_vec2_magnitude },
	{ "Testing vec2 dot product",              test_vec2_dot_product },
	{ "Testing vec2 cross product",            test_vec2_cross_product },
	{ "Testing vec2 distance",                 test_vec2_distance },
	{ "Testing vec2 angle",                    test_vec2_angle },
	{ "Testing vec2 normalize",                test_vec2_normalize },
	{ "Testing vec2 is normalized",            test_vec2_is_normalized },
	{ "Testing vec2 negation",                 test_vec2_negate },
	{ "Testing vec2 zero",                     test_vec2_zero },
};

size_t vec2_test_suite_size( void )
{
	return sizeof(vec2_tests) / sizeof(vec2_tests[0]);
}

#ifdef TEST_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	bool result = test_features( "2D Vector Functions", vec2_tests, vec2_test_suite_size() );
	return result ? 0 : 1;
}
#endif

bool test_vec2_literals( void )
{
	vec2_t v = VEC2( 1, 2 );
	return scaler_compare( v.x, 1.0 ) &&
	       scaler_compare( v.y, 2.0 );
}

bool test_vec2_addition( void )
{
	vec2_t a = VEC2( 0, 1 );
	vec2_t b = VEC2( 4, -1 );
	vec2_t r = vec2_add( &a, &b );
	return scaler_compare( r.x, 4.0 ) &&
	       scaler_compare( r.y, 0.0 );
}

bool test_vec2_subtraction( void )
{
	vec2_t a = VEC2( 2, 2 );
	vec2_t b = VEC2( -2, 2 );
	vec2_t r = vec2_subtract( &a, &b );
	return scaler_compare( r.x, 4.0 ) &&
	       scaler_compare( r.y, 0.0 );
}

bool test_vec2_scaler_multiply( void )
{
	vec2_t a = VEC2( 3, 2 );
	scaler_t s = 0.5;
	vec2_t r = vec2_multiply( &a, s );
	return scaler_compare( r.x, 1.5 ) &&
	       scaler_compare( r.y, 1.0 );
}

bool test_vec2_magnitude( void )
{
	vec2_t a = VEC2( 3, 2 );
	scaler_t r = vec2_magnitude( &a );
	return scaler_compare( r, scaler_sqrt(3*3 + 2*2) );
}

bool test_vec2_dot_product( void )
{
	vec2_t a = VEC2( 3, 2 );
	vec2_t b = VEC2( 3, 2 );
	scaler_t r1 = vec2_dot_product( &a, &b );

	vec2_t c = VEC2( 1, 2 );
	vec2_t d = VEC2( 5, 3 );
	scaler_t r2 = vec2_dot_product( &c, &d );

	return scaler_compare( r1, 13.0 ) &&
	       scaler_compare( r2, 11.0 );
}

bool test_vec2_cross_product( void )
{
	vec2_t a = VEC2( 1, 2 );
	vec2_t c1 = vec2_cross_product( &a );

	bool r1 = scaler_compare( c1.x, a.y ) &&
	          scaler_compare( c1.y, -a.x );

	vec2_t b = VEC2( 3.14, -9 );
	vec2_t c2 = vec2_cross_product( &b );

	bool r2 = scaler_compare( c2.x, b.y ) &&
	          scaler_compare( c2.y, -b.x );

	return r1 && r2;
}

bool test_vec2_distance( void )
{
	vec2_t a = VEC2( 3, 2 );
	vec2_t b = VEC2( 3, 2 );
	scaler_t r1 = vec2_distance( &a, &b );

	vec2_t c = VEC2( 1, 1 );
	vec2_t d = VEC2( 5, 1 );
	scaler_t r2 = vec2_distance( &c, &d );

	return scaler_compare( r1, 0.0 ) &&
	       scaler_compare( r2, 4.0 );
}

bool test_vec2_angle( void )
{
	vec2_t a = VEC2( 1, 1 );
	vec2_t b = VEC2( 0, 1 );
	scaler_t r1 = vec2_angle( &a, &b );

	vec2_t c = VEC2( 1, 0 );
	vec2_t d = VEC2( 0, 1 );
	scaler_t r2 = vec2_angle( &c, &d );

	return scaler_compare( r1, 45.0 * M3D_RADIANS_PER_DEGREE ) &&
	       scaler_compare( r2, 90.0 * M3D_RADIANS_PER_DEGREE );
}

bool test_vec2_normalize( void )
{
	vec2_t a = VEC2( 3.123, 12.5 );
	vec2_normalize( &a );
	return scaler_compare( vec2_magnitude(&a), 1.0 );
}

bool test_vec2_is_normalized( void )
{
	vec2_t a = VEC2( 3.123, 12.5 );
	vec2_normalize( &a );
	return vec2_is_normalized( &a );
}

bool test_vec2_negate( void )
{
	vec2_t a = VEC2( 1, 2 );
	vec2_negate( &a );
	return scaler_compare( a.x, -1.0 ) &&
	       scaler_compare( a.y, -2.0 );
}

bool test_vec2_zero( void )
{
	vec2_t a = VEC2( 1, 2 );
	vec2_zero( &a );
	bool r1 = scaler_compare( a.x, 0.0 ) &&
	          scaler_compare( a.y, 0.0 );

	bool r2 = scaler_compare( VEC2_ZERO.x, 0.0 ) &&
	          scaler_compare( VEC2_ZERO.y, 0.0 );

	return r1 && r2;
}
