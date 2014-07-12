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
#include <stdarg.h>
#include <assert.h>
#include "transforms.h"

mat4_t rotate_xyz( const char* order, ... )
{
	assert( order );
	va_list list;
	va_start( list, order );
	mat4_t result = MAT4_IDENTITY;

	while( *order )
	{
		switch( *order++ )
		{
			case 'x':
			case 'X':
			{
				double angle = va_arg( list, double );
				mat4_t r = rotate_x( angle );
				result = mat4_mult_matrix( &result, &r );
				break;
			}
			case 'y':
			case 'Y':
			{
				double angle = va_arg( list, double );
				mat4_t r = rotate_y( angle );
				result = mat4_mult_matrix( &result, &r );
				break;
			}
			case 'z':
			case 'Z':
			{
				double angle = va_arg( list, double );
				mat4_t r = rotate_z( angle );
				result = mat4_mult_matrix( &result, &r );
				break;
			}
			default:
				break;
		}
	}

	va_end( list );
	return result;
}

/*
mat4_t rotate_xyz( scaler_t xa, scaler_t ya, scaler_t za )
{
	mat4_t result = MAT4_IDENTITY;

	if( abs(xa) < SCALAR_EPSILON )
	{
		mat4_t rx = rotate_x( xa );
		mat4_mult_matrix( result, &rx );
	}

	if( abs(ya) < SCALAR_EPSILON )
	{
		mat4_t ry = rotate_y( ya );
		mat4_mult_matrix( result, &ry );
	}

	if( abs(za) < SCALAR_EPSILON )
	{
		mat4_t rz = rotate_z( za );
	}
}
*/


#if 0
mat4_t look_at( const pt3_t* eye, const pt3_t* target, const vec3_t* up )
{
	vec3_t z = VEC3( eye->x - target->x, eye->y - target->y, eye->z - target->z );
	vec3_normalize( &z );

	vec3_t x = vec3_cross_product( &z, up );
	vec3_normalize( &x );

	vec3_t y = vec3_cross_product( &x, &z );
	vec3_normalize( &y );

	#if 0
	return MAT4(
		  x.x,     x.y,     x.z,  0.0, /* x-axis */
		  y.x,     y.y,     y.z,  0.0, /* y-axis */
		  z.x,     z.y,     z.z,  0.0, /* z-axis */
	  -eye->x, -eye->y, -eye->z,  1.0  /* translation */
	);
	#else
	return MAT4(
		  x.x,     y.x,     z.x,  -eye->x,
		  x.y,     y.y,     z.y,  -eye->y,
		  x.z,     y.z,     z.z,  -eye->z,
	     0.0f,    0.0f,    0.0f,  1.0  /* translation */
	);
	#endif
}
#else
mat4_t look_at( const pt3_t* eye, const pt3_t* target, const vec3_t* up )
{
	vec3_t z = VEC3( target->x - eye->x, target->y - eye->y, target->z - eye->z );
	vec3_normalize( &z );

	vec3_t x = vec3_cross_product( &z, up );
	vec3_normalize( &x );

	vec3_t y = vec3_cross_product( &x, &z );
	vec3_normalize( &y );

	return MAT4(
	       x.x,     x.y,     x.z,  0.0, /* x-axis */
	       y.x,     y.y,     y.z,  0.0, /* y-axis */
	      -z.x,    -z.y,    -z.z,  0.0, /* z-axis */
	   -eye->x, -eye->y, -eye->z,  1.0  /* translation */
	);
}
#endif
