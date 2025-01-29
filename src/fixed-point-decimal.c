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
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mathematics.h>
#include "fixed-point-decimal.h"

static inline unsigned int count_digits( int64_t num )
{
	unsigned int digits = 0;
	for(; num > 0; num /= 10 ) {
		digits += 1;
	}
	return digits;
}

fpdec_t m3d_fixed_point_decimal_from_float( float v )
{
	return (fpdec_t) {
		.val = (int64_t) floorf(v * m3d_powi(2, FLT_MANT_DIG) + 0.5f)
	};
}

fpdec_t m3d_fixed_point_decimal_from_double( double v )
{
	return (fpdec_t) {
		.val = (int64_t) floor(v * m3d_powi(2, DBL_MANT_DIG) + 0.5)
	};
}

fpdec_t m3d_fixed_point_decimal_from_long_double( long double v )
{
	return (fpdec_t) {
		.val = (int64_t) floorl(v * m3d_powi(2, LDBL_MANT_DIG) + 0.5)
	};
}

fpdec_t m3d_fixed_point_decimal_create( int64_t significand, int fraction )
{
	int z = m3d_powi(10, M3D_FIXED_POINT_DECIMAL_SCALE);
	int fraction_digits = count_digits(fraction);

	if( fraction_digits > M3D_FIXED_POINT_DECIMAL_SCALE )
	{
		// TODO
	}

	else if( fraction_digits < M3D_FIXED_POINT_DECIMAL_SCALE )
	{
		fraction *= m3d_powi(10, M3D_FIXED_POINT_DECIMAL_SCALE - fraction_digits);
	}

	return (fpdec_t) {
		.val = significand * z + fraction
	};
}

fpdec_t m3d_fixed_point_decimal_add( fpdec_t a, fpdec_t b, bool* result )
{
	if( result )
	{
		if(( a.val ^ b.val) < 0 ) *result = true; // opposite signs can't overflow
		else if( a.val > 0 )      *result = b.val > INT64_MAX - a.val; // overflow
		else                      *result = b.val < INT64_MAX - a.val; // overflow
	}

	return (fpdec_t) {
		.val = a.val + b.val
	};
}

fpdec_t m3d_fixed_point_decimal_multiply( fpdec_t a, fpdec_t b, bool* result )
{
	if( result )
	{
		*result  = b.val != 0 && a.val < (INT64_MAX / b.val); // overflow
	}

	return (fpdec_t) {
		.val = a.val * b.val / m3d_powi(10, M3D_FIXED_POINT_DECIMAL_SCALE)
	};
}

fpdec_t m3d_fixed_point_decimal_divide( fpdec_t a, fpdec_t b, bool* result )
{
	if( result )
	{
		*result  = b.val != 0;
	}

	return (fpdec_t) {
		.val = (a.val / b.val) * m3d_powi(10, M3D_FIXED_POINT_DECIMAL_SCALE)
	};
}

bool m3d_fixed_point_decimal_string( char* string, size_t size, fpdec_t n )
{
	unsigned int digits = count_digits( n.val );
	int64_t num = n.val;

	if( digits <= M3D_FIXED_POINT_DECIMAL_SCALE)
	{
		digits += 1;
	}

	if( digits > size )
	{
		return false;
	}

	for( int idx = digits; idx >= 0; idx-- )
	{
		if( idx == (digits - M3D_FIXED_POINT_DECIMAL_SCALE) )
		{
			if( idx == 0 ) {
				string[ idx ] = '0';
				idx += 1;
			}
			string[ idx ] = '.';
		}
		else
		{
			int digit = num % 10;
			string[ idx ] = '0' + digit;
			num /= 10;
		}
	}

	string[ digits + 1 ] = '\0';
    return true;
}
