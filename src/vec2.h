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
#ifndef _VEC2_H_
#define _VEC2_H_
#include <float.h>
#include <limits.h>
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <stdbool.h>
#else
#error "Need a C99 compiler."
#endif
#include "mathematics.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Two Dimensional Vectors
 */
typedef struct vec2 {
	scaler_t x;
	scaler_t y;
} vec2_t;

typedef vec2_t pt2_t;

extern const vec2_t VEC2_ZERO;
extern const vec2_t VEC2_XUNIT;
extern const vec2_t VEC2_YUNIT;

const char* vec2_to_string     ( const vec2_t* v ); /* not thread safe */

/* |a|
 * |b|
 */
#define VEC2(a,b)  ((vec2_t){ .x = (a), .y = (b) })

static inline vec2_t vec2_add( const vec2_t* __restrict a, const vec2_t* __restrict b )
{
	return VEC2(
		a->x + b->x,
		a->y + b->y
	);
}

static inline vec2_t vec2_subtract( const vec2_t* __restrict a, const vec2_t* __restrict b )
{
	return VEC2(
		a->x - b->x,
		a->y - b->y
    );
}

static inline vec2_t vec2_multiply( const vec2_t* v, scaler_t s )
{
	return VEC2(
		v->x * s,
		v->y * s
	);
}

static inline void vec2_scale( vec2_t* v, scaler_t s )
{
    v->x *= s;
    v->y *= s;
}

static inline scaler_t vec2_dot_product( const vec2_t* __restrict a, const vec2_t* __restrict b )
{
    return a->x * b->x + a->y * b->y;
}

static inline vec2_t vec2_cross_product( const vec2_t* v )
{
	return VEC2(
		 v->y,
		-v->x
	);
}

static inline scaler_t vec2_determinant( const vec2_t* __restrict a, const vec2_t* __restrict b )
{
    return a->x * b->y - b->x * a->y;
}

static inline scaler_t vec2_magnitude( const vec2_t* v )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return sqrtl( v->x * v->x + v->y * v->y );
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return sqrt( v->x * v->x + v->y * v->y );
	#else /* default: use float */
    return sqrtf( v->x * v->x + v->y * v->y );
	#endif
}

static inline scaler_t vec2_distance( const vec2_t* __restrict a, const vec2_t* __restrict b )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return sqrtl(
		(a->x - b->x) * (a->x - b->x) +
		(a->y - b->y) * (a->y - b->y)
	);
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return sqrt(
		(a->x - b->x) * (a->x - b->x) +
		(a->y - b->y) * (a->y - b->y)
	);
	#else /* default: use float */
    return sqrtf(
		(a->x - b->x) * (a->x - b->x) +
		(a->y - b->y) * (a->y - b->y)
	);
	#endif
}

static inline scaler_t vec2_angle( const vec2_t* __restrict a, const vec2_t* __restrict b ) /* in radians */
{
    scaler_t dot_product = vec2_dot_product( a, b );
    scaler_t a_length    = vec2_magnitude( a );
    scaler_t b_length    = vec2_magnitude( b );

	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return acosl( dot_product / ( a_length * b_length ) );
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return acos( dot_product / ( a_length * b_length ) );
	#else /* default: use float */
    return acosf( dot_product / ( a_length * b_length ) );
	#endif
}

static inline void vec2_normalize( vec2_t* v )
{
	#if 1 /* Need more precision */
	scaler_t length = vec2_magnitude( v );
	if( length > 0.0f )
	{
		v->x /= length;
		v->y /= length;
	}
	#else
    scaler_t inverse_length = fast_inverse_sqrt( v->x * v->x + v->y * v->y );
    v->x *= inverse_length;
    v->y *= inverse_length;
	#endif
}

static inline bool vec2_is_normalized( const vec2_t* v )
{
	scaler_t length = vec2_magnitude( v );
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return (fabsl(length - 1.0f) < SCALAR_EPSILON);
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return (fabs(length - 1.0f) < SCALAR_EPSILON);
	#else /* default: use float */
    return (fabsf(length - 1.0f) < SCALAR_EPSILON);
	#endif
}

static inline void vec2_negate( vec2_t* v )
{
    v->x = -v->x;
    v->y = -v->y;
}

static inline bool vec2_compare( const vec2_t* __restrict a, const vec2_t* __restrict b )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return (fabsl(a->x - b->x) < SCALAR_EPSILON) &&
           (fabsl(a->y - b->y) < SCALAR_EPSILON);
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return (fabs(a->x - b->x) < SCALAR_EPSILON) &&
           (fabs(a->y - b->y) < SCALAR_EPSILON);
	#else /* default: use float */
    return (fabsf(a->x - b->x) < SCALAR_EPSILON) &&
           (fabsf(a->y - b->y) < SCALAR_EPSILON);
	#endif
}

static inline void vec2_zero( vec2_t* v )
{
	*v = VEC2_ZERO;
}

static inline vec2_t vec2_lerp( const vec2_t* __restrict a, const vec2_t* __restrict b, scaler_t s )
{
	return VEC2(
		linear_interpolation( s, a->x, b->x ),
		linear_interpolation( s, a->y, b->y )
	);
}

#define     vec2_area          vec2_determinant

#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _VEC2_H_ */
