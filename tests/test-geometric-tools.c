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
#define SCALAR_EPSILON 0.000001
#include "../src/mat4.h"
#include "../src/mathematics.h"
#include "../src/geometric-tools.h"
#include "../src/transforms.h"
#include "test.h"

bool test_array_wrapping  ( void );

const test_feature_t geometric_tools_tests[] = {
	{ "Testing array wrapping", test_array_wrapping },
};

size_t geometric_tools_test_suite_size( void )
{
	return sizeof(geometric_tools_tests) / sizeof(geometric_tools_tests[0]);
}


#ifdef TEST_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "Geometric Tools", geometric_tools_tests, geometric_tools_test_suite_size() );
	return 0;
}
#endif

bool test_array_wrapping( void )
{
	bool result = true;
	size_t size = 7;
	for (size_t i = 0; result & i < 100; i += 1)
	{
		size_t index = m3d_wrap_index(i, size);
		result = result && (0u <= index) && (index < size);
	}

	size = 13;
	for (size_t i = 0; result & i < 200; i += 1)
	{
		size_t index = m3d_wrap_index(i, size);
		result = result && (0u <= index) && (index < size);
	}

	return result;
}

