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
#include "../src/vec2.h"
#include "../src/mat2.h"
#include "test.h"

bool test_mat2_literals              ( void );
bool test_mat2_identity              ( void );
bool test_mat2_zero                  ( void );
bool test_mat2_determinant           ( void );
bool test_mat2_matrix_multiplication ( void );
bool test_mat2_vector_multiplication ( void );
bool test_mat2_inversion             ( void );
bool test_mat2_transpose             ( void );

const test_feature_t mat2_tests[] = {
	{ "Testing mat2 literals", test_mat2_literals },
	{ "Testing mat2 identity", test_mat2_identity },
	{ "Testing mat2 zero", test_mat2_zero },
	{ "Testing mat2 determinants", test_mat2_determinant },
	{ "Testing mat2 matrix multiplcation", test_mat2_matrix_multiplication },
	{ "Testing mat2 vector multiplcation", test_mat2_vector_multiplication },
	{ "Testing mat2 inversion", test_mat2_inversion },
	{ "Testing mat2 transpose", test_mat2_transpose },
};

size_t mat2_test_suite_size( void )
{
	return sizeof(mat2_tests) / sizeof(mat2_tests[0]);
}


#ifdef TEST_MAT2_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "2x2 Matrix Functions", mat2_tests, mat2_test_suite_size() );
	return 0;
}
#endif

bool test_mat2_literals( void )
{
	mat2_t m = MAT2(
		1, 2,
	    3, 4
	);

	return scaler_compare( m.m[0], 1 ) &&
	       scaler_compare( m.m[1], 2 ) &&
	       scaler_compare( m.m[2], 3 ) &&
	       scaler_compare( m.m[3], 4 );
}

bool test_mat2_identity( void )
{
	mat2_t m = MAT2_IDENTITY;

	return scaler_compare( m.m[0], 1 ) &&
	       scaler_compare( m.m[1], 0 ) &&
	       scaler_compare( m.m[2], 0 ) &&
	       scaler_compare( m.m[3], 1 );
}
bool test_mat2_zero( void )
{
	mat2_t m = MAT2_ZERO;

	return scaler_compare( m.m[0], 0 ) &&
	       scaler_compare( m.m[1], 0 ) &&
	       scaler_compare( m.m[2], 0 ) &&
	       scaler_compare( m.m[3], 0 );
}

bool test_mat2_determinant( void )
{
	mat2_t a = MAT2(
		 1, 4,
	    -1, 1
	);
	float d1 = mat2_determinant( &a );
	bool test1 = scaler_compare( d1, 5.0 );

	mat2_t b = MAT2(
		3, 6,
	    1, 3
	);
	float d2 = mat2_determinant( &b );
	bool test2 = scaler_compare( d2, 3.0 );

	return test1 && test2;
}

bool test_mat2_matrix_multiplication( void )
{
	mat2_t a = MAT2( 1, 3,
	                 3, 1 );
	mat2_t b = MAT2( 1, 5,
	                 6, 4 );
	mat2_t ab = mat2_mult_matrix( &a, &b );
	bool r1 = scaler_compare( ab.m[0], 16 ) &&
	          scaler_compare( ab.m[1], 8 ) &&
	          scaler_compare( ab.m[2], 18 ) &&
	          scaler_compare( ab.m[3], 22 );

	return r1;
}

bool test_mat2_vector_multiplication( void )
{
	mat2_t a = MAT2( 1, -2,
	                 4,  7 );
	vec2_t b = VEC2( 1, 2 );
	vec2_t r1 = mat2_mult_vector( &a, &b );
	bool test1 = scaler_compare( r1.x, 9) &&
	             scaler_compare( r1.y, 12 );

	mat2_t c = MAT2( 1, -3,
	                 0,  1 );
	vec2_t d = VEC2( -1, 2 );
	vec2_t r2 = mat2_mult_vector( &c, &d );
	bool test2 = scaler_compare( r2.x, -1) &&
	             scaler_compare( r2.y, 5 );

	return test1 && test2;
}

bool test_mat2_inversion( void )
{
	mat2_t m1 = MAT2(1, 4, 3, 0);
	mat2_invert( &m1 );
	bool test1 = scaler_compare( m1.m[0], 0 ) &&
	             scaler_compare( m1.m[1], (1.0/3) ) &&
	             scaler_compare( m1.m[2], (1.0/4) ) &&
	             scaler_compare( m1.m[3], (-1.0/12) );

	mat2_t m2 = MAT2(1, 0, 11, 2);
	mat2_invert( &m2 );
	bool test2 = scaler_compare( m2.m[0], 1.0 ) &&
	             scaler_compare( m2.m[1], 0.0 ) &&
	             scaler_compare( m2.m[2], (-11.0/2) ) &&
	             scaler_compare( m2.m[3], (  1.0/2) );

	mat2_t m3 = MAT2(
		1, 0,
		2, 7
	);
	mat2_invert( &m3 );
	bool test3 = scaler_compare( m3.m[0], 1.0 ) &&
		         scaler_compare( m3.m[1], 0.0 ) &&
		         scaler_compare( m3.m[2], (-2.0/7) ) &&
		         scaler_compare( m3.m[3], ( 1.0/7) );

	return test1 && test2 && test3;
}

bool test_mat2_transpose( void )
{
	mat2_t m1 = MAT2(
		4, 3,
		1, 7
	);
	mat2_transpose( &m1 );
	bool test1 = scaler_compare( m1.m[0], 4 ) &&
		         scaler_compare( m1.m[1], 1 ) &&
		         scaler_compare( m1.m[2], 3 ) &&
		         scaler_compare( m1.m[3], 7 );

	mat2_t m2 = MAT2(
		 5, -3,
		-4,  0
	);
	mat2_transpose( &m2 );
	bool test2 = scaler_compare( m2.m[0], 5 ) &&
		         scaler_compare( m2.m[1], -4 ) &&
		         scaler_compare( m2.m[2], -3 ) &&
		         scaler_compare( m2.m[3], 0 );

	return test1 && test2;
}
