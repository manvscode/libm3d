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
#ifndef _MAT2_H_
#define _MAT2_H_
#include <float.h>
#include <limits.h>
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <stdbool.h>
#else
#error "Need a C99 compiler."
#endif
#include "mathematics.h"
#include "vec2.h"
#ifdef __cplusplus
extern "C" {
#endif


/*
 * Two Dimensional Matrices
 */
typedef struct mat2 {
    scaler_t m[ 4 ];
} mat2_t;

extern const mat2_t MAT2_IDENTITY;
extern const mat2_t MAT2_ZERO;

/* |a c|
 * |b d|
 */
#define MAT2(a,b,c,d)  ((mat2_t){ .m = { (a), (b), (c), (d) } })

void        mat2_initialize  ( mat2_t* m, scaler_t a, scaler_t b, scaler_t c, scaler_t d );
void        mat2_identity    ( mat2_t* m );
void        mat2_zero        ( mat2_t* m );
scaler_t    mat2_determinant ( const mat2_t* m );
mat2_t      mat2_mult_matrix ( const mat2_t* restrict a, const mat2_t* restrict b );
vec2_t      mat2_mult_vector ( const mat2_t* restrict m, const vec2_t* restrict v );
bool        mat2_invert      ( mat2_t* m );
void        mat2_transpose   ( mat2_t* m );
const char* mat2_to_string   ( const mat2_t* m );

#define mat2_x_vector( p_m )   ((vec2_t*) &(p_m)->m[0])
#define mat2_y_vector( p_m )   ((vec2_t*) &(p_m)->m[2])


#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _MAT2_H_ */
