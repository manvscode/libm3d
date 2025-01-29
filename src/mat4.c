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
#include "mat4.h"

const mat4_t MAT4_IDENTITY = { .m = {
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				}};

const mat4_t MAT4_ZERO = { .m = {
					0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f
				}};

void mat4_identity( mat4_t* m )
{
	*m = MAT4_IDENTITY;
}

void mat4_zero( mat4_t* m )
{
	*m = MAT4_ZERO;
}

scaler_t mat4_determinant( const mat4_t* m )
{
	// d1, d2, d3, and d4 are the determinants of the sub-matrices
	scaler_t d1 = m->m[5] * (m->m[10] * m->m[15] - m->m[14] * m->m[11]) - m->m[6] * (m->m[9] * m->m[15] - m->m[13] * m->m[11]) + m->m[7] * (m->m[9] * m->m[14] - m->m[13] * m->m[10]);
	scaler_t d2 = m->m[4] * (m->m[10] * m->m[15] - m->m[14] * m->m[11]) - m->m[6] * (m->m[8] * m->m[15] - m->m[12] * m->m[11]) + m->m[7] * (m->m[8] * m->m[14] - m->m[12] * m->m[10]);
	scaler_t d3 = m->m[4] * (m->m[ 9] * m->m[15] - m->m[13] * m->m[11]) - m->m[5] * (m->m[8] * m->m[15] - m->m[12] * m->m[11]) + m->m[7] * (m->m[8] * m->m[13] - m->m[12] * m->m[ 9]);
	scaler_t d4 = m->m[4] * (m->m[ 9] * m->m[14] - m->m[13] * m->m[10]) - m->m[5] * (m->m[8] * m->m[14] - m->m[12] * m->m[10]) + m->m[6] * (m->m[8] * m->m[13] - m->m[12] * m->m[ 9]);

	return m->m[0]*d1 - m->m[1]*d2 + m->m[2]*d3 - m->m[3]*d4;
}

mat4_t mat4_mult_matrix( const mat4_t* restrict a, const mat4_t* restrict b )
{
    assert( a && b );
    assert( a != b );
	// |a00 a04 a08 a12|   |b00 b04 b08 b12|
	// |a01 a05 a09 a13| * |b01 b05 b09 b13|
	// |a02 a06 a10 a14|   |b02 b06 b10 b14|
	// |a03 a07 a11 a15|   |b03 b07 b11 b15|
	return MAT4(
		a->m[ 0] * b->m[ 0]  +  a->m[ 4] * b->m[ 1]  +  a->m[ 8] * b->m[ 2]  +  a->m[12] * b->m[ 3],
		a->m[ 1] * b->m[ 0]  +  a->m[ 5] * b->m[ 1]  +  a->m[ 9] * b->m[ 2]  +  a->m[13] * b->m[ 3],
		a->m[ 2] * b->m[ 0]  +  a->m[ 6] * b->m[ 1]  +  a->m[10] * b->m[ 2]  +  a->m[14] * b->m[ 3],
		a->m[ 3] * b->m[ 0]  +  a->m[ 7] * b->m[ 1]  +  a->m[11] * b->m[ 2]  +  a->m[15] * b->m[ 3],

		a->m[ 0] * b->m[ 4]  +  a->m[ 4] * b->m[ 5]  +  a->m[ 8] * b->m[ 6]  +  a->m[12] * b->m[ 7],
		a->m[ 1] * b->m[ 4]  +  a->m[ 5] * b->m[ 5]  +  a->m[ 9] * b->m[ 6]  +  a->m[13] * b->m[ 7],
		a->m[ 2] * b->m[ 4]  +  a->m[ 6] * b->m[ 5]  +  a->m[10] * b->m[ 6]  +  a->m[14] * b->m[ 7],
		a->m[ 3] * b->m[ 4]  +  a->m[ 7] * b->m[ 5]  +  a->m[11] * b->m[ 6]  +  a->m[15] * b->m[ 7],

		a->m[ 0] * b->m[ 8]  +  a->m[ 4] * b->m[ 9]  +  a->m[ 8] * b->m[10]  +  a->m[12] * b->m[11],
		a->m[ 1] * b->m[ 8]  +  a->m[ 5] * b->m[ 9]  +  a->m[ 9] * b->m[10]  +  a->m[13] * b->m[11],
		a->m[ 2] * b->m[ 8]  +  a->m[ 6] * b->m[ 9]  +  a->m[10] * b->m[10]  +  a->m[14] * b->m[11],
		a->m[ 3] * b->m[ 8]  +  a->m[ 7] * b->m[ 9]  +  a->m[11] * b->m[10]  +  a->m[15] * b->m[11],

		a->m[ 0] * b->m[12]  +  a->m[ 4] * b->m[13]  +  a->m[ 8] * b->m[14]  +  a->m[12] * b->m[15],
		a->m[ 1] * b->m[12]  +  a->m[ 5] * b->m[13]  +  a->m[ 9] * b->m[14]  +  a->m[13] * b->m[15],
		a->m[ 2] * b->m[12]  +  a->m[ 6] * b->m[13]  +  a->m[10] * b->m[14]  +  a->m[14] * b->m[15],
		a->m[ 3] * b->m[12]  +  a->m[ 7] * b->m[13]  +  a->m[11] * b->m[14]  +  a->m[15] * b->m[15]
	);
}

