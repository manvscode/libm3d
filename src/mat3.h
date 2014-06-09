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
#ifndef _MAT3_H_
#define _MAT3_H_
#include <float.h>
#include <limits.h>
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <stdbool.h>
#else
#error "Need a C99 compiler."
#endif
#include "mathematics.h"
#include "vec3.h"
#ifdef __cplusplus
extern "C" {
#endif



/*
 * Three Dimensional Matrices
 */
typedef struct mat3 {
    scaler_t m[ 9 ];
} mat3_t;

extern const mat3_t MAT3_IDENTITY;
extern const mat3_t MAT3_ZERO;

/* |a d g|
 * |b e h|
 * |c f i|
 */
#define MAT3(a,b,c,d,e,f,g,h,i)  ((mat3_t){ .m = { (a), (b), (c), (d), (e), (f), (g), (h), (i) } })

void          mat3_identity    ( mat3_t* m );
void          mat3_zero        ( mat3_t* m );
scaler_t      mat3_determinant ( const mat3_t* m );
mat3_t        mat3_mult_matrix ( const mat3_t* __restrict a, const mat3_t* __restrict b );
vec3_t        mat3_mult_vector ( const mat3_t* __restrict m, const vec3_t* __restrict v );
bool          mat3_invert      ( mat3_t* m );
void          mat3_transpose   ( mat3_t* m );
mat3_t        mat3_cofactor    ( mat3_t* m );
void          mat3_adjoint     ( mat3_t* m );
const char*   mat3_to_string   ( const mat3_t* m );

#define mat3_x_vector( p_m )   ((vec3_t*) &(p_m)->m[0])
#define mat3_y_vector( p_m )   ((vec3_t*) &(p_m)->m[3])
#define mat3_z_vector( p_m )   ((vec3_t*) &(p_m)->m[6])


#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _MAT3_H_ */
