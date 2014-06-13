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
#include <stdio.h>
#include <stdlib.h>
#include "../src/vec3.h"
#include "../src/mat3.h"
#include "test.h"

bool test_mat3_literals              ( void );
bool test_mat3_identity              ( void );
bool test_mat3_zero                  ( void );
bool test_mat3_determinant           ( void );
bool test_mat3_matrix_multiplication ( void );
bool test_mat3_vector_multiplication ( void );
bool test_mat3_inversion             ( void );
bool test_mat3_transpose             ( void );

const test_feature_t mat3_tests[] = {
	{ "Testing mat3 literals", test_mat3_literals },
	{ "Testing mat3 identity", test_mat3_identity },
	{ "Testing mat3 zero", test_mat3_zero },
	{ "Testing mat3 determinants", test_mat3_determinant },
	{ "Testing mat3 matrix multiplcation", test_mat3_matrix_multiplication },
	{ "Testing mat3 vector multiplcation", test_mat3_vector_multiplication },
	{ "Testing mat3 inversion", test_mat3_inversion },
	{ "Testing mat3 transpose", test_mat3_transpose },
};

size_t mat3_test_suite_size( void )
{
	return sizeof(mat3_tests) / sizeof(mat3_tests[0]);
}


#ifdef TEST_MAT3_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "3x3 Matrix Functions", mat3_tests, mat3_test_suite_size() );
	return 0;
}
#endif

bool test_mat3_literals( void )
{
	mat3_t m = MAT3(
		1, 2, 3,
	    4, 5, 6,
		7, 8, 9
	);

	return scaler_compare( m.m[0], 1 ) &&
	       scaler_compare( m.m[1], 2 ) &&
	       scaler_compare( m.m[2], 3 ) &&
	       scaler_compare( m.m[3], 4 ) &&
	       scaler_compare( m.m[4], 5 ) &&
	       scaler_compare( m.m[5], 6 ) &&
	       scaler_compare( m.m[6], 7 ) &&
	       scaler_compare( m.m[7], 8 ) &&
	       scaler_compare( m.m[8], 9 );
}

bool test_mat3_identity( void )
{
	mat3_t m = MAT3_IDENTITY;

	return scaler_compare( m.m[0], 1 ) &&
	       scaler_compare( m.m[1], 0 ) &&
	       scaler_compare( m.m[2], 0 ) &&
	       scaler_compare( m.m[3], 0 ) &&
	       scaler_compare( m.m[4], 1 ) &&
	       scaler_compare( m.m[5], 0 ) &&
	       scaler_compare( m.m[6], 0 ) &&
	       scaler_compare( m.m[7], 0 ) &&
	       scaler_compare( m.m[8], 1 );
}
bool test_mat3_zero( void )
{
	mat3_t m = MAT3_ZERO;

	return scaler_compare( m.m[0], 0 ) &&
	       scaler_compare( m.m[1], 0 ) &&
	       scaler_compare( m.m[2], 0 ) &&
	       scaler_compare( m.m[3], 0 ) &&
	       scaler_compare( m.m[4], 0 ) &&
	       scaler_compare( m.m[5], 0 ) &&
	       scaler_compare( m.m[6], 0 ) &&
	       scaler_compare( m.m[7], 0 ) &&
	       scaler_compare( m.m[8], 0 );
}

bool test_mat3_determinant( void )
{
	mat3_t a = MAT3(
		1, 4, 3,
	    0, -1, 1,
		2, 7, 2
	);
	float d1 = mat3_determinant( &a );
	bool test1 = scaler_compare( d1, 5.0 );

	mat3_t b = MAT3(
		3, 6, 6,
	    1, 3, 8,
		8, 0, 8
	);
	float d2 = mat3_determinant( &b );
	bool test2 = scaler_compare( d2, 264.0 );

	return test1 && test2;
}

bool test_mat3_matrix_multiplication( void )
{
	mat3_t a = MAT3( 1, 3, 2,
	                 2, 2, 1,
	                 3, 1, 3 );
	mat3_t b = MAT3( 4, 6, 4,
	                 5, 5, 6,
	                 6, 4, 5 );

	mat3_t ab = mat3_mult_matrix( &a, &b );

	bool r1 = scaler_compare( ab.m[0], 28 ) &&
	          scaler_compare( ab.m[1], 28 ) &&
	          scaler_compare( ab.m[2], 26 ) &&
	          scaler_compare( ab.m[3], 33 ) &&
	          scaler_compare( ab.m[4], 31 ) &&
	          scaler_compare( ab.m[5], 33 ) &&
	          scaler_compare( ab.m[6], 29 ) &&
	          scaler_compare( ab.m[7], 31 ) &&
	          scaler_compare( ab.m[8], 31 );

	return r1;
}