vec4_t mat4_mult_vector( const mat4_t* restrict m, const vec4_t* restrict v )
{
    assert( m && v );
	// |m00x + m01y + m02z + m03w|   | m00 m04 m08 m12|    |x|
	// |m03x + m04y + m05z + m03w| = | m01 m05 m09 m13| *  |y|
	// |m06x + m07y + m08z + m03w|   | m02 m06 m10 m14|    |z|
	// |m06x + m07y + m08z + m03w|   | m03 m07 m11 m15|    |w|
	return VEC4(
		m->m[ 0] * v->x  +  m->m[ 4] * v->y  +  m->m[ 8] * v->z  +  m->m[12] * v->w,
		m->m[ 1] * v->x  +  m->m[ 5] * v->y  +  m->m[ 9] * v->z  +  m->m[13] * v->w,
		m->m[ 2] * v->x  +  m->m[ 6] * v->y  +  m->m[10] * v->z  +  m->m[14] * v->w,
		m->m[ 3] * v->x  +  m->m[ 7] * v->y  +  m->m[11] * v->z  +  m->m[15] * v->w
	);
}

bool mat4_invert( mat4_t* m )
{
	#if 0
	scaler_t det = mat4_determinant( m );

	if( det > SCALAR_EPSILON ) // testing if not zero
	{
		mat4_adjoint( m );

		m->m[ 0] /= det;
		m->m[ 1] /= det;
		m->m[ 2] /= det;
		m->m[ 3] /= det;
		m->m[ 4] /= det;
		m->m[ 5] /= det;
		m->m[ 6] /= det;
		m->m[ 7] /= det;
		m->m[ 8] /= det;
		m->m[ 9] /= det;
		m->m[10] /= det;
		m->m[11] /= det;
		m->m[12] /= det;
		m->m[13] /= det;
		m->m[14] /= det;
		m->m[15] /= det;

		return true;
	}

	return false;
	#else
	scaler_t d1 = m->m[5] * (m->m[10] * m->m[15] - m->m[14] * m->m[11]) - m->m[6] * (m->m[9] * m->m[15] - m->m[13] * m->m[11]) + m->m[7] * (m->m[9] * m->m[14] - m->m[13] * m->m[10]);
	scaler_t d2 = m->m[4] * (m->m[10] * m->m[15] - m->m[14] * m->m[11]) - m->m[6] * (m->m[8] * m->m[15] - m->m[12] * m->m[11]) + m->m[7] * (m->m[8] * m->m[14] - m->m[12] * m->m[10]);
	scaler_t d3 = m->m[4] * (m->m[9] * m->m[15] - m->m[13] * m->m[11]) - m->m[5] * (m->m[8] * m->m[15] - m->m[12] * m->m[11]) + m->m[7] * (m->m[8] * m->m[13] - m->m[12] * m->m[9]);
	scaler_t d4 = m->m[4] * (m->m[9] * m->m[14] - m->m[13] * m->m[10]) - m->m[5] * (m->m[8] * m->m[14] - m->m[12] * m->m[10]) + m->m[6] * (m->m[8] * m->m[13] - m->m[12] * m->m[9]);
	scaler_t det = m->m[0]*d1 - m->m[1]*d2 + m->m[2]*d3 - m->m[3]*d4;

	if( scaler_abs(det) > SCALAR_EPSILON ) // testing if not zero
	{
		mat4_t cofactor_matrix;
		cofactor_matrix.m[ 0] = +(d1);
		cofactor_matrix.m[ 1] = -(d2);
		cofactor_matrix.m[ 2] = +(d3);
		cofactor_matrix.m[ 3] = -(d4);
		cofactor_matrix.m[ 4] = -(m->m[1] * (m->m[10]*m->m[15]-m->m[14]*m->m[11]) - m->m[2] * (m->m[9]*m->m[15]-m->m[13]*m->m[11]) + m->m[3] * (m->m[9]*m->m[14]-m->m[13]*m->m[10]));
		cofactor_matrix.m[ 5] = +(m->m[0] * (m->m[10]*m->m[15]-m->m[14]*m->m[11]) - m->m[2] * (m->m[8]*m->m[15]-m->m[12]*m->m[11]) + m->m[3] * (m->m[8]*m->m[14]-m->m[12]*m->m[10]));
		cofactor_matrix.m[ 6] = -(m->m[0] * (m->m[9]*m->m[15]-m->m[13]*m->m[11]) - m->m[1] * (m->m[8]*m->m[15]-m->m[12]*m->m[11]) + m->m[3] * (m->m[8]*m->m[13]-m->m[12]*m->m[9]));
		cofactor_matrix.m[ 7] = +(m->m[0] * (m->m[9]*m->m[14]-m->m[13]*m->m[10]) - m->m[1] * (m->m[8]*m->m[14]-m->m[12]*m->m[10]) + m->m[2] * (m->m[8]*m->m[13]-m->m[12]*m->m[9]));
		cofactor_matrix.m[ 8] = +(m->m[1] * (m->m[6]*m->m[15]-m->m[14]*m->m[7]) - m->m[2] * (m->m[5]*m->m[15]-m->m[13]*m->m[7]) + m->m[3] * (m->m[5]*m->m[14]-m->m[13]*m->m[6]));
		cofactor_matrix.m[ 9] = -(m->m[0] * (m->m[6]*m->m[15]-m->m[14]*m->m[7]) - m->m[2] * (m->m[4]*m->m[15]-m->m[12]*m->m[7]) + m->m[3] * (m->m[4]*m->m[14]-m->m[12]*m->m[6]));
		cofactor_matrix.m[10] = +(m->m[0] * (m->m[5]*m->m[15]-m->m[13]*m->m[7]) - m->m[1] * (m->m[4]*m->m[15]-m->m[12]*m->m[7]) + m->m[3] * (m->m[4]*m->m[13]-m->m[12]*m->m[5]));
		cofactor_matrix.m[11] = -(m->m[0] * (m->m[5]*m->m[14]-m->m[13]*m->m[6]) - m->m[1] * (m->m[4]*m->m[14]-m->m[12]*m->m[6]) + m->m[2] * (m->m[4]*m->m[13]-m->m[12]*m->m[5]));
		cofactor_matrix.m[12] = -(m->m[1] * (m->m[6]*m->m[11]-m->m[10]*m->m[7]) - m->m[2] * (m->m[5]*m->m[11]-m->m[9]*m->m[7]) + m->m[3] * (m->m[5]*m->m[10]-m->m[9]*m->m[6]));
		cofactor_matrix.m[13] = +(m->m[0] * (m->m[6]*m->m[11]-m->m[10]*m->m[7]) - m->m[2] * (m->m[4]*m->m[11]-m->m[8]*m->m[7]) + m->m[3] * (m->m[4]*m->m[10]-m->m[8]*m->m[6]));
		cofactor_matrix.m[14] = -(m->m[0] * (m->m[5]*m->m[11]-m->m[9]*m->m[7]) - m->m[1] * (m->m[4]*m->m[11]-m->m[8]*m->m[7]) + m->m[3] * (m->m[4]*m->m[9]-m->m[8]*m->m[5]));
		cofactor_matrix.m[15] = +(m->m[0] * (m->m[5]*m->m[10]-m->m[9]*m->m[6]) - m->m[1] * (m->m[4]*m->m[10]-m->m[8]*m->m[6]) + m->m[2] * (m->m[4]*m->m[9]-m->m[8]*m->m[5]));

		mat4_transpose( &cofactor_matrix );
		*m = cofactor_matrix;

		m->m[ 0] /= det;
		m->m[ 1] /= det;
		m->m[ 2] /= det;
		m->m[ 3] /= det;
		m->m[ 4] /= det;
		m->m[ 5] /= det;
		m->m[ 6] /= det;
		m->m[ 7] /= det;
		m->m[ 8] /= det;
		m->m[ 9] /= det;
		m->m[10] /= det;
		m->m[11] /= det;
		m->m[12] /= det;
		m->m[13] /= det;
		m->m[14] /= det;
		m->m[15] /= det;

		return true;
	}

	return false;
	#endif
}

