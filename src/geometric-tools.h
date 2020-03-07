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
#include <assert.h>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

/*
 * Calculate a normal from a triangle.
 */
vec3_t m3d_normal_from_triangle( const vec3_t* v1, const vec3_t* v2, const vec3_t* v3 );

/*
 * Calculate an average normal from a list of triangles. This is useful for
 * smoothing surfaces.
 */
vec3_t m3d_normal_from_triangles( const vec3_t* points[], size_t max_points );

/*
 * Map a point from viewport coordinates to world coordinates.
 */
vec4_t m3d_point_unproject( const vec2_t* restrict position, const mat4_t* projection, const mat4_t* restrict modelview, int viewport[4] );

/*
 * Map a point from world coordinates to viewport coordinates.
 */
vec2_t m3d_point_project( const vec4_t* restrict point, const mat4_t* restrict projection, const mat4_t* restrict modelview, int viewport[4] );


/*
 *  Map window coordinates (i.e. pixel coordinates) to normalized device coordinates.
 */
static inline vec4_t m3d_wc_to_ndc( const vec2_t* wc, int viewport[4] )
{
	return VEC4(
		(wc->x - viewport[0]) * (2.0f / viewport[2]) - 1.0f,
		(wc->y - viewport[1]) * (2.0f / viewport[3]) - 1.0f,
		0.0f,
		1.0f
	);
}

/*
 *  Map normalized device coordinates to window coorindates.
 */
static inline vec2_t m3d_ndc_to_wc( const vec4_t* ndc, int viewport[4] )
{
	return VEC2(
		(1.0f + ndc->x) * (viewport[2] / 2.0f) + viewport[0],
		(1.0f + ndc->y) * (viewport[3] / 2.0f) + viewport[1]
	);
}

/*
 *  Wrap indexes in the range of [0, length).  This is useful for
 *  sampling rectangular values and not having to worry about indexing
 *  out of bounds in an array.
 */
static inline size_t m3d_wrap_index( size_t index, size_t length )
{
	assert( length > 0 && "Array length must be greater than 0.");
	return ((index % length) + length) % length;
}


#endif /* _GEOMETRIC_TOOLS_H_ */
