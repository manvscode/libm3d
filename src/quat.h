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
#ifndef _QUAT_H_
#define _QUAT_H_
#include <float.h>
#include <limits.h>
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <stdbool.h>
#else
#error "Need a C99 compiler."
#endif
#include "mathematics.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Quaternion
 */
typedef vec4_t quat_t;

#define QUAT            VEC4
#define QUAT_XUNIT      VEC4_XUNIT
#define QUAT_YUNIT      VEC4_YUNIT
#define QUAT_ZUNIT      VEC4_ZUNIT
#define QUAT_WUNIT      VEC4_WUNIT

static inline scaler_t quat_magnitude( const quat_t* q )
{
    return scaler_sqrt( q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w );
}

static inline void quat_normalize( quat_t* q )
{
	scaler_t magnitude = quat_magnitude( q );

	if( magnitude > 0.0f )
	{
		q->w /= magnitude;
		q->x /= magnitude;
		q->y /= magnitude;
		q->z /= magnitude;
	}
}

static inline quat_t quat_from_axis3_angle( const vec3_t* axis, scaler_t angle )
{
	quat_t q = QUAT(
		axis->x * scaler_sin( angle / 2.0f ),
		axis->y * scaler_sin( angle / 2.0f ),
		axis->z * scaler_sin( angle / 2.0f ),
		scaler_cos( angle / 2.0f )
	);

	quat_normalize( &q );
	return q;
}

static inline quat_t quat_from_axis4_angle( const vec4_t* axis, scaler_t angle )
{
	//vec4_normalize( axis );
	quat_t q = QUAT(
		axis->x * scaler_sin( angle / 2.0f ),
		axis->y * scaler_sin( angle / 2.0f ),
		axis->z * scaler_sin( angle / 2.0f ),
		scaler_cos( angle / 2.0f )
	);

	quat_normalize( &q );
	return q;
}

static inline quat_t quat_from_vec3( const vec3_t* v )
{
	return QUAT(
		v->x,
		v->y,
		v->z,
		0.0f
	);
}

static inline quat_t quat_from_vec4( const vec4_t* v )
{
	return QUAT(
		v->x,
		v->y,
		v->z,
		0.0f
	);
}

quat_t quat_from_mat3  ( const mat3_t* m );
quat_t quat_from_mat4  ( const mat4_t* m );
quat_t quat_slerp      ( const quat_t* a, const quat_t* b, scaler_t t );



static inline quat_t quat_add( const quat_t* a, const quat_t* b )
{
	return QUAT(
		a->x + b->x,
		a->y + b->y,
		a->z + b->z,
		a->w + b->w
	);
}

static inline quat_t quat_multiply( const quat_t* a, const quat_t* b )
{
	return QUAT(
		a->w * b->x + a->x * b->w - a->y * b->z + a->z * b->y,
		a->w * b->y + a->x * b->z + a->y * b->w - a->z * b->x,
		a->w * b->z - a->x * b->y + a->y * b->x + a->z * b->w,
		a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z
	);
}

static inline void quat_scale( quat_t* q, scaler_t s )
{
	q->x *= s;
	q->y *= s;
	q->z *= s;
	q->w *= s;
}

static inline scaler_t quat_dot_product( const quat_t* a, const quat_t* b ) /* 1 := similiar rotations */
{
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

static inline quat_t quat_conjugate( const quat_t* q )
{
	return QUAT(
		-q->x,
		-q->y,
		-q->z,
		 q->w
	);
}

static inline vec3_t quat_multiply_vec3( const quat_t* q, const vec3_t* v )
{
	quat_t q_v = quat_from_vec3( v );
	q_v.w = 0.0f;

	quat_t q_inverse = quat_conjugate( q );
	quat_t q_v_inverse = quat_multiply( &q_v, &q_inverse );
	quat_t q_result = quat_multiply( q, &q_v_inverse );

	return VEC3( q_result.x, q_result.y, q_result.z );
}

static inline vec3_t quat_rotate3( const quat_t* q, const vec3_t* v )
{
	return quat_multiply_vec3( q, v );
}

static inline vec4_t quat_multiply_vec4( const quat_t* q, const vec4_t* v )
{
	quat_t q_v = *v;
	q_v.w = 0.0f;

	quat_t q_inverse = quat_conjugate( q );
	quat_t q_v_inverse = quat_multiply( &q_v, &q_inverse );
	quat_t q_result = quat_multiply( q, &q_v_inverse );

	return VEC4( q_result.x, q_result.y, q_result.z, 0.0f );
}

static inline vec4_t quat_rotate4( const quat_t* q, const vec4_t* v )
{
	return quat_multiply_vec4( q, v );
}

static inline mat3_t quat_to_mat3( const quat_t* q )
{
	return MAT3(
		1-2*q->y*q->y-2*q->z*q->z,  2*q->x*q->y+2*q->w*q->z,   2*q->x*q->z-2*q->w*q->y,
		2*q->x*q->y-2*q->w*q->z,    1-2*q->x*q->x-2*q->z*q->z, 2*q->y*q->z+2*q->w*q->x,
		2*q->x*q->z+2*q->w*q->y,    2*q->y*q->z-2*q->w*q->x,   1-2*q->x*q->x-2*q->y*q->y
	);
}

static inline mat4_t quat_to_mat4( const quat_t* q )
{
	return MAT4(
		1-2*q->y*q->y-2*q->z*q->z,  2*q->x*q->y+2*q->w*q->z,   2*q->x*q->z-2*q->w*q->y,   0.0f,
		2*q->x*q->y-2*q->w*q->z,    1-2*q->x*q->x-2*q->z*q->z, 2*q->y*q->z+2*q->w*q->x,   0.0f,
		2*q->x*q->z+2*q->w*q->y,    2*q->y*q->z-2*q->w*q->x,   1-2*q->x*q->x-2*q->y*q->y, 0.0f,
		0.0f,                       0.0f,                      0.0f,                      1.0f
	);
}

static inline scaler_t quat_angle( const quat_t* q )
{
	return scaler_acos( q->w ) * 2.0f;
}

static inline void quat_extract_axis3_and_angle( const quat_t* q, vec3_t* axis, scaler_t* angle )
{
	*angle = scaler_acos( q->w ) * 2.0f;

	scaler_t sin_angle = scaler_sin( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
}

static inline void quat_extract_axis4_and_angle( const quat_t* q, vec4_t* axis, scaler_t* angle )
{
	*angle = scaler_acos( q->w ) * 2.0f;

	scaler_t sin_angle = scaler_sin( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
	axis->w = 0.0f;
}

static inline quat_t quat_lerp( const quat_t* restrict a, const quat_t* restrict b, scaler_t s )
{
	return QUAT(
		m3d_linear_interpolation( s, a->x, b->x ),
		m3d_linear_interpolation( s, a->y, b->y ),
		m3d_linear_interpolation( s, a->z, b->z ),
		m3d_linear_interpolation( s, a->w, b->w )
	);
}


#define quat_to_string vec4_to_string


#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _QUAT_H_ */
