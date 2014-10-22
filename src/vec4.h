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
#ifndef _VEC4_H_
#define _VEC4_H_
#include "mathematics.h"
#include "vec3.h"
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
extern const vec4_t VEC4_ONE;
extern const vec4_t VEC4_XUNIT;
extern const vec4_t VEC4_YUNIT;
extern const vec4_t VEC4_ZUNIT;
extern const vec4_t VEC4_WUNIT;

const char* vec4_to_string      ( const vec4_t* v ); /* not thread safe */

/* |a|
 * |b|
 * |c|
 * |d|
 */
#define VEC4(a,b,c,d)  (vec4_t){ .x = (a), .y = (b), .z = (c), .w = (d) }

#define vec4_to_vec2( p_v ) ((vec2_t*)(p_v))
#define vec4_to_vec3( p_v ) ((vec3_t*)(p_v))

static inline vec4_t vec4_add( const vec4_t* restrict a, const vec4_t* restrict b )
{
	return VEC4(
		a->x + b->x,
		a->y + b->y,
		a->z + b->z,
		a->w + b->w
	);
}

static inline vec4_t vec4_subtract( const vec4_t* restrict a, const vec4_t* restrict b )
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

static inline scaler_t vec4_dot_product( const vec4_t* restrict a, const vec4_t* restrict b )
{
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

/* 3D cross product because we use homogenous coordinates. */
static inline vec4_t vec4_cross_product( const vec4_t* restrict a, const vec4_t* restrict b )
{
	vec3_t result = vec3_cross_product(  vec4_to_vec3(a), vec4_to_vec3(b) );
	return VEC4( result.x, result.y, result.z, 0 );
}

static inline scaler_t vec4_magnitude( const vec4_t* v )
{
    return scaler_sqrt( v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w );
}

static inline scaler_t vec4_distance( const vec4_t* restrict a, const vec4_t* restrict b )
{
    return scaler_sqrt(
		(a->x - b->x) * (a->x - b->x) +
		(a->y - b->y) * (a->y - b->y) +
		(a->z - b->z) * (a->z - b->z) +
		(a->w - b->w) * (a->w - b->w)
	);
}

static inline scaler_t vec4_angle( const vec4_t* restrict a, const vec4_t* restrict b ) /* in radians */
{
    scaler_t dot_product = vec4_dot_product( a, b );
    scaler_t a_length    = vec4_magnitude( a );
    scaler_t b_length    = vec4_magnitude( b );

    return scaler_acos( dot_product / ( a_length * b_length ) );
}

static inline void vec4_normalize( vec4_t* v )
{
    #if 1 /* Need more precision */
	scaler_t length = vec4_magnitude( v );
	if( length > 0.0f )
	{
		v->x /= length;
		v->y /= length;
		v->z /= length;
		v->w /= length;
	}
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
	scaler_t length = vec4_magnitude( v );
    return scaler_abs(length - 1.0f) < SCALAR_EPSILON;
}

static inline void vec4_negate( vec4_t* v )
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
    v->w = -v->w;
}

static inline bool vec4_compare( const vec4_t* restrict a, const vec4_t* restrict b )
{
    return (scaler_abs(a->x - b->x) < SCALAR_EPSILON) &&
           (scaler_abs(a->y - b->y) < SCALAR_EPSILON) &&
           (scaler_abs(a->z - b->z) < SCALAR_EPSILON) &&
           (scaler_abs(a->w - b->w) < SCALAR_EPSILON);
}

static inline void vec4_zero( vec4_t* v )
{
	*v = VEC4_ZERO;
}

static inline vec4_t vec4_lerp( const vec4_t* restrict a, const vec4_t* restrict b, scaler_t s )
{
	return VEC4(
		linear_interpolation( s, a->x, b->x ),
		linear_interpolation( s, a->y, b->y ),
		linear_interpolation( s, a->z, b->z ),
		linear_interpolation( s, a->w, b->w )
	);
}

static inline scaler_t vec4_max_component( const vec4_t* v )
{
	return scaler_max( scaler_max( scaler_max(v->x, v->y), v->z ), v->w );
}

static inline scaler_t vec4_min_component( const vec4_t* v )
{
	return scaler_min( scaler_min( scaler_min(v->x, v->y), v->z ), v->w );
}


#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _VEC4_H_ */
