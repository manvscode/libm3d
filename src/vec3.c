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
#include <float.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include "vec3.h"

const vec3_t VEC3_ZERO  = (vec3_t){ .x = 0.0f, .y = 0.0f, .z = 0.0f };
const vec3_t VEC3_ONE   = (vec3_t){ .x = 1.0f, .y = 1.0f, .z = 1.0f };
const vec3_t VEC3_XUNIT = (vec3_t){ .x = 1.0f, .y = 0.0f, .z = 0.0f };
const vec3_t VEC3_YUNIT = (vec3_t){ .x = 0.0f, .y = 1.0f, .z = 0.0f };
const vec3_t VEC3_ZUNIT = (vec3_t){ .x = 0.0f, .y = 0.0f, .z = 1.0f };


const char* vec3_to_string( const vec3_t* v ) /* not thread safe */
{
	static char string_buffer[ 128 ];
	snprintf( string_buffer, sizeof(string_buffer) - 1, "(%08.1f, %08.1f, %08.1f)", v->x, v->y, v->z );
	string_buffer[ sizeof(string_buffer) - 1 ] = '\0';
	return string_buffer;
}

