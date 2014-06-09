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
#ifndef _VEC4_H_
#define _VEC4_H_
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
 * Four Dimensional Vectors
 */
typedef struct vec4 {
	scaler_t x;
	scaler_t y;
	scaler_t z;
	scaler_t w;
} vec4_t;

typedef vec4_t pt4_t;

extern const vec4_t VEC4_ZERO;
extern const vec4_t VEC4_XUNIT;
extern const vec4_t VEC4_YUNIT;
extern const vec4_t VEC4_ZUNIT;
extern const vec4_t VEC4_WUNIT;

/* |a|
 * |b|
 * |c|
 * |d|
 */
#define VEC4(a,b,c,d)  (vec4_t){ .x = a, .y = b, .z = c, .w = d }

static inline vec4_t vec4_add( const vec4_t* __restrict a, const vec4_t* __restrict b )
{
	return VEC4(
		a->x + b->x,
		a->y + b->y,
		a->z + b->z,
		a->w + b->w
	);
}

static inline vec4_t vec4_subtract( const vec4_t* __restrict a, const vec4_t* __restrict b )
{
	return VEC4(
		a->x - b->x,
		a->y - b->y,
		a->z - b->z,
		a->w - b->w
	);
}

static inline vec4_t vec4_multiply( const vec4_t* v, scaler_t s )
{
	return VEC4(
		v->x * s,
		v->y * s,
		v->z * s,
		v->w * s
	);
}

static inline void vec4_scale( vec4_t* v, scaler_t s )
{
    v->x *= s;
    v->y *= s;
    v->z *= s;
    v->w *= s;
}

static inline scaler_t vec4_dot_product( const vec4_t* __restrict a, const vec4_t* __restrict b )
{
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

static inline vec4_t vec4_cross_product( const vec4_t* __restrict a, const vec4_t* __restrict b, const vec4_t* __restrict c )
{
    vec4_t result;
    // TODO: Implement this!
    assert( false );
    return result;
}

static inline scaler_t vec4_magnitude( const vec4_t* v )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return sqrtl( v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w );
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return sqrt( v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w );
	#else /* default: use float */
    return sqrtf( v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w );
	#endif
}

static inline scaler_t vec4_distance( const vec4_t* __restrict a, const vec4_t* __restrict b )
{
	#if defined(VEC3_USE_LONG_DOUBLE)
    return sqrtl(
		(a->x - b->x) * (a->x - b->x) +
		(a->y - b->y) * (a->y - b->y) +
		(a->z - b->z) * (a->z - b->z) +
		(a->w - b->w) * (a->w - b->w)
	);
	#elif defined(VEC3_USE_DOUBLE)
    return sqrt(
		(a->x - b->x) * (a->x - b->x) +
		(a->y - b->y) * (a->y - b->y) +
		(a->z - b->z) * (a->z - b->z) +
		(a->w - b->w) * (a->w - b->w)
	);
	#else /* default: use float */
    return sqrtf(
		(a->x - b->x) * (a->x - b->x) +
		(a->y - b->y) * (a->y - b->y) +
		(a->z - b->z) * (a->z - b->z) +
		(a->w - b->w) * (a->w - b->w)
	);
	#endif
}

static inline scaler_t vec4_angle( const vec4_t* __restrict a, const vec4_t* __restrict b ) /* in radians */
{
    scaler_t dot_product = vec4_dot_product( a, b );
    scaler_t a_length    = vec4_magnitude( a );
    scaler_t b_length    = vec4_magnitude( b );

	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return acosl( dot_product / ( a_length * b_length ) );
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return acos( dot_product / ( a_length * b_length ) );
	#else /* default: use float */
    return acosf( dot_product / ( a_length * b_length ) );
	#endif
}

static inline void vec4_normalize( vec4_t* v )
{
    #if 1 /* Need more precision */
    scaler_t length = vec4_magnitude( v );
    v->x /= length;
    v->y /= length;
    v->z /= length;
    v->w /= length;
    #else
    scaler_t inverse_length = fast_inverse_sqrt( v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w );
    v->x *= inverse_length;
    v->y *= inverse_length;
    v->z *= inverse_length;
    v->w *= inverse_length;
    #endif
}

static inline bool vec4_is_normalized( const vec4_t* v )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return (fabsl(v->x - 1.0f) < SCALAR_EPSILON) &&
           (fabsl(v->y - 1.0f) < SCALAR_EPSILON) &&
           (fabsl(v->z - 1.0f) < SCALAR_EPSILON) &&
           (fabsl(v->w - 1.0f) < SCALAR_EPSILON);
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return (fabs(v->x - 1.0f) < SCALAR_EPSILON) &&
           (fabs(v->y - 1.0f) < SCALAR_EPSILON) &&
           (fabs(v->z - 1.0f) < SCALAR_EPSILON) &&
           (fabs(v->w - 1.0f) < SCALAR_EPSILON);
	#else /* default: use float */
    return (fabsf(v->x - 1.0f) < SCALAR_EPSILON) &&
           (fabsf(v->y - 1.0f) < SCALAR_EPSILON) &&
           (fabsf(v->z - 1.0f) < SCALAR_EPSILON) &&
           (fabsf(v->w - 1.0f) < SCALAR_EPSILON);
	#endif
}

static inline void vec4_negate( vec4_t* v )
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
    v->w = -v->w;
}

static inline bool vec4_compare( const vec4_t* __restrict a, const vec4_t* __restrict b )
{
	#if defined(LIB3DMATH_USE_LONG_DOUBLE)
    return (fabsl(a->x - b->x) < SCALAR_EPSILON) &&
           (fabsl(a->y - b->y) < SCALAR_EPSILON) &&
           (fabsl(a->z - b->z) < SCALAR_EPSILON) &&
           (fabsl(a->w - b->w) < SCALAR_EPSILON);
	#elif defined(LIB3DMATH_USE_DOUBLE)
    return (fabs(a->x - b->x) < SCALAR_EPSILON) &&
           (fabs(a->y - b->y) < SCALAR_EPSILON) &&
           (fabs(a->z - b->z) < SCALAR_EPSILON) &&
           (fabs(a->w - b->w) < SCALAR_EPSILON);
	#else /* default: use float */
    return (fabsf(a->x - b->x) < SCALAR_EPSILON) &&
           (fabsf(a->y - b->y) < SCALAR_EPSILON) &&
           (fabsf(a->z - b->z) < SCALAR_EPSILON) &&
           (fabsf(a->w - b->w) < SCALAR_EPSILON);
	#endif
}

static inline void vec4_zero( vec4_t* v )
{
	*v = VEC4_ZERO;
}

static inline vec4_t vec4_lerp( const vec4_t* __restrict a, const vec4_t* __restrict b, scaler_t s )
{
	return VEC4(
		linear_interpolation( s, a->x, b->x ),
		linear_interpolation( s, a->y, b->y ),
		linear_interpolation( s, a->z, b->z ),
		linear_interpolation( s, a->w, b->w )
	);
}


const char* vec4_to_string      ( const vec4_t* v ); /* not thread safe */

#define vec4_to_vec2( p_v ) ((vec2_t*)(p_v))
#define vec4_to_vec3( p_v ) ((vec3_t*)(p_v))


#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _VEC4_H_ */
