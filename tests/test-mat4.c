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
#include "../src/vec4.h"
#include "../src/mat4.h"
#include "test.h"

bool test_mat4_literals              ( void );
bool test_mat4_identity              ( void );
bool test_mat4_zero                  ( void );
bool test_mat4_determinant           ( void );
bool test_mat4_matrix_multiplication ( void );
bool test_mat4_vector_multiplication ( void );
bool test_mat4_inversion             ( void );
bool test_mat4_transpose             ( void );

const test_feature_t mat4_tests[] = {
	{ "Testing mat4 literals", test_mat4_literals },
	{ "Testing mat4 identity", test_mat4_identity },
	{ "Testing mat4 zero", test_mat4_zero },
	{ "Testing mat4 determinants", test_mat4_determinant },
	{ "Testing mat4 matrix multiplcation", test_mat4_matrix_multiplication },
	{ "Testing mat4 vector multiplcation", test_mat4_vector_multiplication },
	{ "Testing mat4 inversion", test_mat4_inversion },
	{ "Testing mat4 transpose", test_mat4_transpose },
};

size_t mat4_test_suite_size( void )
{
	return sizeof(mat4_tests) / sizeof(mat4_tests[0]);
}


#ifdef TEST_MAT4_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "4x4 Matrix Functions", mat4_tests, mat4_test_suite_size() );
	return 0;
}
#endif

bool test_mat4_literals( void )
{
	mat4_t m = MAT4(
		 1,  2,  3,  4,
	     5,  6,  7,  8,
		 9, 10, 11, 12,
		13, 14, 15, 16
	);

	return scaler_compare( m.m[ 0], 1 ) &&
	       scaler_compare( m.m[ 1], 2 ) &&
	       scaler_compare( m.m[ 2], 3 ) &&
	       scaler_compare( m.m[ 3], 4 ) &&
	       scaler_compare( m.m[ 4], 5 ) &&
	       scaler_compare( m.m[ 5], 6 ) &&
	       scaler_compare( m.m[ 6], 7 ) &&
	       scaler_compare( m.m[ 7], 8 ) &&
	       scaler_compare( m.m[ 8], 9 ) &&
	       scaler_compare( m.m[ 9], 10 ) &&
	       scaler_compare( m.m[10], 11 ) &&
	       scaler_compare( m.m[11], 12 ) &&
	       scaler_compare( m.m[12], 13 ) &&
	       scaler_compare( m.m[13], 14 ) &&
	       scaler_compare( m.m[14], 15 ) &&
	       scaler_compare( m.m[15], 16 );
}

bool test_mat4_identity( void )
{
	mat4_t m = MAT4_IDENTITY;

	return scaler_compare( m.m[ 0], 1 ) &&
	       scaler_compare( m.m[ 1], 0 ) &&
	       scaler_compare( m.m[ 2], 0 ) &&
	       scaler_compare( m.m[ 3], 0 ) &&
	       scaler_compare( m.m[ 4], 0 ) &&
	       scaler_compare( m.m[ 5], 1 ) &&
	       scaler_compare( m.m[ 6], 0 ) &&
	       scaler_compare( m.m[ 7], 0 ) &&
	       scaler_compare( m.m[ 8], 0 ) &&
	       scaler_compare( m.m[ 9], 0 ) &&
	       scaler_compare( m.m[10], 1 ) &&
	       scaler_compare( m.m[11], 0 ) &&
	       scaler_compare( m.m[12], 0 ) &&
	       scaler_compare( m.m[13], 0 ) &&
	       scaler_compare( m.m[14], 0 ) &&
	       scaler_compare( m.m[15], 1 );
}
bool test_mat4_zero( void )
{
	mat4_t m = MAT4_ZERO;

	return scaler_compare( m.m[ 0], 0 ) &&
	       scaler_compare( m.m[ 1], 0 ) &&
	       scaler_compare( m.m[ 2], 0 ) &&
	       scaler_compare( m.m[ 3], 0 ) &&
	       scaler_compare( m.m[ 4], 0 ) &&
	       scaler_compare( m.m[ 5], 0 ) &&
	       scaler_compare( m.m[ 6], 0 ) &&
	       scaler_compare( m.m[ 7], 0 ) &&
	       scaler_compare( m.m[ 8], 0 ) &&
	       scaler_compare( m.m[ 9], 0 ) &&
	       scaler_compare( m.m[10], 0 ) &&
	       scaler_compare( m.m[11], 0 ) &&
	       scaler_compare( m.m[12], 0 ) &&
	       scaler_compare( m.m[13], 0 ) &&
	       scaler_compare( m.m[14], 0 ) &&
	       scaler_compare( m.m[15], 0 );
}

