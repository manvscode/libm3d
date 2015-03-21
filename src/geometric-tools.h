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
#ifndef _GEOMETRIC_TOOLS_H_
#define _GEOMETRIC_TOOLS_H_
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

vec3_t normal_from_triangle  ( const vec3_t* v1, const vec3_t* v2, const vec3_t* v3 );
vec3_t normal_from_triangles ( const vec3_t* points[], size_t max_points );

vec4_t point_unproject ( const vec2_t* position, const mat4_t* projection, const mat4_t* model, int viewport[] );
vec2_t point_project   ( const vec4_t* point, const mat4_t* projection, const mat4_t* model, int viewport[] );

#endif /* _GEOMETRIC_TOOLS_H_ */