bool test_mat3_vector_multiplication( void )
{
	mat3_t a = MAT3( 1, -2, 3,
	                 4, 7, 2,
	                 -2, 1, 1 );
	vec3_t b = VEC3( 1, 2, 3 );
	vec3_t r1 = mat3_mult_vector( &a, &b );
	bool test1 = scaler_compare( r1.x, 3) &&
	             scaler_compare( r1.y, 15 ) &&
	             scaler_compare( r1.z, 10 );

	mat3_t c = MAT3( 1, -3, 5,
	                 0, 1, -4,
	                 2, 7, 0 );
	vec3_t d = VEC3( -1, 2, -1 );
	vec3_t r2 = mat3_mult_vector( &c, &d );
	bool test2 = scaler_compare( r2.x, -3) &&
	             scaler_compare( r2.y, -2 ) &&
	             scaler_compare( r2.z, -13 );

	return test1 && test2;
}

bool test_mat3_inversion( void )
{
	mat3_t m1 = MAT3(1, 4, 3, 0, -1, 1, 2, 7, 2);
	mat3_invert( &m1 );

	bool test1 = scaler_compare( m1.m[0], -1.8 ) &&
	             scaler_compare( m1.m[1], 2.6 ) &&
	             scaler_compare( m1.m[2], 1.4 ) &&
	             scaler_compare( m1.m[3], 0.4 ) &&
	             scaler_compare( m1.m[4], -0.8 ) &&
	             scaler_compare( m1.m[5], -0.2 ) &&
	             scaler_compare( m1.m[6], 0.4 ) &&
	             scaler_compare( m1.m[7], 0.2 ) &&
	             scaler_compare( m1.m[8], -0.2 );

	mat3_t m2 = MAT3(1, 0, 11, 2, 7, 0, 3, 1, 2);
	mat3_invert( &m2 );

	bool test2 = scaler_compare( m2.m[0], (-14.0/195) ) &&
	             scaler_compare( m2.m[1], (-11.0/195) ) &&
	             scaler_compare( m2.m[2], ( 77.0/195) ) &&
	             scaler_compare( m2.m[3], (  4.0/195) ) &&
	             scaler_compare( m2.m[4], ( 31.0/195) ) &&
	             scaler_compare( m2.m[5], (-22.0/195) ) &&
	             scaler_compare( m2.m[6], ( 19.0/195) ) &&
	             scaler_compare( m2.m[7], (  1.0/195) ) &&
	             scaler_compare( m2.m[8], ( -7.0/195) );

	mat3_t m3 = MAT3(
		1, 0, 11,
		2, 7, 0,
		3, 1, 2
	);
	mat3_invert( &m3 );

	bool test3 = scaler_compare( m3.m[0], (-14.0/195) ) &&
		         scaler_compare( m3.m[1], (-11.0/195) ) &&
		         scaler_compare( m3.m[2], ( 77.0/195) ) &&
		         scaler_compare( m3.m[3], (  4.0/195) ) &&
		         scaler_compare( m3.m[4], ( 31.0/195) ) &&
		         scaler_compare( m3.m[5], (-22.0/195) ) &&
		         scaler_compare( m3.m[6], ( 19.0/195) ) &&
		         scaler_compare( m3.m[7], (  1.0/195) ) &&
		         scaler_compare( m3.m[8], ( -7.0/195) );

	return test1 && test2 && test3;
}

bool test_mat3_transpose( void )
{
	mat3_t m1 = MAT3(
		1, 4, 3,
		0, 1, 1,
		2, 7, 2
	);
	mat3_transpose( &m1 );
	bool test1 = scaler_compare( m1.m[0], 1 ) &&
		         scaler_compare( m1.m[1], 0 ) &&
		         scaler_compare( m1.m[2], 2 ) &&
		         scaler_compare( m1.m[3], 4 ) &&
		         scaler_compare( m1.m[4], 1 ) &&
		         scaler_compare( m1.m[5], 7 ) &&
		         scaler_compare( m1.m[6], 3 ) &&
		         scaler_compare( m1.m[7], 1 ) &&
		         scaler_compare( m1.m[8], 2 );

	mat3_t m2 = MAT3(
		 5, -3, 1,
		-4,  0, 8,
		 2, 11, 0
	);
	mat3_transpose( &m2 );
	bool test2 = scaler_compare( m2.m[0], 5 ) &&
		         scaler_compare( m2.m[1], -4 ) &&
		         scaler_compare( m2.m[2], 2 ) &&
		         scaler_compare( m2.m[3], -3 ) &&
		         scaler_compare( m2.m[4], 0 ) &&
		         scaler_compare( m2.m[5], 11 ) &&
		         scaler_compare( m2.m[6], 1 ) &&
		         scaler_compare( m2.m[7], 8 ) &&
		         scaler_compare( m2.m[8], 0 );

	return test1 && test2;
}
