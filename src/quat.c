/* Copyright (C) 2013 by Joseph A. Marrero, http://www.manvscode.com/
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
#include "quat.h"

quat_t quat_from_axis3_angle( const vec3_t* axis, scaler_t angle )
{
	quat_t q;

	//vec3_normalize( axis );

	#if defined(QUAT_USE_LONG_DOUBLE)
	q.w = cosl( angle / 2.0f );
	q.x = axis->x * sinl( angle / 2.0f );
	q.y = axis->y * sinl( angle / 2.0f );
	q.z = axis->z * sinl( angle / 2.0f );
	#elif defined(QUAT_USE_DOUBLE)
	q.w = cos( angle / 2.0f );
	q.x = axis->x * sin( angle / 2.0f );
	q.y = axis->y * sin( angle / 2.0f );
	q.z = axis->z * sin( angle / 2.0f );
	#else
	q.w = cosf( angle / 2.0f );
	q.x = axis->x * sinf( angle / 2.0f );
	q.y = axis->y * sinf( angle / 2.0f );
	q.z = axis->z * sinf( angle / 2.0f );
	#endif

	quat_normalize( &q );

	return q;
}

quat_t quat_from_axis4_angle( const vec4_t* axis, scaler_t angle )
{
	quat_t q;

	//vec4_normalize( axis );

	#if defined(QUAT_USE_LONG_DOUBLE)
	q.w = cosl( angle / 2.0f );
	q.x = axis->x * sinl( angle / 2.0f );
	q.y = axis->y * sinl( angle / 2.0f );
	q.z = axis->z * sinl( angle / 2.0f );
	#elif defined(QUAT_USE_DOUBLE)
	q.w = cos( angle / 2.0f );
	q.x = axis->x * sin( angle / 2.0f );
	q.y = axis->y * sin( angle / 2.0f );
	q.z = axis->z * sin( angle / 2.0f );
	#else
	q.w = cosf( angle / 2.0f );
	q.x = axis->x * sinf( angle / 2.0f );
	q.y = axis->y * sinf( angle / 2.0f );
	q.z = axis->z * sinf( angle / 2.0f );
	#endif

	quat_normalize( &q );

	return q;
}

quat_t quat_from_vec3( const vec3_t* v )
{
	quat_t q;

	q.w = 0.0f;
	q.x = v->x;
	q.y = v->y;
	q.z = v->z;

	return q;
}

quat_t quat_from_vec4( const vec4_t* v )
{
	quat_t q;

	q.w = 0.0f;
	q.x = v->x;
	q.y = v->y;
	q.z = v->z;

	return q;
}

quat_t quat_from_mat3( const mat3_t* m )
{
	quat_t q;

	scaler_t trace = m->m[0] + m->m[4] + m->m[8]; /* add the diagonal values */

	if( trace > 0.0f )
	{
		#if defined(QUAT_USE_LONG_DOUBLE)
		scaler_t s = 0.5 / sqrtl( trace );
		#elif defined(QUAT_USE_DOUBLE)
		scaler_t s = 0.5 / sqrt( trace );
		#else
		scaler_t s = 0.5 / sqrtf( trace );
		#endif

		q.w = 0.25 / s;
		q.x = (m->m[7] - m->m[5]) * s;
		q.y = (m->m[2] - m->m[6]) * s;
		q.z = (m->m[3] - m->m[1]) * s;
	}
	else
	{
		#if defined(QUAT_USE_LONG_DOUBLE)
		scaler_t max_diagonal_elem = maxld( m->m[0], maxld( m->m[4], m->m[8] ) );
		#elif defined(QUAT_USE_DOUBLE)
		scaler_t max_diagonal_elem = maxd( m->m[0], maxd( m->m[4], m->m[8] ) );
		#else
		scaler_t max_diagonal_elem = maxf( m->m[0], maxf( m->m[4], m->m[8] ) );
		#endif

		#if defined(QUAT_USE_LONG_DOUBLE)
		if( fabsl(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#elif defined(QUAT_USE_DOUBLE)
		if( fabs(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#else
		if( fabsf(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#endif
		{
			#if defined(QUAT_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[0] - m->m[4] - m->m[8] ) * 2.0;
			#elif defined(QUAT_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[0] - m->m[4] - m->m[8] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[0] - m->m[4] - m->m[8] ) * 2.0;
			#endif

			q.x = 0.5 / s;
			q.y = (m->m[1] + m->m[3]) / s;
			q.z = (m->m[2] + m->m[6]) / s;
			q.w = (m->m[5] + m->m[7]) / s;
		}
		#if defined(QUAT_USE_LONG_DOUBLE)
		else if( fabsl(m->m[4] - max_diagonal_elem) < SCALAR_EPSILON )
		#elif defined(QUAT_USE_DOUBLE)
		else if( fabs(m->m[4] - max_diagonal_elem) < SCALAR_EPSILON )
		#else
		else if( fabsf(m->m[4] - max_diagonal_elem) < SCALAR_EPSILON )
		#endif
		{
			#if defined(QUAT_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[4] - m->m[0] - m->m[8] ) * 2.0;
			#elif defined(QUAT_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[4] - m->m[0] - m->m[8] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[4] - m->m[0] - m->m[8] ) * 2.0;
			#endif

			q.x = (m->m[1] + m->m[3]) / s;
			q.y = 0.5 / s;
			q.z = (m->m[5] + m->m[7]) / s;
			q.w = (m->m[2] + m->m[6]) / s;
		}
		else
		{
			#if defined(QUAT_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[8] - m->m[0] - m->m[4] ) * 2.0;
			#elif defined(QUAT_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[8] - m->m[0] - m->m[4] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[8] - m->m[0] - m->m[4] ) * 2.0;
			#endif

			q.x = (m->m[2] + m->m[6]) / s;
			q.y = (m->m[5] + m->m[7]) / s;
			q.x = 0.5 / s;
			q.w = (m->m[1] + m->m[3]) / s;
		}
	}

	return q;
}

quat_t quat_from_mat4( const mat4_t* m )
{
	quat_t q;

	scaler_t trace = m->m[0] + m->m[5] + m->m[10] + 1; /* add the diagonal values */

	if( trace > 0.0f )
	{
		#if defined(QUAT_USE_LONG_DOUBLE)
		scaler_t s = 0.5 / sqrtl( trace );
		#elif defined(QUAT_USE_DOUBLE)
		scaler_t s = 0.5 / sqrt( trace );
		#else
		scaler_t s = 0.5 / sqrtf( trace );
		#endif

		q.w = 0.25 / s;
		q.x = (m->m[9] - m->m[6]) * s;
		q.y = (m->m[2] - m->m[8]) * s;
		q.z = (m->m[4] - m->m[1]) * s;
	}
	else
	{
		#if defined(QUAT_USE_LONG_DOUBLE)
		scaler_t max_diagonal_elem = maxld( m->m[0], maxld( m->m[5], m->m[10] ) );
		#elif defined(QUAT_USE_DOUBLE)
		scaler_t max_diagonal_elem = maxd( m->m[0], maxd( m->m[5], m->m[10] ) );
		#else
		scaler_t max_diagonal_elem = maxf( m->m[0], maxf( m->m[5], m->m[10] ) );
		#endif

		#if defined(QUAT_USE_LONG_DOUBLE)
		if( fabsl(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#elif defined(QUAT_USE_DOUBLE)
		if( fabs(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#else
		if( fabsf(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#endif
		{
			#if defined(QUAT_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[0] - m->m[5] - m->m[10] ) * 2.0;
			#elif defined(QUAT_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[0] - m->m[5] - m->m[10] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[0] - m->m[5] - m->m[10] ) * 2.0;
			#endif

			q.x = 0.5 / s;
			q.y = (m->m[1] + m->m[4]) / s;
			q.z = (m->m[2] + m->m[8]) / s;
			q.w = (m->m[6] + m->m[9]) / s;
		}
		#if defined(QUAT_USE_LONG_DOUBLE)
		else if( fabsl(m->m[5] - max_diagonal_elem) < SCALAR_EPSILON )
		#elif defined(QUAT_USE_DOUBLE)
		else if( fabs(m->m[5] - max_diagonal_elem) < SCALAR_EPSILON )
		#else
		else if( fabsf(m->m[5] - max_diagonal_elem) < SCALAR_EPSILON )
		#endif
		{
			#if defined(QUAT_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[5] - m->m[0] - m->m[10] ) * 2.0;
			#elif defined(QUAT_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[5] - m->m[0] - m->m[10] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[5] - m->m[0] - m->m[10] ) * 2.0;
			#endif

			q.x = (m->m[1] + m->m[4]) / s;
			q.y = 0.5 / s;
			q.z = (m->m[6] + m->m[9]) / s;
			q.w = (m->m[2] + m->m[8]) / s;
		}
		else
		{
			#if defined(QUAT_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[10] - m->m[0] - m->m[5] ) * 2.0;
			#elif defined(QUAT_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[10] - m->m[0] - m->m[5] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[10] - m->m[0] - m->m[5] ) * 2.0;
			#endif

			q.x = (m->m[2] + m->m[8]) / s;
			q.y = (m->m[6] + m->m[9]) / s;
			q.x = 0.5 / s;
			q.w = (m->m[1] + m->m[4]) / s;
		}
	}

	return q;
}

quat_t quat_add( const quat_t* a, const quat_t* b )
{
	quat_t result;

	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	result.w = a->w + b->w;

	return result;
}

quat_t quat_multiply( const quat_t* a, const quat_t* b )
{
	quat_t result;

	result.w = a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z;
	result.x = a->w * b->x + a->x * b->w - a->y * b->z + a->z * b->y;
	result.y = a->w * b->y + a->x * b->z + a->y * b->w - a->z * b->x;
	result.z = a->w * b->z - a->x * b->y + a->y * b->x + a->z * b->w;

	return result;
}

void quat_scale( quat_t* q, scaler_t s )
{
	q->x *= s;
	q->y *= s;
	q->z *= s;
	q->w *= s;
}

scaler_t quat_dot_product( const quat_t* a, const quat_t* b )
{
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

quat_t quat_slerp( const quat_t* a, const quat_t* b, scaler_t t )
{
	scaler_t dot = a->w * b->w + a->x * b->x + a->y * b->y + a->z * b->z;

	if( fabs(dot) > 1.0f )
	{
		return *a;
	}

	scaler_t sin_of_omega = sqrt( 1.0f - dot * dot );

	quat_t result;

	// TODO: Implement this!
	assert( false );

	return result;
}

vec3_t quat_rotate3( const quat_t* q, const vec3_t* v )
{
	quat_t q_v = quat_from_vec3( v );
	q_v.w = 0.0f;

	quat_t q_inverse = quat_conjugate( q );
	quat_t q_v_inverse = quat_multiply( &q_v, &q_inverse );
	quat_t q_result = quat_multiply( q, &q_v_inverse );

	vec3_t result = VEC3_VECTOR( q_result.x, q_result.y, q_result.z );
	return result;
}

vec4_t quat_rotate4( const quat_t* q, const vec4_t* v )
{
	quat_t q_v = *v;//quat_from_vec4( v );
	q_v.w = 0.0f;

	quat_t q_inverse = quat_conjugate( q );
	quat_t q_v_inverse = quat_multiply( &q_v, &q_inverse );
	quat_t q_result = quat_multiply( q, &q_v_inverse );

	vec4_t result = VEC4_VECTOR( q_result.x, q_result.y, q_result.z, 0.0f );
	return result;
}

scaler_t quat_magnitude( const quat_t* q )
{
	#if defined(QUAT_USE_LONG_DOUBLE)
    return sqrtl( q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w );
	#elif defined(QUAT_USE_DOUBLE)
    return sqrt( q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w );
	#else
    return sqrtf( q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w );
	#endif
}

quat_t quat_conjugate( const quat_t* q )
{
	quat_t result;

	result.w =  q->w;
	result.x = -q->x;
	result.y = -q->y;
	result.z = -q->z;

	return result;
}

void quat_normalize( quat_t* q )
{
	scaler_t magnitude = quat_magnitude( q );

	q->w /= magnitude;
	q->x /= magnitude;
	q->y /= magnitude;
	q->z /= magnitude;
}

mat3_t quat_to_mat3( const quat_t* q )
{
	mat3_t result = MAT3_MATRIX(
		1-2*q->y*q->y-2*q->z*q->z,  2*q->x*q->y+2*q->w*q->z,   2*q->x*q->z-2*q->w*q->y,
		2*q->x*q->y-2*q->w*q->z,    1-2*q->x*q->x-2*q->z*q->z, 2*q->y*q->z+2*q->w*q->x,
		2*q->x*q->z+2*q->w*q->y,    2*q->y*q->z-2*q->w*q->x,   1-2*q->x*q->x-2*q->y*q->y
	);

	return result;
}

mat4_t quat_to_mat4( const quat_t* q )
{
	mat4_t result = MAT4_MATRIX(
		1-2*q->y*q->y-2*q->z*q->z,  2*q->x*q->y+2*q->w*q->z,   2*q->x*q->z-2*q->w*q->y,   0.0f,
		2*q->x*q->y-2*q->w*q->z,    1-2*q->x*q->x-2*q->z*q->z, 2*q->y*q->z+2*q->w*q->x,   0.0f,
		2*q->x*q->z+2*q->w*q->y,    2*q->y*q->z-2*q->w*q->x,   1-2*q->x*q->x-2*q->y*q->y, 0.0f,
		0.0f,                       0.0f,                      0.0f,                      1.0f
	);

	return result;
}

scaler_t quat_angle( const quat_t* q )
{
	#if defined(QUAT_USE_LONG_DOUBLE)
	return acosl( q->w ) * 2.0;
	#elif defined(QUAT_USE_DOUBLE)
	return acos( q->w ) * 2.0;
	#else
	return acosf( q->w ) * 2.0f;
	#endif
}

void quat_extract_axis3_and_angle( const quat_t* q, vec3_t* axis, scaler_t* angle )
{
	#if defined(QUAT_USE_LONG_DOUBLE)
	*angle = acosl( q->w ) * 2.0;
	#elif defined(QUAT_USE_DOUBLE)
	*angle = acos( q->w ) * 2.0;
	#else
	*angle = acosf( q->w ) * 2.0f;
	#endif

	#if defined(QUAT_USE_LONG_DOUBLE)
	scaler_t sin_angle = sinl( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
	#elif defined(QUAT_USE_DOUBLE)
	scaler_t sin_angle = sin( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
	#else
	scaler_t sin_angle = sinf( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
	#endif
}

void quat_extract_axis4_and_angle( const quat_t* q, vec4_t* axis, scaler_t* angle )
{
	#if defined(QUAT_USE_LONG_DOUBLE)
	*angle = acosl( q->w ) * 2.0;
	#elif defined(QUAT_USE_DOUBLE)
	*angle = acos( q->w ) * 2.0;
	#else
	*angle = acosf( q->w ) * 2.0f;
	#endif

	#if defined(QUAT_USE_LONG_DOUBLE)
	scaler_t sin_angle = sinl( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
	axis->w = 0.0f;
	#elif defined(QUAT_USE_DOUBLE)
	scaler_t sin_angle = sin( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
	axis->w = 0.0f;
	#else
	scaler_t sin_angle = sinf( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
	axis->w = 0.0f;
	#endif
}