bool test_mat4_determinant( void )
{
	mat4_t a = MAT4(
		1,  4, 3, -8,
	    0, -1, 1,  2,
		2,  7, 2, -1,
		0,  1, 0,  1
	);
	float d1 = mat4_determinant( &a );
	bool test1 = scaler_compare( d1, 28.0 );

	mat4_t b = MAT4(
		 3,  6,  6,  0,
	     1,  3,  8,  1,
		 8,  0,  8,  0,
		-1,  1,  0,  1
	);
	float d2 = mat4_determinant( &b );
	bool test2 = scaler_compare( d2, 240.0 );

	return test1 && test2;
}

bool test_mat4_matrix_multiplication( void )
{
	mat4_t a = MAT4(
		1,  0,  0,  0,
	    0,  1,  0,  0,
	    0,  0,  1,  0,
		0,  0,  0,  1
	);
	mat4_t b = MAT4(
		 1,  2,  3,  4,
	     5,  6,  7,  8,
	     9, 10, 11, 12,
		13, 14, 15, 16
	);
	mat4_t ab = mat4_mult_matrix( &a, &b );
	bool r1 = scaler_compare( ab.m[ 0], 1 ) &&
	          scaler_compare( ab.m[ 1], 2 ) &&
	          scaler_compare( ab.m[ 2], 3 ) &&
	          scaler_compare( ab.m[ 3], 4 ) &&
	          scaler_compare( ab.m[ 4], 5 ) &&
	          scaler_compare( ab.m[ 5], 6 ) &&
	          scaler_compare( ab.m[ 6], 7 ) &&
	          scaler_compare( ab.m[ 7], 8 ) &&
	          scaler_compare( ab.m[ 8], 9 ) &&
	          scaler_compare( ab.m[ 9], 10 ) &&
	          scaler_compare( ab.m[10], 11 ) &&
	          scaler_compare( ab.m[11], 12 ) &&
	          scaler_compare( ab.m[12], 13 ) &&
	          scaler_compare( ab.m[13], 14 ) &&
	          scaler_compare( ab.m[14], 15 ) &&
	          scaler_compare( ab.m[15], 16 );

	mat4_t c = MAT4(
		1,  1,  1,  1,
	    1,  1,  1,  1,
	    1,  1,  1,  1,
		1,  1,  1,  1
	);
	mat4_t d = MAT4(
		 1,  2,  3,  4,
	     5,  6,  7,  8,
	     9, 10, 11, 12,
		13, 14, 15, 16
	);
	mat4_t cd = mat4_mult_matrix( &c, &d );
	bool r2 = scaler_compare( cd.m[ 0], 10 ) &&
	          scaler_compare( cd.m[ 1], 10 ) &&
	          scaler_compare( cd.m[ 2], 10 ) &&
	          scaler_compare( cd.m[ 3], 10 ) &&
	          scaler_compare( cd.m[ 4], 26 ) &&
	          scaler_compare( cd.m[ 5], 26 ) &&
	          scaler_compare( cd.m[ 6], 26 ) &&
	          scaler_compare( cd.m[ 7], 26 ) &&
	          scaler_compare( cd.m[ 8], 42 ) &&
	          scaler_compare( cd.m[ 9], 42 ) &&
	          scaler_compare( cd.m[10], 42 ) &&
	          scaler_compare( cd.m[11], 42 ) &&
	          scaler_compare( cd.m[12], 58 ) &&
	          scaler_compare( cd.m[13], 58 ) &&
	          scaler_compare( cd.m[14], 58 ) &&
	          scaler_compare( cd.m[15], 58 );

	mat4_t e = MAT4(
		1,  3,  2,  0,
	    2,  2,  1,  1,
	    3,  1,  3,  5,
		0, -1, -1,  0
	);
	mat4_t f = MAT4(
		1,  0,  2,  0,
	    2, -2,  2,  1,
	    0,  7,  1,  4,
		0, -1, -3,  0
	);
	mat4_t ef = mat4_mult_matrix( &e, &f );
	bool r3 = scaler_compare( ef.m[ 0], 7 ) &&
	          scaler_compare( ef.m[ 1], 5 ) &&
	          scaler_compare( ef.m[ 2], 8 ) &&
	          scaler_compare( ef.m[ 3], 10 ) &&
	          scaler_compare( ef.m[ 4], 4 ) &&
	          scaler_compare( ef.m[ 5], 3 ) &&
	          scaler_compare( ef.m[ 6], 7 ) &&
	          scaler_compare( ef.m[ 7], 8 ) &&
	          scaler_compare( ef.m[ 8], 17 ) &&
	          scaler_compare( ef.m[ 9], 11 ) &&
	          scaler_compare( ef.m[10], 6 ) &&
	          scaler_compare( ef.m[11], 12 ) &&
	          scaler_compare( ef.m[12], -11 ) &&
	          scaler_compare( ef.m[13], -5 ) &&
	          scaler_compare( ef.m[14], -10 ) &&
	          scaler_compare( ef.m[15], -16 );

	return r1 && r2 && r3;
}

