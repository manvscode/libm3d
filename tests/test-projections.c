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
#include "../src/projections.h"
#include "../src/transforms.h"
#include "test.h"

bool test_orthographic_projection1  ( void );
bool test_orthographic_projection2  ( void );
bool test_orthographic_projection3  ( void );
bool test_perspective_projection1   ( void );
bool test_perspective_projection2   ( void );
bool test_perspective_projection3   ( void );

const test_feature_t projection_tests[] = {
	{ "Testing orthographic projection with 4:3 aspect ratio", test_orthographic_projection1 },
	{ "Testing orthographic projection with 1:1 aspect ratio", test_orthographic_projection2 },
	{ "Testing orthographic projection clip-coordinates", test_orthographic_projection3 },
	{ "Testing perspective projection 45\xc2\xb0 with 4:3 aspect ratio", test_perspective_projection1 },
	{ "Testing perspective projection 160\xc2\xb0 with 1:1 aspect ratio", test_perspective_projection2 },
	{ "Testing perspective projection clip-coordinates", test_perspective_projection3 },
};

size_t projection_test_suite_size( void )
{
	return sizeof(projection_tests) / sizeof(projection_tests[0]);
}


#ifdef TEST_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "Projection Transformations", projection_tests, projection_test_suite_size() );
	return 0;
}
#endif

bool test_orthographic_projection1( void )
{
	scaler_t aspect = 4.0 / 3.0;
	mat4_t o = m3d_orthographic( -10.0 * aspect, 10.0 * aspect, -10.0, 10.0, -10.0, 10.0 );
	return scaler_compare( o.m[ 0],  0.075 ) &&
	       scaler_compare( o.m[ 1],  0.0 ) &&
	       scaler_compare( o.m[ 2],  0.0 ) &&
	       scaler_compare( o.m[ 3],  0.0 ) &&
	       scaler_compare( o.m[ 4],  0.0 ) &&
	       scaler_compare( o.m[ 5],  0.1 ) &&
	       scaler_compare( o.m[ 6],  0.0 ) &&
	       scaler_compare( o.m[ 7],  0.0 ) &&
	       scaler_compare( o.m[ 8],  0.0 ) &&
	       scaler_compare( o.m[ 9],  0.0 ) &&
	       scaler_compare( o.m[10], -0.1 ) &&
	       scaler_compare( o.m[11],  0.0 ) &&
	       scaler_compare( o.m[12],  0.0 ) &&
	       scaler_compare( o.m[13],  0.0 ) &&
	       scaler_compare( o.m[14],  0.0 ) &&
	       scaler_compare( o.m[15],  1.0 );
}

bool test_orthographic_projection2( void )
{
	mat4_t o = m3d_orthographic( 0, 3.0, 0, 3.0, 0, 3.0 );
	return scaler_compare( o.m[ 0],  0.6666666667 ) &&
	       scaler_compare( o.m[ 1],  0.0 ) &&
	       scaler_compare( o.m[ 2],  0.0 ) &&
	       scaler_compare( o.m[ 3],  0.0 ) &&
	       scaler_compare( o.m[ 4],  0.0 ) &&
	       scaler_compare( o.m[ 5],  0.6666666667 ) &&
	       scaler_compare( o.m[ 6],  0.0 ) &&
	       scaler_compare( o.m[ 7],  0.0 ) &&
	       scaler_compare( o.m[ 8],  0.0 ) &&
	       scaler_compare( o.m[ 9],  0.0 ) &&
	       scaler_compare( o.m[10], -0.6666666667 ) &&
	       scaler_compare( o.m[11],  0.0 ) &&
	       scaler_compare( o.m[12], -1.0 ) &&
	       scaler_compare( o.m[13], -1.0 ) &&
	       scaler_compare( o.m[14], -1.0 ) &&
	       scaler_compare( o.m[15],  1.0 );
}

bool test_orthographic_projection3( void )
{
	const mat4_t o = m3d_orthographic( -10.0, 10.0, -10.0, 10.0, 10.0, -10.0 );
	const vec4_t normalized_clip_box[] = { // in normalized-device coordaintes
		VEC4(-1.0, -1.0, -1.0, 1.0),
		VEC4(-1.0, -1.0, +1.0, 1.0),
		VEC4(-1.0, +1.0, -1.0, 1.0),
		VEC4(-1.0, +1.0, +1.0, 1.0),
		VEC4(+1.0, -1.0, -1.0, 1.0),
		VEC4(+1.0, -1.0, +1.0, 1.0),
		VEC4(+1.0, +1.0, -1.0, 1.0),
		VEC4(+1.0, +1.0, +1.0, 1.0)
	};
	const vec4_t p[] = {
		VEC4(-10.0, -10.0, -10.0, 1.0),
		VEC4(-10.0, -10.0, +10.0, 1.0),
		VEC4(-10.0, +10.0, -10.0, 1.0),
		VEC4(-10.0, +10.0, +10.0, 1.0),
		VEC4(+10.0, -10.0, -10.0, 1.0),
		VEC4(+10.0, -10.0, +10.0, 1.0),
		VEC4(+10.0, +10.0, -10.0, 1.0),
		VEC4(+10.0, +10.0, +10.0, 1.0)
	};

	bool result = true;
	for( int i = 0; result && i < 8; i++) // transform points to clip space
	{
		vec4_t c = mat4_mult_vector( &o, &p[i] );
		result = result && vec4_compare( &normalized_clip_box[i], &c );

#if 0
		if( !result )
		{
			printf("%s\n", vec4_to_string(&c));
		}
#endif
	}
	return result;
}

