/* Copyright (C) 2013-2019 by Joseph A. Marrero, http://www.manvscode.com/
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
#ifndef _FIXED_POINT_DECIMAL_H_
#define _FIXED_POINT_DECIMAL_H_

#ifndef M3D_FIXED_POINT_DECIMAL_SCALE
# define M3D_FIXED_POINT_DECIMAL_SCALE      5
#endif

#include <stdbool.h>

typedef struct fixed_point_decimal {
	int64_t val;
	//uint16_t scale;
} fpdec_t;

fpdec_t m3d_fixed_point_decimal_from_float( float v );
fpdec_t m3d_fixed_point_decimal_from_double( double v );
fpdec_t m3d_fixed_point_decimal_from_long_double( long double v );
fpdec_t m3d_fixed_point_decimal_create( int64_t significand, int fraction );

fpdec_t m3d_fixed_point_decimal_add( fpdec_t a, fpdec_t b, bool* result );
fpdec_t m3d_fixed_point_decimal_multiply( fpdec_t a, fpdec_t b, bool* result );
fpdec_t m3d_fixed_point_decimal_divide( fpdec_t a, fpdec_t b, bool* result );

bool m3d_fixed_point_decimal_string( char* string, size_t size, fpdec_t n );

#endif /* _FIXED_POINT_DECIMAL_H_ */
