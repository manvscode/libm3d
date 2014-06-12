#include <stdio.h>
#include <stdlib.h>
#include "test.h"

extern const test_feature_t math_tests[];
extern size_t math_test_suite_size( void );

extern const test_feature_t vec2_tests[];
size_t vec2_test_suite_size( void );

extern const test_feature_t vec3_tests[];
size_t vec3_test_suite_size( void );

extern const test_feature_t vec4_tests[];
size_t vec4_test_suite_size( void );

extern const test_feature_t mat2_tests[];
size_t mat2_test_suite_size( void );

extern const test_feature_t mat3_tests[];
size_t mat3_test_suite_size( void );

extern const test_feature_t mat4_tests[];
size_t mat4_test_suite_size( void );

extern const test_feature_t quat_tests[];
size_t quat_test_suite_size( void );


const test_suite_t suites[] = {
	{ "Tests for mathematics.h", math_tests, math_test_suite_size },

	{ "Tests for vec2.h", vec2_tests, vec2_test_suite_size },
	{ "Tests for vec3.h", vec3_tests, vec3_test_suite_size },
	{ "Tests for vec4.h", vec4_tests, vec4_test_suite_size },

	{ "Tests for mat2.h", mat2_tests, mat2_test_suite_size },
	{ "Tests for mat3.h", mat3_tests, mat3_test_suite_size },
	{ "Tests for mat4.h", mat4_tests, mat4_test_suite_size },

	//{ "Tests for quat.h", quat_tests, quat_test_suite_size },
};


int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	return test_suites( suites, sizeof(suites)/sizeof(suites[0]) );
}