bool test_perspective_projection1( void )
{
	scaler_t aspect = 4.0 / 3.0;
	mat4_t p = m3d_perspective( m3d_to_radians(45.0), aspect, 0.1, 100.0 );
	return scaler_compare( p.m[ 0],  1.81066000 ) &&
	       scaler_compare( p.m[ 1],  0.0 ) &&
	       scaler_compare( p.m[ 2],  0.0 ) &&
	       scaler_compare( p.m[ 3],  0.0 ) &&
	       scaler_compare( p.m[ 4],  0.0 ) &&
	       scaler_compare( p.m[ 5],  2.41421342 ) &&
	       scaler_compare( p.m[ 6],  0.0 ) &&
	       scaler_compare( p.m[ 7],  0.0 ) &&
	       scaler_compare( p.m[ 8],  0.0 ) &&
	       scaler_compare( p.m[ 9],  0.0 ) &&
	       scaler_compare( p.m[10], -1.00100100 ) &&
	       scaler_compare( p.m[11], -1.0 ) &&
	       scaler_compare( p.m[12],  0.0 ) &&
	       scaler_compare( p.m[13],  0.0 ) &&
	       scaler_compare( p.m[14], -0.10010010 ) &&
	       scaler_compare( p.m[15],  0.0 );
}

bool test_perspective_projection2( void )
{
	mat4_t p = m3d_perspective( m3d_to_radians(160.0), 1.0, 0.01, 1000.0 );
	return scaler_compare( p.m[ 0],  0.17632702 ) &&
	       scaler_compare( p.m[ 1],  0.0 ) &&
	       scaler_compare( p.m[ 2],  0.0 ) &&
	       scaler_compare( p.m[ 3],  0.0 ) &&
	       scaler_compare( p.m[ 4],  0.0 ) &&
	       scaler_compare( p.m[ 5],  0.17632702 ) &&
	       scaler_compare( p.m[ 6],  0.0 ) &&
	       scaler_compare( p.m[ 7],  0.0 ) &&
	       scaler_compare( p.m[ 8],  0.0 ) &&
	       scaler_compare( p.m[ 9],  0.0 ) &&
	       scaler_compare( p.m[10], -1.00001001 ) &&
	       scaler_compare( p.m[11], -1.0 ) &&
	       scaler_compare( p.m[12],  0.0 ) &&
	       scaler_compare( p.m[13],  0.0 ) &&
	       scaler_compare( p.m[14], -0.01000010 ) &&
	       scaler_compare( p.m[15],  0.0 );
}

bool test_perspective_projection3( void )
{
	const mat4_t f = m3d_frustum( -10.0, 10.0, -10.0, 10.0, 1.0, 100.0 );
	const vec4_t clip_box[] = { // in clip-space
		VEC4(  -1.0,   -1.0,  -1.0,   1.0),
		VEC4(  -1.0,   +1.0,  -1.0,   1.0),
		VEC4(  +1.0,   -1.0,  -1.0,   1.0),
		VEC4(  +1.0,   +1.0,  -1.0,   1.0),
		VEC4(-100.0, -100.0, 100.0, 100.0),
		VEC4(-100.0, +100.0, 100.0, 100.0),
		VEC4(+100.0, -100.0, 100.0, 100.0),
		VEC4(+100.0, +100.0, 100.0, 100.0)
	};
	const vec4_t normalized_clip_box[] = { // in normalized-device coordaintes
		VEC4(-1.0, -1.0, -1.0, 1.0),
		VEC4(-1.0, +1.0, -1.0, 1.0),
		VEC4(+1.0, -1.0, -1.0, 1.0),
		VEC4(+1.0, +1.0, -1.0, 1.0),
		VEC4(-1.0, -1.0, +1.0, 1.0),
		VEC4(-1.0, +1.0, +1.0, 1.0),
		VEC4(+1.0, -1.0, +1.0, 1.0),
		VEC4(+1.0, +1.0, +1.0, 1.0)
	};
	const vec4_t p[] = {
		VEC4(  -10.0,   -10.0,   -1.0, 1.0),
		VEC4(  -10.0,   +10.0,   -1.0, 1.0),
		VEC4(  +10.0,   -10.0,   -1.0, 1.0),
		VEC4(  +10.0,   +10.0,   -1.0, 1.0),
		VEC4(-1000.0, -1000.0, -100.0, 1.0),
		VEC4(-1000.0, +1000.0, -100.0, 1.0),
		VEC4(+1000.0, -1000.0, -100.0, 1.0),
		VEC4(+1000.0, +1000.0, -100.0, 1.0)
	};

	bool result = true;
	for( int i = 0; result && i < 8; i++) // transform points to clip space
	{
		vec4_t c = mat4_mult_vector( &f, &p[i] );
		result = result && vec4_compare( &clip_box[i], &c );
#if 0
		if( !result )
		{
			printf("%d. %s\n", i, vec4_to_string(&c));
		}
#endif

		vec4_t ndc = m3d_perspective_divide( &c );
		result = result && vec4_compare(&normalized_clip_box[i], &ndc);
#if 0
		if( !result )
		{
			printf("%d. %s\n", i, vec4_to_string(&ndc));
		}
#endif
	}



	return result;
}
