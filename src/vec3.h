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
#ifndef _VEC3_H_
#define _VEC3_H_
#include "mathematics.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Three Dimensional Vectors
 */
typedef struct vec3 {
	scaler_t x;
	scaler_t y;
	scaler_t z;
} vec3_t;

typedef vec3_t pt3_t;

extern const vec3_t VEC3_ZERO;
extern const vec3_t VEC3_ONE;
extern const vec3_t VEC3_XUNIT;
extern const vec3_t VEC3_YUNIT;
extern const vec3_t VEC3_ZUNIT;

const char* vec3_to_string     ( const vec3_t* v ); /* not thread safe */

/* |a|
 * |b|
 * |c|
 */
#define VEC3(a,b,c)  ((vec3_t){ .x = (a), .y = (b), .z = (c) })

#define vec3_to_vec2( p_v ) ((vec2_t*)(p_v))

static inline vec3_t vec3_add( const vec3_t* restrict a, const vec3_t* restrict b )
{
	return VEC3(
		a->x + b->x,
		a->y + b->y,
		a->z + b->z
	);
}

static inline vec3_t vec3_subtract( const vec3_t* restrict a, const vec3_t* restrict b )
{
	return VEC3(
		a->x - b->x,
		a->y - b->y,
		a->z - b->z
	);
}

static inline vec3_t vec3_multiply( const vec3_t* v, scaler_t s )
{
	return VEC3(
    	v->x * s,
    	v->y * s,
    	v->z * s
	);
}

static inline void vec3_scale( vec3_t* v, scaler_t s )
{
    v->x *= s;
    v->y *= s;
    v->z *= s;
}

static inline scaler_t vec3_dot_product( const vec3_t* restrict a, const vec3_t* restrict b )
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

static inline vec3_t vec3_cross_product( const vec3_t* restrict a, const vec3_t* restrict b )
{
	return VEC3(
		a->y * b->z - a->z * b->y,
		a->z * b->x - a->x * b->z,
		a->x * b->y - a->y * b->x
	);
}

static inline scaler_t vec3_magnitude( const vec3_t* v )
{
    return scaler_sqrt( v->x * v->x + v->y * v->y + v->z * v->z );
}

static inline scaler_t vec3_distance( const vec3_t* restrict a, const vec3_t* restrict b )
{
    return scaler_sqrt(
		(a->x - b->x) * (a->x - b->x) +
		(a->y - b->y) * (a->y - b->y) +
		(a->z - b->z) * (a->z - b->z)
	);
}

static inline scaler_t vec3_angle( const vec3_t* restrict a, const vec3_t* restrict b ) /* in radians */
{
    scaler_t dot_product = vec3_dot_product( a, b );
    scaler_t a_length    = vec3_magnitude( a );
    scaler_t b_length    = vec3_magnitude( b );

    return scaler_acos( dot_product / ( a_length * b_length ) );
}

static inline void vec3_normalize( vec3_t* v )
{
	#if 1 /* Need more precision */
	scaler_t length = vec3_magnitude( v );
	if( length > 0.0f )
	{
		v->x /= length;
		v->y /= length;
		v->z /= length;
	}
	#else
    scaler_t inverse_length = fast_inverse_sqrt( v->x * v->x + v->y * v->y + v->z * v->z );
    v->x *= inverse_length;
    v->y *= inverse_length;
    v->z *= inverse_length;
	#endif
}

static inline bool vec3_is_normalized( const vec3_t* v )
{
	scaler_t length = vec3_magnitude( v );
    return scaler_abs(length - 1.0f) < SCALAR_EPSILON;
}

static inline void vec3_negate( vec3_t* v )
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

static inline bool vec3_compare( const vec3_t* restrict a, const vec3_t* restrict b )
{
    return (scaler_abs(a->x - b->x) < SCALAR_EPSILON) &&
           (scaler_abs(a->y - b->y) < SCALAR_EPSILON) &&
           (scaler_abs(a->z - b->z) < SCALAR_EPSILON);
}

static inline void vec3_zero( vec3_t* v )
{
	*v = VEC3_ZERO;
}

static inline vec3_t vec3_lerp( const vec3_t* restrict a, const vec3_t* restrict b, scaler_t s )
{
	return VEC3(
		linear_interpolation( s, a->x, b->x ),
		linear_interpolation( s, a->y, b->y ),
		linear_interpolation( s, a->z, b->z )
	);
}

static inline scaler_t vec3_max_component( const vec3_t* v )
{
	return scaler_max( scaler_max(v->x, v->y), v->z );
}

static inline scaler_t vec3_min_component( const vec3_t* v )
{
	return scaler_min( scaler_min(v->x, v->y), v->z );
}

#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _VEC3_H_ */