void mat4_transpose( mat4_t* m )
{
    assert( m );

	// |  X  m04 m08 m12 |
	// | m01  X  m09 m13 |
	// | m02 m06  X  m14 |
	// | m03 m07 m11  X  |
	scaler_t tmp1 = m->m[ 1];
	scaler_t tmp2 = m->m[ 2];
	scaler_t tmp3 = m->m[ 3];
	scaler_t tmp4 = m->m[ 6];
	scaler_t tmp5 = m->m[ 7];
	scaler_t tmp6 = m->m[11];

	m->m[ 1] = m->m[ 4];
	m->m[ 2] = m->m[ 8];
	m->m[ 3] = m->m[12];
	m->m[ 6] = m->m[ 9];
	m->m[ 7] = m->m[13];
	m->m[11] = m->m[14];

	m->m[ 4] = tmp1;
	m->m[ 8] = tmp2;
	m->m[12] = tmp3;
	m->m[ 9] = tmp4;
	m->m[13] = tmp5;
	m->m[14] = tmp6;
}

mat4_t mat4_cofactor( const mat4_t* m )
{
	assert( m );
	// | m00 m04 m08 m12 |
	// | m01 m05 m09 m13 |
	// | m02 m06 m10 m14 |
	// | m03 m07 m11 m15 |
	return MAT4(
		+(m->m[5] * (m->m[10] * m->m[15] - m->m[14] * m->m[11]) - m->m[6] * (m->m[9] * m->m[15] - m->m[13] * m->m[11]) + m->m[7] * (m->m[9] * m->m[14] - m->m[13] * m->m[10])),
		-(m->m[4] * (m->m[10] * m->m[15] - m->m[14] * m->m[11]) - m->m[6] * (m->m[8] * m->m[15] - m->m[12] * m->m[11]) + m->m[7] * (m->m[8] * m->m[14] - m->m[12] * m->m[10])),
		+(m->m[4] * (m->m[ 9] * m->m[15] - m->m[13] * m->m[11]) - m->m[5] * (m->m[8] * m->m[15] - m->m[12] * m->m[11]) + m->m[7] * (m->m[8] * m->m[13] - m->m[12] * m->m[ 9])),
		-(m->m[4] * (m->m[ 9] * m->m[14] - m->m[13] * m->m[10]) - m->m[5] * (m->m[8] * m->m[14] - m->m[12] * m->m[10]) + m->m[6] * (m->m[8] * m->m[13] - m->m[12] * m->m[ 9])),
		-(m->m[1] * (m->m[10] * m->m[15] - m->m[14] * m->m[11]) - m->m[2] * (m->m[9] * m->m[15] - m->m[13] * m->m[11]) + m->m[3] * (m->m[9] * m->m[14] - m->m[13] * m->m[10])),
		+(m->m[0] * (m->m[10] * m->m[15] - m->m[14] * m->m[11]) - m->m[2] * (m->m[8] * m->m[15] - m->m[12] * m->m[11]) + m->m[3] * (m->m[8] * m->m[14] - m->m[12] * m->m[10])),
		-(m->m[0] * (m->m[ 9] * m->m[15] - m->m[13] * m->m[11]) - m->m[1] * (m->m[8] * m->m[15] - m->m[12] * m->m[11]) + m->m[3] * (m->m[8] * m->m[13] - m->m[12] * m->m[ 9])),
		+(m->m[0] * (m->m[ 9] * m->m[14] - m->m[13] * m->m[10]) - m->m[1] * (m->m[8] * m->m[14] - m->m[12] * m->m[10]) + m->m[2] * (m->m[8] * m->m[13] - m->m[12] * m->m[ 9])),
		+(m->m[1] * (m->m[ 6] * m->m[15] - m->m[14] * m->m[ 7]) - m->m[2] * (m->m[5] * m->m[15] - m->m[13] * m->m[ 7]) + m->m[3] * (m->m[5] * m->m[14] - m->m[13] * m->m[ 6])),
		-(m->m[0] * (m->m[ 6] * m->m[15] - m->m[14] * m->m[ 7]) - m->m[2] * (m->m[4] * m->m[15] - m->m[12] * m->m[ 7]) + m->m[3] * (m->m[4] * m->m[14] - m->m[12] * m->m[ 6])),
		+(m->m[0] * (m->m[ 5] * m->m[15] - m->m[13] * m->m[ 7]) - m->m[1] * (m->m[4] * m->m[15] - m->m[12] * m->m[ 7]) + m->m[3] * (m->m[4] * m->m[13] - m->m[12] * m->m[ 5])),
		-(m->m[0] * (m->m[ 5] * m->m[14] - m->m[13] * m->m[ 6]) - m->m[1] * (m->m[4] * m->m[14] - m->m[12] * m->m[ 6]) + m->m[2] * (m->m[4] * m->m[13] - m->m[12] * m->m[ 5])),
		-(m->m[1] * (m->m[ 6] * m->m[11] - m->m[10] * m->m[ 7]) - m->m[2] * (m->m[5] * m->m[11] - m->m[ 9] * m->m[ 7]) + m->m[3] * (m->m[5] * m->m[10] - m->m[ 9] * m->m[ 6])),
		+(m->m[0] * (m->m[ 6] * m->m[11] - m->m[10] * m->m[ 7]) - m->m[2] * (m->m[4] * m->m[11] - m->m[ 8] * m->m[ 7]) + m->m[3] * (m->m[4] * m->m[10] - m->m[ 8] * m->m[ 6])),
		-(m->m[0] * (m->m[ 5] * m->m[11] - m->m[ 9] * m->m[ 7]) - m->m[1] * (m->m[4] * m->m[11] - m->m[ 8] * m->m[ 7]) + m->m[3] * (m->m[4] * m->m[ 9] - m->m[ 8] * m->m[ 5])),
		+(m->m[0] * (m->m[ 5] * m->m[10] - m->m[ 9] * m->m[ 6]) - m->m[1] * (m->m[4] * m->m[10] - m->m[ 8] * m->m[ 6]) + m->m[2] * (m->m[4] * m->m[ 9] - m->m[ 8] * m->m[ 5]))
	);
}

