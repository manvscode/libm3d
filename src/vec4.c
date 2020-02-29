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
#include <float.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "vec4.h"
#include "vec3.h"

const vec4_t VEC4_ZERO  = { .x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 0.0f };
const vec4_t VEC4_ONE   = { .x = 1.0f, .y = 1.0f, .z = 1.0f, .w = 1.0f };
const vec4_t VEC4_XUNIT = { .x = 1.0f, .y = 0.0f, .z = 0.0f, .w = 0.0f };
const vec4_t VEC4_YUNIT = { .x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f };
const vec4_t VEC4_ZUNIT = { .x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f };
const vec4_t VEC4_WUNIT = { .x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f };


const char* vec4_to_string( const vec4_t* v ) /* not thread safe */
{
	static char string_buffer[ 128 ];
#if defined(LIBM3D_USE_LONG_DOUBLE)
	snprintf( string_buffer, sizeof(string_buffer) - 1, "(%.2Lf, %.2Lf, %.2Lf, %.2Lf)", v->x, v->y, v->z, v->w );
#elif defined(LIBM3D_USE_DOUBLE)
	snprintf( string_buffer, sizeof(string_buffer) - 1, "(%.2lf, %.2lf, %.2lf, %.2lf)", v->x, v->y, v->z, v->w );
#else
	snprintf( string_buffer, sizeof(string_buffer) - 1, "(%.2f, %.2f, %.2f, %.2f)", v->x, v->y, v->z, v->w );
#endif
	string_buffer[ sizeof(string_buffer) - 1 ] = '\0';
	return string_buffer;
}
