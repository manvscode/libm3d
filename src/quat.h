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
#ifdef __restrict
#undef __restrict
#define __restrict restrict
#endif
#ifdef __inline
#undef __inline
#define __inline inline
#endif
#else
#define bool int
#define true 1
#define false 0
#ifdef __restrict
#undef __restrict
#define __restrict
#endif
#ifdef __inline
#undef __inline
#define __inline
#endif
#endif
#ifdef __cplusplus
extern "C" {
#endif

#if defined(QUAT_USE_LONG_DOUBLE)
	#ifndef SCALAR_T
	#define SCALAR_T 
	typedef long double scaler_t;
	#endif
	#ifndef SCALAR_EPSILON
	#define SCALAR_EPSILON LDBL_EPSILON
	#endif
#elif defined(QUAT_USE_DOUBLE)
	#ifndef SCALAR_T
	#define SCALAR_T 
	typedef double scaler_t;
	#endif
	#ifndef SCALAR_EPSILON
	#define SCALAR_EPSILON DBL_EPSILON
	#endif
#else /* default: use float */
	#ifndef SCALAR_T
	#define SCALAR_T 
	typedef float scaler_t;
	#endif
	#ifndef SCALAR_EPSILON
	#define SCALAR_EPSILON FLT_EPSILON
	#endif
#endif

#include "vec4.h"

/*
 * Quaternion
 */
typedef vec4_t quat_t;


quat_t      quat_from_axis3_angle        ( const vec3_t* axis, scaler_t angle );
quat_t      quat_from_axis4_angle        ( const vec4_t* axis, scaler_t angle );
quat_t      quat_from_vec3               ( const vec3_t* v );
quat_t      quat_from_vec4               ( const vec4_t* v );
quat_t      quat_from_mat3               ( const mat3_t* m );
quat_t      quat_from_mat4               ( const mat4_t* m );
quat_t      quat_add                     ( const quat_t* a, const quat_t* b );
quat_t      quat_multiply                ( const quat_t* a, const quat_t* b );
void        quat_scale                   ( quat_t* a, scaler_t s );
scaler_t    quat_dot_product             ( const quat_t* a, const quat_t* b ); /* 1 := similiar rotations */
quat_t      quat_slerp                   ( const quat_t* a, const quat_t* b, scaler_t t );
vec3_t      quat_rotate3                 ( const quat_t* q, const vec3_t* v );
vec4_t      quat_rotate4                 ( const quat_t* q, const vec4_t* v );
scaler_t    quat_magnitude               ( const quat_t* v );
quat_t      quat_conjugate               ( const quat_t* q );
void        quat_normalize               ( quat_t* q );
mat3_t      quat_to_mat3                 ( const quat_t* q );
mat4_t      quat_to_mat4                 ( const quat_t* q );
scaler_t    quat_angle                   ( const quat_t* q );
void        quat_extract_axis3_and_angle ( const quat_t* q, vec3_t* axis, scaler_t* angle );
void        quat_extract_axis4_and_angle ( const quat_t* q, vec4_t* axis, scaler_t* angle );

#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _QUAT_H_ */
