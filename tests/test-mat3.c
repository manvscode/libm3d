#include <stdio.h>
#include <stdlib.h>
#include <vec2.h>
#include <vec3.h>
#include <mat2.h>
#include <mat3.h>
#include "test.h"



bool test_mat3_determinant( void );
bool test_mat3_multiplcation( void );
bool test_mat3_inversion( void );

const test_feature_t mat3_functions[] = {
	{ "Testing mat3 determinants", test_mat3_determinant },
	{ "Testing mat3 multiplcation", test_mat3_multiplcation },
	{ "Testing mat3 inversion", test_mat3_inversion },
};

int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_eval_features( "3x3 Matrix Functions", mat3_functions, sizeof(mat3_functions) / sizeof(mat3_functions[0]) );
	mat3_t matrix = MAT3_IDENTITY;

	printf( "x' = %s\n", vec3_to_string( mat3_x_vector(&matrix) ) );
	printf( "y' = %s\n", vec3_to_string( mat3_y_vector(&matrix) ) );
	printf( "z' = %s\n", vec3_to_string( mat3_z_vector(&matrix) ) );

	printf( "%s\n", mat3_to_string(&matrix) );


	mat2_t A = MAT2(2, 1, 0.5, 3);
	mat2_t B = MAT2(0.33, 7, 4, -3);

	mat2_t C = mat2_mult_matrix( &A, &B );

	printf( "%s\n", mat2_to_string(&C) );
	printf( "x' = %s\n", vec2_to_string( mat2_x_vector(&C) ) );
	printf( "y' = %s\n", vec2_to_string( mat2_y_vector(&C) ) );


#if 1
	mat3_t D = MAT3(1, 0, 2, 3, 1, 1, 1, 5, 1);
	mat3_t E = MAT3(1, 1, 1, 1, 1, 1, 1, 1, 1);
	vec3_t a = VEC3(1,2,1);
	vec3_t r = mat3_mult_vector( &D, &a );



	printf( "det D = %lf\n", mat3_determinant(&D) );

	printf( "%s\n", mat3_to_string(&D) );
	printf( "%s\n", vec3_to_string(&a) );
	printf( "%s\n", vec3_to_string(&r) );

	mat3_t s = mat3_mult_matrix( &D, &E );
	printf( "%s\n", mat3_to_string(&s) );
	mat3_transpose( &s );
	printf( "%s\n", mat3_to_string(&s) );
#endif

	return 0;
}
bool test_mat3_determinant( void )
{
	mat3_t matrix1 = MAT3(
		1, 4, 3,
	    0, -1, 1,
		2, 7, 2
	);
	float d1 = mat3_determinant( &matrix1 );

	bool test1 = fabs(d1 - 5.0f) < SCALAR_EPSILON;

	mat3_t matrix2 = MAT3(1, 0, 11, 2, 7, 0, 3, 1, 2);
	mat3_invert( &matrix2 );

	bool test2 =
		(fabs( matrix2.m[0] - (-14.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[1] - (-11.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[2] - ( 77.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[3] - (  4.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[4] - ( 31.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[5] - (-22.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[6] - ( 19.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[7] - (  1.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[8] - ( -7.0f/195)) < SCALAR_EPSILON);

	return test1 && test2;
}

bool test_mat3_multiplcation( void )
{
	mat3_t a = MAT3( 1, 3, 2,
	                 2, 2, 1,
	                 3, 1, 3 );
	mat3_t b = MAT3( 4, 6, 4,
	                 5, 5, 6,
	                 6, 4, 5 );

	mat3_t r = mat3_mult_matrix( &a, &b );


	bool result = r.m[ 0 ] == 28 &&
	              r.m[ 1 ] == 28 &&
	              r.m[ 2 ] == 26 &&
	              r.m[ 3 ] == 33 &&
	              r.m[ 4 ] == 31 &&
	              r.m[ 5 ] == 33 &&
	              r.m[ 6 ] == 29 &&
	              r.m[ 7 ] == 31 &&
	              r.m[ 8 ] == 31;

	if( !result )
	{
		printf( "%s\n", mat3_to_string(&a) );
		printf( "%s\n", mat3_to_string(&b) );
		printf( "%s\n", mat3_to_string(&r) );
	}

	return result;
}

bool test_mat3_inversion( void )
{
	mat3_t matrix1 = MAT3(1, 4, 3, 0, -1, 1, 2, 7, 2);
	mat3_invert( &matrix1 );

	bool test1 =
		(fabs( matrix1.m[0] + 1.8) < SCALAR_EPSILON) &&
		(fabs( matrix1.m[1] - 2.6) < SCALAR_EPSILON) &&
		(fabs( matrix1.m[2] - 1.4) < SCALAR_EPSILON) &&
		(fabs( matrix1.m[3] - 0.4) < SCALAR_EPSILON) &&
		(fabs( matrix1.m[4] + 0.8) < SCALAR_EPSILON) &&
		(fabs( matrix1.m[5] + 0.2) < SCALAR_EPSILON) &&
		(fabs( matrix1.m[6] - 0.4) < SCALAR_EPSILON) &&
		(fabs( matrix1.m[7] - 0.2) < SCALAR_EPSILON) &&
		(fabs( matrix1.m[8] + 0.2) < SCALAR_EPSILON);

	mat3_t matrix2 = MAT3(1, 0, 11, 2, 7, 0, 3, 1, 2);
	mat3_invert( &matrix2 );

	bool test2 =
		(fabs( matrix2.m[0] - (-14.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[1] - (-11.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[2] - ( 77.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[3] - (  4.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[4] - ( 31.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[5] - (-22.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[6] - ( 19.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[7] - (  1.0f/195)) < SCALAR_EPSILON) &&
		(fabs( matrix2.m[8] - ( -7.0f/195)) < SCALAR_EPSILON);

	return test1 && test2;
}
