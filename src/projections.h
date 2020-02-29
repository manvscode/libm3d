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
#ifndef _PROJECTIONS_H_
#define _PROJECTIONS_H_
#include "mathematics.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"
#ifdef __cplusplus
extern "C" {
#endif


static inline mat4_t m3d_projection_orthographic( scaler_t left, scaler_t right, scaler_t bottom, scaler_t top, scaler_t near, scaler_t far )
{
	return MAT4(
		2.0 / (right - left)          , 0.0                           ,  0.0                      , 0.0,
		0.0                           , 2.0 / (top - bottom)          ,  0.0                      , 0.0,
		0.0                           , 0.0                           , -2.0 / (far - near)       , 0.0,
		-(right + left)/(right - left), -(top + bottom)/(top - bottom), -(far + near)/(far - near), 1.0
	);
}

static inline mat4_t m3d_projection_frustum( scaler_t left, scaler_t right, scaler_t bottom, scaler_t top, scaler_t near, scaler_t far )
{
	scaler_t A = 2.0 * near / (right - left);
	scaler_t B = (right + left) / (right - left);
	scaler_t C = 2.0 * near / (top - bottom);
	scaler_t D = (top + bottom) / (top - bottom);
	scaler_t E = -(far + near) / (far - near);
	scaler_t F = -(2.0 * far * near) / (far - near);

	return MAT4(
		  A,  0.0,    B,  0.0,
		0.0,    C,    D,  0.0,
		0.0,  0.0,    E,    F,
		0.0,  0.0, -1.0,  0.0
	);
}

static inline mat4_t m3d_projection_perspective( scaler_t fov /* in radians */, scaler_t aspect, scaler_t near, scaler_t far )
{
	scaler_t A = 1.0 / tan(fov * 0.5);
	scaler_t B = -far / (far - near);
	scaler_t C = -(far * near)/ (far - near);

	return MAT4(
	    A/aspect,  0.0,  0.0,  0.0,
	         0.0,    A,  0.0,  0.0,
	         0.0,  0.0,    B, -1.0,
	         0.0,  0.0,    C,  0.0
	);
}

#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _PROJECTIONS_H_ */
