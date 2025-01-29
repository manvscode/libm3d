/* Copyright (C) 2013-2025 by Joseph A. Marrero, http://joemarrero.com/
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
#ifndef _MAT4_H_
#define _MAT4_H_
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
#ifdef __cplusplus
extern "C" {
#endif


/*
 * Four Dimensional Matrices
 */
typedef struct mat4 {
    scaler_t m[ 16 ];
} mat4_t;

extern const mat4_t MAT4_IDENTITY;
extern const mat4_t MAT4_ZERO;

/* |A E I M|
 * |B F J N|
 * |C G K O|
 * |D H L P|
 */
#define MAT4(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)  ((mat4_t){ .m = { (A), (B), (C), (D), (E), (F), (G), (H), (I), (J), (K), (L), (M), (N), (O), (P) } })

void        mat4_identity         ( mat4_t* m );
void        mat4_zero             ( mat4_t* m );
scaler_t    mat4_determinant      ( const mat4_t* m );
mat4_t      mat4_mult_matrix      ( const mat4_t* restrict a, const mat4_t* restrict b );
vec4_t      mat4_mult_vector      ( const mat4_t* restrict m, const vec4_t* restrict v );
bool        mat4_invert           ( mat4_t* m );
void        mat4_transpose        ( mat4_t* m );
mat4_t      mat4_cofactor         ( const mat4_t* m );
void        mat4_adjoint          ( mat4_t* m );
mat4_t      mat4_from_axis3_angle ( const vec3_t* axis, scaler_t angle );
const char* mat4_to_string        ( const mat4_t* m );

#define mat4_x_vector( p_m )   ((vec4_t*) &(p_m)->m[0])
#define mat4_y_vector( p_m )   ((vec4_t*) &(p_m)->m[4])
#define mat4_z_vector( p_m )   ((vec4_t*) &(p_m)->m[8])
#define mat4_w_vector( p_m )   ((vec4_t*) &(p_m)->m[12])


#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _MAT4_H_ */
