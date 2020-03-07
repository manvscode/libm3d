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
#include "test.h"
#include "../src/mathematics.h"

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

extern const test_feature_t numerical_methods_tests[];
size_t numerical_methods_test_suite_size( void );

extern const test_feature_t projection_tests[];
size_t projection_test_suite_size( void );

extern const test_feature_t geometric_tools_tests[];
extern size_t geometric_tools_test_suite_size( void );

extern const test_feature_t geographic_tests[];
size_t geographic_test_suite_size( void );

const test_suite_t suites[] = {
	{ "Tests for mathematics.h", math_tests, math_test_suite_size },

	{ "Tests for vec2.h", vec2_tests, vec2_test_suite_size },
	{ "Tests for vec3.h", vec3_tests, vec3_test_suite_size },
	{ "Tests for vec4.h", vec4_tests, vec4_test_suite_size },

	{ "Tests for mat2.h", mat2_tests, mat2_test_suite_size },
	{ "Tests for mat3.h", mat3_tests, mat3_test_suite_size },
	{ "Tests for mat4.h", mat4_tests, mat4_test_suite_size },

	//{ "Tests for quat.h", quat_tests, quat_test_suite_size },
	{ "Tests for numerical-methods.h", numerical_methods_tests, numerical_methods_test_suite_size },
	{ "Tests for projections.h", projection_tests, projection_test_suite_size },
	{ "Tests for geometric-tools.h", geometric_tools_tests, geometric_tools_test_suite_size },
	{ "Tests for geographic.h", geographic_tests, geographic_test_suite_size },
};


int main( int argc, char* argv[] )
{
	srand( time(NULL) );

	#if defined(LIBM3D_USE_LONG_DOUBLE)
	printf( "%s: %s%-30s%s\n\n", COLOR_CYAN_STR("Type of scaler_t"), COLOR_GREEN, "long double", COLOR_END );
	#elif defined(LIBM3D_USE_DOUBLE)
	printf( "%s: %s%-30s%s\n\n", COLOR_CYAN_STR("Type of scaler_t"), COLOR_GREEN, "double", COLOR_END );
	#else /* default: use float */
	printf( "%s: %s%-30s%s\n\n", COLOR_CYAN_STR("Type of scaler_t"), COLOR_GREEN, "float", COLOR_END );
	#endif
	return test_suites( suites, sizeof(suites)/sizeof(suites[0]) );
}
