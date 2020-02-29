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
#include "../src/vec3.h"
#include "test.h"

bool test_vec3_literals        ( void );
bool test_vec3_addition        ( void );
bool test_vec3_subtraction     ( void );
bool test_vec3_scaler_multiply ( void );
bool test_vec3_magnitude       ( void );
bool test_vec3_dot_product     ( void );
bool test_vec3_cross_product   ( void );
bool test_vec3_distance        ( void );
bool test_vec3_angle           ( void );
bool test_vec3_normalize       ( void );
bool test_vec3_is_normalized   ( void );
bool test_vec3_negate          ( void );
bool test_vec3_zero            ( void );

const test_feature_t vec3_tests[] = {
	{ "Testing vec3 literals",                 test_vec3_literals },
	{ "Testing vec3 addition",                 test_vec3_addition },
	{ "Testing vec3 subtraction",              test_vec3_subtraction },
	{ "Testing vec3 scaler multiply",          test_vec3_scaler_multiply },
	{ "Testing vec3 magnitude (i.e. length)",  test_vec3_magnitude },
	{ "Testing vec3 dot product",              test_vec3_dot_product },
	{ "Testing vec3 cross product",            test_vec3_cross_product },
	{ "Testing vec3 distance",                 test_vec3_distance },
	{ "Testing vec3 angle",                    test_vec3_angle },
	{ "Testing vec3 normalize",                test_vec3_normalize },
	{ "Testing vec3 is normalized",            test_vec3_is_normalized },
	{ "Testing vec3 negation",                 test_vec3_negate },
	{ "Testing vec3 zero",                     test_vec3_zero },
};

size_t vec3_test_suite_size( void )
{
	return sizeof(vec3_tests) / sizeof(vec3_tests[0]);
}

#ifdef TEST_VEC3_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	bool result = test_features( "3D Vector Functions", vec3_tests, vec3_test_suite_size() );
	return result ? 0 : 1;
}
#endif

bool test_vec3_literals( void )
{
	vec3_t v = VEC3( 1, 2, 3 );
	return scaler_compare( v.x, 1.0 ) &&
	       scaler_compare( v.y, 2.0 ) &&
	       scaler_compare( v.z, 3.0 );
}

bool test_vec3_addition( void )
{
	vec3_t a = VEC3( 0, 1, 2 );
	vec3_t b = VEC3( 4, -1, 2 );
	vec3_t r = vec3_add( &a, &b );
	return scaler_compare( r.x, 4.0 ) &&
	       scaler_compare( r.y, 0.0 ) &&
	       scaler_compare( r.z, 4.0 );
}

bool test_vec3_subtraction( void )
{
	vec3_t a = VEC3( 2, 2, 5 );
	vec3_t b = VEC3( -2, 2, 1 );
	vec3_t r = vec3_subtract( &a, &b );
	return scaler_compare( r.x, 4.0 ) &&
	       scaler_compare( r.y, 0.0 ) &&
	       scaler_compare( r.z, 4.0 );
}

bool test_vec3_scaler_multiply( void )
{
	vec3_t a = VEC3( 3, 2, 1 );
	scaler_t s = 0.5;
	vec3_t r = vec3_multiply( &a, s );
	return scaler_compare( r.x, 1.5 ) &&
	       scaler_compare( r.y, 1.0 ) &&
	       scaler_compare( r.z, 0.5 );
}

bool test_vec3_magnitude( void )
{
	vec3_t a = VEC3( 3, 2, 1 );
	scaler_t r = vec3_magnitude( &a );
	return scaler_compare( r, 3.7416573867739413 );
}

bool test_vec3_dot_product( void )
{
	vec3_t a = VEC3( 3, 2, 1 );
	vec3_t b = VEC3( 3, 2, 1 );
	scaler_t r1 = vec3_dot_product( &a, &b );

	vec3_t c = VEC3( 1, 2, 1 );
	vec3_t d = VEC3( 5, 3, 6 );
	scaler_t r2 = vec3_dot_product( &c, &d );

	return scaler_compare( r1, 14.0 ) &&
	       scaler_compare( r2, 17.0 );
}

bool test_vec3_cross_product( void )
{
	vec3_t a = VEC3( 1, 0, 0 );
	vec3_t b = VEC3( 0, 1, 0 );
	vec3_t c1 = vec3_cross_product( &a, &b );

	bool r1 = scaler_compare( c1.x, 0.0 ) &&
	          scaler_compare( c1.y, 0.0 ) &&
	          scaler_compare( c1.z, 1.0 );

	vec3_t c = VEC3( 3, -3, 1 );
	vec3_t d = VEC3( 4, 9, 2 );
	vec3_t c2 = vec3_cross_product( &c, &d );

	bool r2 = scaler_compare( c2.x, -15.0 ) &&
	          scaler_compare( c2.y, -2.0 ) &&
	          scaler_compare( c2.z, 39.0 );

	return r1 && r2;
}

bool test_vec3_distance( void )
{
	vec3_t a = VEC3( 3, 2, 1 );
	vec3_t b = VEC3( 3, 2, 1 );
	scaler_t r1 = vec3_distance( &a, &b );

	vec3_t c = VEC3( 1, 1, 1 );
	vec3_t d = VEC3( 5, 1, 6 );
	scaler_t r2 = vec3_distance( &c, &d );

	return scaler_compare( r1, 0.0 ) &&
	       scaler_compare( r2, 6.4031242374328485 );
}

bool test_vec3_angle( void )
{
	vec3_t a = VEC3( 1, 1, 0 );
	vec3_t b = VEC3( 0, 1, 0 );
	scaler_t r1 = vec3_angle( &a, &b );

	vec3_t c = VEC3( 1, 0, 0 );
	vec3_t d = VEC3( 0, 1, 0 );
	scaler_t r2 = vec3_angle( &c, &d );

	return scaler_compare( r1, 45.0 * M3D_RADIANS_PER_DEGREE ) &&
	       scaler_compare( r2, 90.0 * M3D_RADIANS_PER_DEGREE );
}

bool test_vec3_normalize( void )
{
	vec3_t a = VEC3( 3.123, 12.5, 0.123123 );
	vec3_normalize( &a );
	return scaler_compare( vec3_magnitude(&a), 1.0 );
}

bool test_vec3_is_normalized( void )
{
	vec3_t a = VEC3( 3.123, 12.5, 0.123123 );
	vec3_normalize( &a );
	return vec3_is_normalized( &a );
}

bool test_vec3_negate( void )
{
	vec3_t a = VEC3( 1, 2, 3 );
	vec3_negate( &a );
	return scaler_compare( a.x, -1.0 ) &&
	       scaler_compare( a.y, -2.0 ) &&
	       scaler_compare( a.z, -3.0 );
}

bool test_vec3_zero( void )
{
	vec3_t a = VEC3( 1, 2, 3 );
	vec3_zero( &a );
	bool r1 = scaler_compare( a.x, 0.0 ) &&
	          scaler_compare( a.y, 0.0 ) &&
	          scaler_compare( a.z, 0.0 );

	bool r2 = scaler_compare( VEC3_ZERO.x, 0.0 ) &&
	          scaler_compare( VEC3_ZERO.y, 0.0 ) &&
	          scaler_compare( VEC3_ZERO.z, 0.0 );

	return r1 && r2;
}
