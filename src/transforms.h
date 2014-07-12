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
#ifndef _TRANSFORMS_H_
#define _TRANSFORMS_H_
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
#include "mat4.h"
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Transformations
 */

static inline mat4_t translate( const vec3_t* t )
{
	assert( t );
	return MAT4(
		 1.0,  0.0,  0.0,  0.0,
		 0.0,  1.0,  0.0,  0.0,
		 0.0,  0.0,  1.0,  0.0,
	 	t->x, t->y, t->z,  1.0
	);
}

static inline mat4_t rotate_x( scaler_t a )
{
	scaler_t s = scaler_sin( a );
	scaler_t c = scaler_cos( a );

	return MAT4(
		1.0, 0.0, 0.0, 0.0,
		0.0,   c,  -s, 0.0,
	 	0.0,   s,   c, 0.0,
	 	0.0, 0.0, 0.0, 1.0
	);
}

static inline mat4_t rotate_y( scaler_t a )
{
	scaler_t s = scaler_sin( a );
	scaler_t c = scaler_cos( a );

	return MAT4(
		  c, 0.0,   s, 0.0,
		0.0, 1.0, 0.0, 0.0,
	 	 -s, 0.0,   c, 0.0,
	 	0.0, 0.0, 0.0, 1.0
	);
}

static inline mat4_t rotate_z( scaler_t a )
{
	scaler_t s = scaler_sin( a );
	scaler_t c = scaler_cos( a );

	return MAT4(
		  c,  -s, 0.0, 0.0,
		  s,   c, 0.0, 0.0,
	 	0.0, 0.0, 1.0, 0.0,
	 	0.0, 0.0, 0.0, 1.0
	);
}

static inline mat4_t scale( const vec3_t* s )
{
	assert( s );
	return MAT4(
		s->x,  0.0,  0.0,  0.0,
		 0.0, s->y,  0.0,  0.0,
	 	 0.0,  0.0, s->z,  0.0,
	 	 0.0,  0.0,  0.0,  1.0
	);
}

static inline mat4_t uniform_scale( scaler_t s )
{
	return MAT4(
		  s, 0.0, 0.0, 0.0,
		0.0,   s, 0.0, 0.0,
	 	0.0, 0.0,   s, 0.0,
	 	0.0, 0.0, 0.0, 1.0
	);
}

static inline mat4_t shear( scaler_t s )
{
	return MAT4(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
	 	  s, 0.0, 1.0, 0.0,
	 	0.0, 0.0, 0.0, 1.0
	);
}

static inline mat4_t orientation( vec3_t* f, vec3_t* l, vec3_t* u )
{
	assert( f );
	assert( l );
	assert( u );
	vec3_normalize( f );
	vec3_normalize( l );
	vec3_normalize( u );

	return MAT4(
		l->x, l->y, l->z, 0.0,
		u->x, u->y, u->z, 0.0,
		f->x, f->y, f->z, 0.0, // TODO: Check if this should be negative forward vector
		0.0,   0.0,  0.0, 1.0
	);
}

static inline mat4_t change_handedness()
{
	// convert from our coordinate system (looking down X)
	// to OpenGL's coordinate system (looking down -Z)
	return MAT4(
		 0, 0, -1, 0,
		-1, 0,  0, 0,
		 0, 1,  0, 0,
		 0, 0,  0, 1
	);
}

#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _TRANSFORMS_H_ */
