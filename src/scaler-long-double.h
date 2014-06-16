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
#ifndef _SCALER_H_
#define _SCALER_H_

#ifndef SCALAR_T
#define SCALAR_T
typedef long double scaler_t;
#endif
#ifndef SCALAR_EPSILON
#define SCALAR_EPSILON LDBL_EPSILON
#endif

static inline bool scaler_compare( scaler_t a, scaler_t b )
{
	return fabsl( a - b ) < SCALAR_EPSILON;
}

static inline scaler_t scaler_max( scaler_t a, scaler_t b )
{
	return maxld( a, b );
}

static inline scaler_t scaler_min( scaler_t a, scaler_t b )
{
	return minld( a, b );
}

static inline scaler_t scaler_abs( scaler_t s )
{
	return fabsl( s );
}

static inline scaler_t scaler_sqrt( scaler_t s )
{
	return sqrtl( s );
}

static inline scaler_t scaler_sin( scaler_t a )
{
	return sinl( a );
}

static inline scaler_t scaler_asin( scaler_t a )
{
	return asinl( a );
}

static inline scaler_t scaler_cos( scaler_t a )
{
	return cosl( a );
}

static inline scaler_t scaler_acos( scaler_t a )
{
	return acosl( a );
}

static inline char* scaler_type_string( void )
{
	return "long double";
}

#endif /* _SCALER_H_ */
