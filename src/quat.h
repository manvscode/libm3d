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

static inline scaler_t quat_magnitude( const quat_t* q )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return sqrtl( q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w );
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return sqrt( q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w );
	#else
    return sqrtf( q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w );
	#endif
}

static inline void quat_normalize( quat_t* q )
{
	scaler_t magnitude = quat_magnitude( q );

	q->w /= magnitude;
	q->x /= magnitude;
	q->y /= magnitude;
	q->z /= magnitude;
}

static inline quat_t quat_from_axis3_angle( const vec3_t* axis, scaler_t angle )
{
	//vec3_normalize( axis );

	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
	quat_t q = QUAT(
		axis->x * sinl( angle / 2.0f ),
		axis->y * sinl( angle / 2.0f ),
		axis->z * sinl( angle / 2.0f ),
		cosl( angle / 2.0f )
	);
	#elif defined(QUAT_USE_DOUBLE)
	quat_t q = QUAT(
		axis->x * sin( angle / 2.0f ),
		axis->y * sin( angle / 2.0f ),
		axis->z * sin( angle / 2.0f ),
		cos( angle / 2.0f )
	);
	#else
	quat_t q = QUAT(
		axis->x * sinf( angle / 2.0f ),
		axis->y * sinf( angle / 2.0f ),
		axis->z * sinf( angle / 2.0f ),
		cosf( angle / 2.0f )
	);
	#endif

	quat_normalize( &q );

	return q;
}

static inline quat_t quat_from_axis4_angle( const vec4_t* axis, scaler_t angle )
{
	//vec4_normalize( axis );

	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
	quat_t q = QUAT(
		axis->x * sinl( angle / 2.0f ),
		axis->y * sinl( angle / 2.0f ),
		axis->z * sinl( angle / 2.0f ),
		cosl( angle / 2.0f )
	);
	#elif defined(QUAT_USE_DOUBLE)
	quat_t q = QUAT(
		axis->x * sin( angle / 2.0f ),
		axis->y * sin( angle / 2.0f ),
		axis->z * sin( angle / 2.0f ),
		cos( angle / 2.0f )
	);
	#else
	quat_t q = QUAT(
		axis->x * sinf( angle / 2.0f ),
		axis->y * sinf( angle / 2.0f ),
		axis->z * sinf( angle / 2.0f ),
		cosf( angle / 2.0f )
	);
	#endif

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

quat_t      quat_from_mat3               ( const mat3_t* m );
quat_t      quat_from_mat4               ( const mat4_t* m );
quat_t      quat_slerp                   ( const quat_t* a, const quat_t* b, scaler_t t );



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

static inline vec3_t quat_rotate3( const quat_t* q, const vec3_t* v )
{
	quat_t q_v = quat_from_vec3( v );
	q_v.w = 0.0f;

	quat_t q_inverse = quat_conjugate( q );
	quat_t q_v_inverse = quat_multiply( &q_v, &q_inverse );
	quat_t q_result = quat_multiply( q, &q_v_inverse );

	return VEC3( q_result.x, q_result.y, q_result.z );
}

static inline vec4_t quat_rotate4( const quat_t* q, const vec4_t* v )
{
	quat_t q_v = *v;
	q_v.w = 0.0f;

	quat_t q_inverse = quat_conjugate( q );
	quat_t q_v_inverse = quat_multiply( &q_v, &q_inverse );
	quat_t q_result = quat_multiply( q, &q_v_inverse );

	return VEC4( q_result.x, q_result.y, q_result.z, 0.0f );
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
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
	return acosl( q->w ) * 2.0;
	#elif defined(LIB3DMATH_USE_DOUBLE)
	return acos( q->w ) * 2.0;
	#else
	return acosf( q->w ) * 2.0f;
	#endif
}

static inline void quat_extract_axis3_and_angle( const quat_t* q, vec3_t* axis, scaler_t* angle )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
	*angle = acosl( q->w ) * 2.0;
	#elif defined(LIB3DMATH_USE_DOUBLE)
	*angle = acos( q->w ) * 2.0;
	#else
	*angle = acosf( q->w ) * 2.0f;
	#endif

	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
	scaler_t sin_angle = sinl( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
	#elif defined(LIB3DMATH_USE_DOUBLE)
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

static inline void quat_extract_axis4_and_angle( const quat_t* q, vec4_t* axis, scaler_t* angle )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
	*angle = acosl( q->w ) * 2.0;
	#elif defined(LIB3DMATH_USE_DOUBLE)
	*angle = acos( q->w ) * 2.0;
	#else
	*angle = acosf( q->w ) * 2.0f;
	#endif

	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
	scaler_t sin_angle = sinl( 0.5f * (*angle) );
	axis->x = q->x / sin_angle;
	axis->y = q->y / sin_angle;
	axis->z = q->z / sin_angle;
	axis->w = 0.0f;
	#elif defined(LIB3DMATH_USE_DOUBLE)
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



#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _QUAT_H_ */