void mat4_adjoint( mat4_t* m )
{
	mat4_t cofactor_matrix = mat4_cofactor( m );
	mat4_transpose( &cofactor_matrix );
	*m = cofactor_matrix;
}

mat4_t mat4_from_axis3_angle( const vec3_t* axis, scaler_t angle )
{
	scaler_t sin_a           = scaler_sin(angle);
	scaler_t cos_a           = scaler_cos(angle);
	scaler_t one_minus_cos_a = 1 - cos_a;

	vec3_t ax = *axis;
    vec3_normalize( &ax );

	return MAT4(
		cos_a + (ax.x * ax.x) * one_minus_cos_a,
		ax.y * ax.x * one_minus_cos_a + ax.z * sin_a,
		ax.z * ax.x * one_minus_cos_a - ax.y * sin_a,
		0.0f,

		ax.x * ax.y * one_minus_cos_a - ax.z * sin_a,
		cos_a + (ax.y * ax.y) * one_minus_cos_a,
		ax.z * ax.y * one_minus_cos_a + ax.x * sin_a,
		0.0f,

		ax.x * ax.z * one_minus_cos_a + ax.y * sin_a,
		ax.y * ax.z * one_minus_cos_a - ax.x * sin_a,
		cos_a + (ax.z * ax.z) * one_minus_cos_a,
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	);
}

