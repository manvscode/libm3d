#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vec3.h>
#include <mat3.h>
#include "test.h"

bool test_vec3_literals( void );
bool test_vec3_addition( void );
bool test_vec3_subtraction( void );
bool test_vec3_scaler_multiply( void );
bool test_vec3_magnitude( void );
bool test_vec3_dot_product( void );
bool test_vec3_distance( void );
bool test_vec3_angle( void );

bool test_vec3_normalize( void );
bool test_vec3_is_normalized( void );
bool test_vec3_negate( void );
bool test_vec3_zero( void );

bool test_vec3_nil( void ) { return false; }

const test_feature_t vec3_functions[] = {
	{ "Testing vec3 literals",                 test_vec3_literals },
	{ "Testing vec3 addition",                 test_vec3_addition },
	{ "Testing vec4 subtraction",              test_vec3_subtraction },
	{ "Testing vec3 scaler multiply",          test_vec3_scaler_multiply },
	{ "Testing vec3 magnitude (i.e. length)",  test_vec3_magnitude },
	{ "Testing vec3 dot product",              test_vec3_dot_product },
	{ "Testing vec3 distance",                 test_vec3_distance },
	{ "Testing vec3 angle",                    test_vec3_angle },
	{ "Testing vec3 normalize",                test_vec3_normalize },
	{ "Testing vec3 is normalized",            test_vec3_is_normalized },
	{ "Testing vec3 negation",                 test_vec3_negate },
	{ "Testing vec3 zero",                     test_vec3_zero },
};

int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	bool result = test_eval_features( "3D Vector Functions", vec3_functions, sizeof(vec3_functions) / sizeof(vec3_functions[0]) );
	return result ? 0 : 1;
}

bool test_vec3_literals( void )
{
	vec3_t v = VEC3( 1, 2, 3 );
	return scaler_compare( v.x, 1.0f ) &&
	       scaler_compare( v.y, 2.0f ) &&
	       scaler_compare( v.z, 3.0f );
}

bool test_vec3_addition( void )
{
	vec3_t a = VEC3( 0, 1, 2 );
	vec3_t b = VEC3( 4, -1, 2 );
	vec3_t r = vec3_add( &a, &b );
	return scaler_compare( r.x, 4.0f ) &&
	       scaler_compare( r.y, 0.0f ) &&
	       scaler_compare( r.z, 4.0f );
}

bool test_vec3_subtraction( void )
{
	vec3_t a = VEC3( 2, 2, 5 );
	vec3_t b = VEC3( -2, 2, 1 );
	vec3_t r = vec3_subtract( &a, &b );
	return scaler_compare( r.x, 4.0f ) &&
	       scaler_compare( r.y, 0.0f ) &&
	       scaler_compare( r.z, 4.0f );
}

bool test_vec3_scaler_multiply( void )
{
	vec3_t a = VEC3( 3, 2, 1 );
	scaler_t s = 0.5f;
	vec3_t r = vec3_multiply( &a, s );
	return scaler_compare( r.x, 1.5f ) &&
	       scaler_compare( r.y, 1.0f ) &&
	       scaler_compare( r.z, 0.5f );
}

bool test_vec3_magnitude( void )
{
	vec3_t a = VEC3( 3, 2, 1 );
	scaler_t r = vec3_magnitude( &a );
	return scaler_compare( r, 3.741657386773941f );
}

bool test_vec3_dot_product( void )
{
	vec3_t a = VEC3( 3, 2, 1 );
	vec3_t b = VEC3( 3, 2, 1 );
	scaler_t r1 = vec3_dot_product( &a, &b );

	vec3_t c = VEC3( 1, 2, 1 );
	vec3_t d = VEC3( 5, 3, 6 );
	scaler_t r2 = vec3_dot_product( &c, &d );

	return scaler_compare( r1, 14.0f ) &&
	       scaler_compare( r2, 17.0f );
}

bool test_vec3_distance( void )
{
	vec3_t a = VEC3( 3, 2, 1 );
	vec3_t b = VEC3( 3, 2, 1 );
	scaler_t r1 = vec3_distance( &a, &b );

	vec3_t c = VEC3( 1, 1, 1 );
	vec3_t d = VEC3( 5, 1, 6 );
	scaler_t r2 = vec3_distance( &c, &d );

	return scaler_compare( r1, 0.0f ) &&
	       scaler_compare( r2, 6.403124237432849f );
}

bool test_vec3_angle( void )
{
	vec3_t a = VEC3( 1, 1, 0 );
	vec3_t b = VEC3( 0, 1, 0 );
	scaler_t r1 = vec3_angle( &a, &b );

	vec3_t c = VEC3( 1, 0, 0 );
	vec3_t d = VEC3( 0, 1, 0 );
	scaler_t r2 = vec3_angle( &c, &d );

	return scaler_compare( r1, 45.0f * RADIANS_PER_DEGREE ) &&
	       scaler_compare( r2, 90.0f * RADIANS_PER_DEGREE );
}

bool test_vec3_normalize( void )
{
	vec3_t a = VEC3( 3.123f, 12.5f, 0.123123f );
	vec3_normalize( &a );
	return scaler_compare( vec3_magnitude(&a), 1.0f );
}

bool test_vec3_is_normalized( void )
{
	vec3_t a = VEC3( 3.123f, 12.5f, 0.123123f );
	vec3_normalize( &a );
	return vec3_is_normalized( &a );
}

bool test_vec3_negate( void )
{
	vec3_t a = VEC3( 1, 2, 3 );
	vec3_negate( &a );
	return scaler_compare( a.x, -1.0f ) &&
	       scaler_compare( a.y, -2.0f ) &&
	       scaler_compare( a.z, -3.0f );
}

bool test_vec3_zero( void )
{
	vec3_t a = VEC3( 1, 2, 3 );
	vec3_zero( &a );
	bool r1 = scaler_compare( a.x, 0.0f ) &&
	          scaler_compare( a.y, 0.0f ) &&
	          scaler_compare( a.z, 0.0f );

	bool r2 = scaler_compare( VEC3_ZERO.x, 0.0f ) &&
	          scaler_compare( VEC3_ZERO.y, 0.0f ) &&
	          scaler_compare( VEC3_ZERO.z, 0.0f );

	return r1 && r2;
}
