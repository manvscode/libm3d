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
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "mathematics.h"
#include "mat2.h"

const mat2_t MAT2_IDENTITY = { .m = {
					1.0f, 0.0f,
					0.0f, 1.0f
				}};

const mat2_t MAT2_ZERO = { .m = {
					0.0f, 0.0f,
					0.0f, 0.0f
				}};

void mat2_initialize( mat2_t* m, scaler_t a, scaler_t b, scaler_t c, scaler_t d )
{
	m->m[ 0 ] = a;
	m->m[ 1 ] = b;
	m->m[ 2 ] = c;
	m->m[ 3 ] = d;
}

void mat2_identity( mat2_t* m )
{
	*m = MAT2_IDENTITY;
}

void mat2_zero( mat2_t* m )
{
	*m = MAT2_ZERO;
}

scaler_t mat2_determinant( const mat2_t* m )
{
	return m->m[ 0 ] * m->m[ 3 ] - m->m[ 1 ] * m->m[ 2 ];
}

mat2_t mat2_mult_matrix( const mat2_t* restrict a, const mat2_t* restrict b )
{
	/*      a     b              result
	 *   |a  c||e  g|  =  |(a*e+c*f) (a*g+c*h)|
	 *   |b  d||f  h|     |(b*e+d*f) (b*g+d*h)|
	 */
	return MAT2(
		a->m[ 0 ] * b->m[ 0 ] + a->m[ 2 ] * b->m[ 1 ],
		a->m[ 1 ] * b->m[ 0 ] + a->m[ 3 ] * b->m[ 1 ],
		a->m[ 0 ] * b->m[ 2 ] + a->m[ 2 ] * b->m[ 3 ],
		a->m[ 1 ] * b->m[ 2 ] + a->m[ 3 ] * b->m[ 3 ]
	);
}

vec2_t mat2_mult_vector( const mat2_t* restrict m, const vec2_t* restrict v )
{
	return VEC2(
		m->m[ 0 ] * v->x + m->m[ 2 ] * v->y,
		m->m[ 1 ] * v->x + m->m[ 3 ] * v->y
	);
}

bool mat2_invert( mat2_t* m )
{
	/* inv(A) = (1/det(A)) * transpose( cofactors(A) ) */
	scaler_t det = mat2_determinant( m );

	if( scaler_abs(det) > SCALAR_EPSILON ) // testing if not zero
	{
		/* |a  c|  cofactors and transpose  | d  -c|
		 * |b  d|  ---------------------->  |-b   a|
		 */
		{
			scaler_t tmp = m->m[ 0 ];
			m->m[ 0 ] = m->m[ 3 ];
			m->m[ 3 ] = tmp;
		}

		m->m[ 0 ] /=  det;
		m->m[ 1 ] /= -det;
		m->m[ 2 ] /= -det;
		m->m[ 3 ] /=  det;

		return true;
	}

	return false;
}

void mat2_transpose( mat2_t* m )
{
	/* | a  c |   --->  | a  b |
	 * | b  d |         | c  d |
	 */
	scaler_t tmp = m->m[ 1 ];
	m->m[ 1 ] = m->m[ 2 ];
	m->m[ 2 ] = tmp;
}

const char* mat2_to_string( const mat2_t* m )
{
	static char string_buffer[ 128 ];
	#if defined(LIBM3D_USE_LONG_DOUBLE)
	snprintf( string_buffer, sizeof(string_buffer) - 1,
		"|%-6.2Lf %6.2Lf|\n"
		"|%-6.2Lf %6.2Lf|\n",
		m->m[0], m->m[2],
		m->m[1], m->m[3]
 	);
	#elif defined(LIBM3D_USE_DOUBLE)
	snprintf( string_buffer, sizeof(string_buffer) - 1,
		"|%-6.2lf %6.2lf|\n"
		"|%-6.2lf %6.2lf|\n",
		m->m[0], m->m[2],
		m->m[1], m->m[3]
 	);
	#else
	snprintf( string_buffer, sizeof(string_buffer) - 1,
		"|%-6.2f %6.2f|\n"
		"|%-6.2f %6.2f|\n",
		m->m[0], m->m[2],
		m->m[1], m->m[3]
 	);
	#endif
	string_buffer[ sizeof(string_buffer) - 1 ] = '\0';
	return string_buffer;
}

#if 0
const vec2_t* mat2_x_vector( const mat2_t* m )
{
    return (vec2_t*) &m->x;
}

const vec2_t* mat2_y_vector( const mat2_t* m )
{
    return (vec2_t*) &m->y;
}
#endif
