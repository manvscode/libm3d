/* Copyright (C) 2013-2025 by Joseph A. Marrero, http://joemarrero.com/
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
#include <stdlib.h>
#include "geometric-tools.h"

/*
 * Calculate a normal from a triangle.
 */
vec3_t m3d_normal_from_triangle( const vec3_t* v1, const vec3_t* v2, const vec3_t* v3 )
{
	vec3_t normal = vec3_cross_product(
		&VEC3( v2->x - v1->x, v2->y - v1->y, v2->z - v1->z ),
		&VEC3( v3->x - v1->x, v3->y - v1->y, v3->z - v1->z )
	);
	vec3_normalize( &normal );

	return normal;
}

/*
 * Calculate an average normal from a list of triangles. This is useful for
 * smoothing surfaces.
 */
vec3_t m3d_normal_from_triangles( const vec3_t* points[], size_t max_points )
{
	/*
	 * Every vertex is generally shared among 6 triangles.  We calculate the
	 * normal of each triangle and average them together to calculate the
	 * normal at vertex 0.
  	 *
	 *                             1--2--*
	 *  The numbers are the        |\ |\ |
	 *  vertices that are members  | \| \|
	 *  of the 6 triangles shared  6--0--3
	 *  by vertex 0.               |\ |\ |
	 *                             | \| \|
	 *                             *--5--4
	 *
	 * This function extends this idea to an arbitrary number of triangles.
	 */
	const size_t number_of_triangles = max_points / 3;

	vec3_t normal = VEC3_ZERO;

	for( size_t i = 0; i < max_points; i += 3 )
	{
		vec3_t n = m3d_normal_from_triangle( points[ i + 0 ], points[ i + 1 ], points[ i + 2 ] );

		if( vec3_dot_product( &normal, &n ) < 0.0f )
		{
			/* Vector n is in opposite direction to
			 * accumulated normal. This happens when the points
			 * winding is not consistent.
			 */
			vec3_negate( &n );
		}

		normal = vec3_add( &normal, &n );
	}

	return vec3_multiply( &normal, 1.0f / number_of_triangles );
}

vec4_t m3d_point_unproject( const vec2_t* restrict point, const mat4_t* restrict projection, const mat4_t* restrict modelview, int viewport[4] )
{
	/* Convert to normalized device coordinates */
	vec4_t normalized_device_coordinate = VEC4(
		(point->x - viewport[0]) * (2.0f / viewport[2]) - 1.0f,
		(point->y - viewport[1]) * (2.0f / viewport[3]) - 1.0f,
		0.0f,
		1.0f
	);

	mat4_t inv_projmodel = mat4_mult_matrix( projection, modelview );
	mat4_invert( &inv_projmodel );

	return mat4_mult_vector( &inv_projmodel, &normalized_device_coordinate );
}

vec2_t m3d_point_project( const vec4_t* restrict point, const mat4_t* restrict projection, const mat4_t* restrict modelview, int viewport[4] )
{
	mat4_t projmodel = mat4_mult_matrix( projection, modelview );
	vec4_t pt = mat4_mult_vector( &projmodel, point );
	return VEC2(
		(1.0f + pt.x) * (viewport[2] / 2.0f) + viewport[0],
		(1.0f + pt.y) * (viewport[3] / 2.0f) + viewport[1]
	);
}

int m3d_cyrus_beck_line_clipping( const vec2_t* p0, const vec2_t* p1, vec2_t points[2] )
{
	const size_t edge_count = 4;
	const vec2_t edge_points[] = {
		VEC2(+1, +1),
		VEC2(-1, +1),
		VEC2(-1, -1),
		VEC2(+1, -1)
	};
	const vec2_t edge_normals[] = {
		VEC2( 0, +1),
		VEC2(-1,  0),
		VEC2( 0, -1),
		VEC2(+1,  0)
	};
	return m3d_cyrus_beck_polygon_line_clipping( edge_points, edge_normals, edge_count, p0, p1, points );
}

int m3d_cyrus_beck_polygon_line_clipping( const vec2_t* edge_points, const vec2_t* edge_normals, size_t edge_count,
                                          const vec2_t* p0, const vec2_t* p1, vec2_t points[2] )
{
	assert( edge_count >= 3 && "Expected a convex polygon" );
	vec2_t line_vector = vec2_subtract(p1, p0);
	int found_intersections = 0;
	vec2_t intersections[2];
	scaler_t edge_line_dot_product = 0;

	for( int i = 0; found_intersections < 2 && i < edge_count; i++ )
	{
		vec2_t edge_to_point_vector = vec2_subtract(&edge_points[i], p0 );
		scaler_t denominator = vec2_dot_product( &edge_normals[i], &line_vector );
		scaler_t t = vec2_dot_product( &edge_normals[i], &edge_to_point_vector ) / denominator;

		if( 0.0f < t && t < 1.0f )
		{
			assert( (found_intersections + 1) <= 2 && "Expecting at most 2 intersection points" );
			intersections[found_intersections++] = VEC2(
				p0->x + (p1->x - p0->x) * t,
				p0->y + (p1->y - p0->y) * t
			);
			edge_line_dot_product = denominator;
		}
	}

	if (found_intersections > 1)
	{
			points[0] = intersections[0];
			points[1] = intersections[1];

	}
	else if (found_intersections == 1)
	{
		if( edge_line_dot_product > 0  )
		{
			points[0] = intersections[0];
			points[1] = *p1;
		}
		else
		{
			points[0] = *p0;
			points[1] = intersections[0];

		}
	}

	return found_intersections;
}