bool test_mat4_vector_multiplication( void )
{
	mat4_t a = MAT4_IDENTITY;
	vec4_t b = VEC4( 1, 2, 3, 4);
	vec4_t ab = mat4_mult_vector( &a, &b );
	bool r1 = scaler_compare( ab.x, 1 ) &&
	          scaler_compare( ab.y, 2 ) &&
	          scaler_compare( ab.z, 3 ) &&
	          scaler_compare( ab.w, 4 );

	mat4_t c = MAT4(
		1,  1,  1,  1,
	    1,  1,  1,  1,
	    1,  1,  1,  1,
		1,  1,  1,  1
	);
	vec4_t d = VEC4( 1, 2, 3, 4);
	vec4_t cd = mat4_mult_vector( &c, &d );
	bool r2 = scaler_compare( cd.x, 10 ) &&
	          scaler_compare( cd.y, 10 ) &&
	          scaler_compare( cd.z, 10 ) &&
	          scaler_compare( cd.w, 10 );

	mat4_t e = MAT4(
		 1,  2,  3,  4,
	     5,  6,  7,  8,
	     9, 10, 11, 12,
		13, 14, 15, 16
	);
	vec4_t f = VEC4( 1, -2, 3, -4);
	vec4_t ef = mat4_mult_vector( &e, &f );
	bool r3 = scaler_compare( ef.x, -34 ) &&
	          scaler_compare( ef.y, -36 ) &&
	          scaler_compare( ef.z, -38 ) &&
	          scaler_compare( ef.w, -40 );

	return r1 && r2 && r3;
}