const char* mat4_to_string( const mat4_t* m )
{
	static char string_buffer[ 128 ];
	#if defined(LIBM3D_USE_LONG_DOUBLE)
	snprintf( string_buffer, sizeof(string_buffer) - 1,
		"|%-6.2Lf %-6.2Lf %-6.2Lf %6.2Lf|\n"
		"|%-6.2Lf %-6.2Lf %-6.2Lf %6.2Lf|\n"
		"|%-6.2Lf %-6.2Lf %-6.2Lf %6.2Lf|\n"
		"|%-6.2Lf %-6.2Lf %-6.2Lf %6.2Lf|\n",
		m->m[ 0], m->m[ 4], m->m[ 8], m->m[12],
		m->m[ 1], m->m[ 5], m->m[ 9], m->m[13],
		m->m[ 2], m->m[ 6], m->m[10], m->m[14],
		m->m[ 3], m->m[ 7], m->m[11], m->m[15]
 	);
	#elif defined(LIBM3D_USE_DOUBLE)
	snprintf( string_buffer, sizeof(string_buffer) - 1,
		"|%-6.2lf %-6.2lf %-6.2lf %6.2lf|\n"
		"|%-6.2lf %-6.2lf %-6.2lf %6.2lf|\n"
		"|%-6.2lf %-6.2lf %-6.2lf %6.2lf|\n"
		"|%-6.2lf %-6.2lf %-6.2lf %6.2lf|\n",
		m->m[ 0], m->m[ 4], m->m[ 8], m->m[12],
		m->m[ 1], m->m[ 5], m->m[ 9], m->m[13],
		m->m[ 2], m->m[ 6], m->m[10], m->m[14],
		m->m[ 3], m->m[ 7], m->m[11], m->m[15]
 	);
	#else
	snprintf( string_buffer, sizeof(string_buffer) - 1,
		"|%-6.2f %-6.2f %-6.2f %6.2f|\n"
		"|%-6.2f %-6.2f %-6.2f %6.2f|\n"
		"|%-6.2f %-6.2f %-6.2f %6.2f|\n"
		"|%-6.2f %-6.2f %-6.2f %6.2f|\n",
		m->m[ 0], m->m[ 4], m->m[ 8], m->m[12],
		m->m[ 1], m->m[ 5], m->m[ 9], m->m[13],
		m->m[ 2], m->m[ 6], m->m[10], m->m[14],
		m->m[ 3], m->m[ 7], m->m[11], m->m[15]
 	);
	#endif
	string_buffer[ sizeof(string_buffer) - 1 ] = '\0';
	return string_buffer;
}

#if 0
const vec4_t* mat4_x_vector( const mat4_t* m )
{
    return (vec4_t*) &m->x;
}

const vec4_t* mat4_y_vector( const mat4_t* m )
{
    return (vec4_t*) &m->y;
}

const vec4_t* mat4_z_vector( const mat4_t* m )
{
    return (vec4_t*) &m->z;
}

const vec4_t* mat4_w_vector( const mat4_t* m )
{
    return (vec4_t*) &m->w;
}
#endif
