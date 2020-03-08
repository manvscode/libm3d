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
#ifndef _VEC2_H_
#define _VEC2_H_
#include <float.h>
#include <limits.h>
#include "mathematics.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Two Dimensional Vectors
 */
typedef struct vec2 {
	#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
	union {
		struct {
			scaler_t x;
			scaler_t y;
		};
		struct {
			scaler_t s;
			scaler_t t;
		};
	};
	#else
	scaler_t x;
	scaler_t y;
	#endif
} vec2_t;

typedef vec2_t pt2_t;

extern const vec2_t VEC2_ZERO;
extern const vec2_t VEC2_ONE;
extern const vec2_t VEC2_XUNIT;
extern const vec2_t VEC2_YUNIT;

const char* vec2_to_string     ( const vec2_t* v ); /* not thread safe */

/* |a|
 * |b|
 */
#define VEC2(a,b)  ((vec2_t){ .x = (a), .y = (b) })

static inline vec2_t vec2_add( const vec2_t* restrict a, const vec2_t* restrict b )
{
	return VEC2(
		a->x + b->x,
		a->y + b->y
	);
}

static inline vec2_t vec2_subtract( const vec2_t* restrict a, const vec2_t* restrict b )
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

static inline scaler_t vec2_dot_product( const vec2_t* restrict a, const vec2_t* restrict b )
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

static inline scaler_t vec2_determinant( const vec2_t* restrict a, const vec2_t* restrict b )
{
    return a->x * b->y - b->x * a->y;
}

static inline scaler_t vec2_magnitude( const vec2_t* v )
{
    return scaler_sqrt( v->x * v->x + v->y * v->y );
}

static inline scaler_t vec2_magnitude_squared( const vec2_t* v )
{
    return v->x * v->x + v->y * v->y;
}

static inline scaler_t vec2_distance( const vec2_t* restrict a, const vec2_t* restrict b )
{
    return scaler_sqrt(
		(a->x - b->x) * (a->x - b->x) +
		(a->y - b->y) * (a->y - b->y)
	);
}

static inline scaler_t vec2_angle( const vec2_t* restrict a, const vec2_t* restrict b ) /* in radians */
{
    scaler_t dot_product = vec2_dot_product( a, b );
    scaler_t a_length    = vec2_magnitude( a );
    scaler_t b_length    = vec2_magnitude( b );

    return scaler_acos( dot_product / ( a_length * b_length ) );
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
    return scaler_abs(length - 1.0f) < SCALAR_EPSILON;
}

static inline void vec2_negate( vec2_t* v )
{
    v->x = -v->x;
    v->y = -v->y;
}

static inline bool vec2_compare( const vec2_t* restrict a, const vec2_t* restrict b )
{
    return (scaler_abs(a->x - b->x) < SCALAR_EPSILON) &&
           (scaler_abs(a->y - b->y) < SCALAR_EPSILON);
}

static inline void vec2_zero( vec2_t* v )
{
	*v = VEC2_ZERO;
}

static inline vec2_t vec2_lerp( const vec2_t* restrict a, const vec2_t* restrict b, scaler_t s )
{
	return VEC2(
		m3d_linear_interpolation( s, a->x, b->x ),
		m3d_linear_interpolation( s, a->y, b->y )
	);
}

static inline scaler_t vec2_max_component( const vec2_t* v )
{
	return scaler_max(v->x, v->y);
}

static inline scaler_t vec2_min_component( const vec2_t* v )
{
	return scaler_min(v->x, v->y);
}

#define     vec2_area          vec2_determinant

#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _VEC2_H_ */