bool test_mat4_inversion( void )
{
	mat4_t a = MAT4(
		1,  1,  1,  1,
	    1,  1,  1,  1,
	    1,  1,  1,  1,
		1,  1,  1,  1
	);
	bool r1 = mat4_invert( &a ) == false;

	mat4_t b = MAT4(
		 1,  5, -4,  0,
	     0,  7,  4,  1,
	     3,  0,  1,  3,
		 8,  1,  0,  1
	);
	mat4_invert( &b );
	bool r2 = scaler_compare( b.m[ 0], (  -9.0/481) ) &&
	          scaler_compare( b.m[ 1], (  -7.0/962) ) &&
	          scaler_compare( b.m[ 2], ( -22.0/481) ) &&
	          scaler_compare( b.m[ 3], ( 139.0/962) ) &&
	          scaler_compare( b.m[ 4], (  38.0/481) ) &&
	          scaler_compare( b.m[ 5], (  83.0/962) ) &&
	          scaler_compare( b.m[ 6], ( -14.0/481) ) &&
	          scaler_compare( b.m[ 7], (   1.0/962) ) &&
	          scaler_compare( b.m[ 8], ( -75.0/481) ) &&
	          scaler_compare( b.m[ 9], (  51.0/481) ) &&
	          scaler_compare( b.m[10], ( -23.0/481) ) &&
	          scaler_compare( b.m[11], (  18.0/481) ) &&
	          scaler_compare( b.m[12], (  34.0/481) ) &&
	          scaler_compare( b.m[13], ( -27.0/962) ) &&
	          scaler_compare( b.m[14], ( 190.0/481) ) &&
	          scaler_compare( b.m[15], (-151.0/962) );

	mat4_t c = MAT4(
		 1,  0,  0,  5,
	     0,  7,  0,  0,
	     5,  1,  2,  0,
		 0,  0,  0,  1
	);
	mat4_invert( &c );
	bool r3 = scaler_compare( c.m[ 0], 1.0 ) &&
	          scaler_compare( c.m[ 1], 0.0 ) &&
	          scaler_compare( c.m[ 2], 0.0 ) &&
	          scaler_compare( c.m[ 3], -5.0 ) &&
	          scaler_compare( c.m[ 4], 0.0 ) &&
	          scaler_compare( c.m[ 5], (1.0/7) ) &&
	          scaler_compare( c.m[ 6], 0.0 ) &&
	          scaler_compare( c.m[ 7], 0.0 ) &&
	          scaler_compare( c.m[ 8], (-5.0/2) ) &&
	          scaler_compare( c.m[ 9], (-1.0/14) ) &&
	          scaler_compare( c.m[10], ( 1.0/2) ) &&
	          scaler_compare( c.m[11], (25.0/2) ) &&
	          scaler_compare( c.m[12], 0.0 ) &&
	          scaler_compare( c.m[13], 0.0 ) &&
	          scaler_compare( c.m[14], 0.0 ) &&
	          scaler_compare( c.m[15], 1.0 );

	return r1 && r2 && r3;
}

bool test_mat4_transpose( void )
{
	mat4_t a = MAT4(
		 1,  2,  3,  4,
	     5,  6,  7,  8,
	     9, 10, 11, 12,
		13, 14, 15, 16
	);
	mat4_transpose( &a );
	bool r1 = scaler_compare( a.m[ 0], 1 ) &&
	          scaler_compare( a.m[ 1], 5 ) &&
	          scaler_compare( a.m[ 2], 9 ) &&
	          scaler_compare( a.m[ 3], 13 ) &&
	          scaler_compare( a.m[ 4], 2 ) &&
	          scaler_compare( a.m[ 5], 6 ) &&
	          scaler_compare( a.m[ 6], 10 ) &&
	          scaler_compare( a.m[ 7], 14 ) &&
	          scaler_compare( a.m[ 8], 3 ) &&
	          scaler_compare( a.m[ 9], 7 ) &&
	          scaler_compare( a.m[10], 11 ) &&
	          scaler_compare( a.m[11], 15 ) &&
	          scaler_compare( a.m[12], 4 ) &&
	          scaler_compare( a.m[13], 8 ) &&
	          scaler_compare( a.m[14], 12 ) &&
	          scaler_compare( a.m[15], 16 );

	return r1;
}
