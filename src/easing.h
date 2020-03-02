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
#ifndef _EASING_H_
#define _EASING_H_
#include <stdlib.h>
#include <math.h>
#include "mathematics.h"

static inline scaler_t m3d_easing_hermite( scaler_t start, scaler_t end, scaler_t value )
{
	return m3d_lerp( value * value * (3.0 - 2.0 * value), start, end );
}

static inline scaler_t m3d_easing_sinerp( scaler_t start, scaler_t end, scaler_t value )
{
	return m3d_lerp( sinf(value * M3D_PI * 0.5), start, end );
}

static inline scaler_t m3d_easing_coserp( scaler_t start, scaler_t end, scaler_t value )
{
	return m3d_lerp( 1.0 - cosf(value * M3D_PI * 0.5), start, end );
}

/* Overshoots and then bounces at the end */
static inline scaler_t m3d_easing_berp( scaler_t start, scaler_t end, scaler_t value )
{
	value = m3d_clampf( value, 0.0, 1.0 );
	value = ( sinf(value * M3D_PI * (0.2 + 2.5 * value * value * value)) * powf(1.0 - value, 2.2) + value) * (1.0 + (1.2 * (1.0 - value)));
	return start + (end - start) * value;
}

static inline scaler_t m3d_easing_smooth_step( scaler_t x, scaler_t min, scaler_t max )
{
	x = m3d_clampf( x, min, max );
	scaler_t v1 = (x - min) / (max - min);
	scaler_t v2 = (x - min) / (max - min);
	return -2*v1 * v1 *v1 + 3*v2 * v2;
}

scaler_t m3d_easing_bounce( scaler_t x )
{
	return fabs( sinf(6.28*(x+1.0)*(x+1.0)) * (1.0-x) );
}

static inline scaler_t m3d_easing_linear( scaler_t step )
{
	return step;
}

static inline scaler_t m3d_easing_in_quadratic( scaler_t step, scaler_t acceleration )
{
	return m3d_lerp( fabs(acceleration), step, step * step );
}

static inline scaler_t m3d_easing_out_quadratic( scaler_t step, scaler_t acceleration )
{
	return m3d_lerp( fabs(acceleration), step, (1.0 - step) * (1.0 - step) );
}

static inline scaler_t m3d_easing_inout_quadratic( scaler_t step, scaler_t acceleration )
{
	return m3d_lerp( fabs(acceleration), step, (1.0 - step) * (1.0 - step) );
}

#endif /* _EASING_H_ */
