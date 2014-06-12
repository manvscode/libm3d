#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <vec4.h>
#include "test.h"

bool test_vec4_literals        ( void );
bool test_vec4_addition        ( void );
bool test_vec4_subtraction     ( void );
bool test_vec4_scaler_multiply ( void );
bool test_vec4_magnitude       ( void );
bool test_vec4_dot_product     ( void );
bool test_vec4_distance        ( void );
bool test_vec4_angle           ( void );
bool test_vec4_normalize       ( void );
bool test_vec4_is_normalized   ( void );
bool test_vec4_negate          ( void );
bool test_vec4_zero            ( void );

const test_feature_t vec4_tests[] = {
	{ "Testing vec4 literals",                 test_vec4_literals },
	{ "Testing vec4 addition",                 test_vec4_addition },
	{ "Testing vec4 subtraction",              test_vec4_subtraction },
	{ "Testing vec4 scaler multiply",          test_vec4_scaler_multiply },
	{ "Testing vec4 magnitude (i.e. length)",  test_vec4_magnitude },
	{ "Testing vec4 dot product",              test_vec4_dot_product },
	{ "Testing vec4 distance",                 test_vec4_distance },
	{ "Testing vec4 angle",                    test_vec4_angle },
	{ "Testing vec4 normalize",                test_vec4_normalize },
	{ "Testing vec4 is normalized",            test_vec4_is_normalized },
	{ "Testing vec4 negation",                 test_vec4_negate },
	{ "Testing vec4 zero",                     test_vec4_zero },
};

size_t vec4_test_suite_size( void )
{
	return sizeof(vec4_tests) / sizeof(vec4_tests[0]);
}

#ifdef TEST_VEC4_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	bool result = test_features( "4D Vector Functions", vec4_tests, vec4_test_suite_size() );
	return result ? 0 : 1;
}
#endif

bool test_vec4_literals( void )
{
	vec4_t v = VEC4( 1, 2, 3, 4 );
	return scaler_compare( v.x, 1.0f ) &&
	       scaler_compare( v.y, 2.0f ) &&
	       scaler_compare( v.z, 3.0f ) &&
	       scaler_compare( v.w, 4.0f );
}

bool test_vec4_addition( void )
{
	vec4_t a = VEC4( 0, 1, 2, 5 );
	vec4_t b = VEC4( 4, -1, 2, 5 );
	vec4_t r = vec4_add( &a, &b );
	return scaler_compare( r.x, 4.0f ) &&
	       scaler_compare( r.y, 0.0f ) &&
	       scaler_compare( r.z, 4.0f ) &&
	       scaler_compare( r.w, 10.0f );
}

bool test_vec4_subtraction( void )
{
	vec4_t a = VEC4( 2, 2, 5, 5 );
	vec4_t b = VEC4( -2, 2, 1, 10 );
	vec4_t r = vec4_subtract( &a, &b );
	return scaler_compare( r.x, 4.0f ) &&
	       scaler_compare( r.y, 0.0f ) &&
	       scaler_compare( r.z, 4.0f ) &&
	       scaler_compare( r.w, -5.0f );
}

bool test_vec4_scaler_multiply( void )
{
	vec4_t a = VEC4( 3, 2, 1, 0 );
	scaler_t s = 0.5f;
	vec4_t r = vec4_multiply( &a, s );
	return scaler_compare( r.x, 1.5f ) &&
	       scaler_compare( r.y, 1.0f ) &&
	       scaler_compare( r.z, 0.5f ) &&
	       scaler_compare( r.w, 0.0f );
}

bool test_vec4_magnitude( void )
{
	vec4_t a = VEC4( 4, 3, 2, 1 );
	scaler_t r = vec4_magnitude( &a );
	return scaler_compare( r, 5.477225575051661 );
}

bool test_vec4_dot_product( void )
{
	vec4_t a = VEC4( 4, 3, 2, 1 );
	vec4_t b = VEC4( 4, 3, 2, 1 );
	scaler_t r1 = vec4_dot_product( &a, &b );

	vec4_t c = VEC4( 1, 2, 1, 0 );
	vec4_t d = VEC4( 5, 3, 6, 8 );
	scaler_t r2 = vec4_dot_product( &c, &d );

	return scaler_compare( r1, 30.0f ) &&
	       scaler_compare( r2, 17.0f );
}

bool test_vec4_distance( void )
{
	vec4_t a = VEC4( 4, 3, 2, 1 );
	vec4_t b = VEC4( 4, 3, 2, 1 );
	scaler_t r1 = vec4_distance( &a, &b );

	vec4_t c = VEC4( 1, 1, 1, -5 );
	vec4_t d = VEC4( 5, 1, 6, 5 );
	scaler_t r2 = vec4_distance( &c, &d );

	return scaler_compare( r1, 0.0f ) &&
	       scaler_compare( r2, 11.87434208703792 );
}

bool test_vec4_angle( void )
{
	vec4_t a = VEC4( 1, 1, 0, 0 );
	vec4_t b = VEC4( 0, 1, 0, 0 );
	scaler_t r1 = vec4_angle( &a, &b );

	vec4_t c = VEC4( 1, 0, 0, 0 );
	vec4_t d = VEC4( 0, 1, 0, 0 );
	scaler_t r2 = vec4_angle( &c, &d );

	return scaler_compare( r1, 45.0f * RADIANS_PER_DEGREE ) &&
	       scaler_compare( r2, 90.0f * RADIANS_PER_DEGREE );
}

bool test_vec4_normalize( void )
{
	vec4_t a = VEC4( 3.123f, 12.5f, 0.123123f, 100.0001f );
	vec4_normalize( &a );
	return scaler_compare( vec4_magnitude(&a), 1.0f );
}

bool test_vec4_is_normalized( void )
{
	vec4_t a = VEC4( 3.123f, 12.5f, 0.123123f, 100.0001f );
	vec4_normalize( &a );
	return vec4_is_normalized( &a );
}

bool test_vec4_negate( void )
{
	vec4_t a = VEC4( 1, 2, 3, 4 );
	vec4_negate( &a );
	return scaler_compare( a.x, -1.0f ) &&
	       scaler_compare( a.y, -2.0f ) &&
	       scaler_compare( a.z, -3.0f ) &&
	       scaler_compare( a.w, -4.0f );
}

bool test_vec4_zero( void )
{
	vec4_t a = VEC4( 1, 2, 3, 4 );
	vec4_zero( &a );
	bool r1 = scaler_compare( a.x, 0.0f ) &&
	          scaler_compare( a.y, 0.0f ) &&
	          scaler_compare( a.z, 0.0f ) &&
	          scaler_compare( a.w, 0.0f );

	bool r2 = scaler_compare( VEC4_ZERO.x, 0.0f ) &&
	          scaler_compare( VEC4_ZERO.y, 0.0f ) &&
	          scaler_compare( VEC4_ZERO.z, 0.0f ) &&
	          scaler_compare( VEC4_ZERO.w, 0.0f );

	return r1 && r2;
}
