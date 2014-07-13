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
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "mathematics.h"
#include "quat.h"

quat_t quat_from_mat3( const mat3_t* m )
{
	quat_t q;

	scaler_t trace = m->m[0] + m->m[4] + m->m[8]; /* add the diagonal values */

	if( trace > 0.0f )
	{
		scaler_t s = 0.5 / scaler_sqrt( trace );

		q.w = 0.25 / s;
		q.x = (m->m[7] - m->m[5]) * s;
		q.y = (m->m[2] - m->m[6]) * s;
		q.z = (m->m[3] - m->m[1]) * s;
	}
	else
	{
		scaler_t max_diagonal_elem = scaler_max( m->m[0], scaler_max( m->m[4], m->m[8] ) );

		if( scaler_abs(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		{
			scaler_t s = scaler_sqrt( 1.0 + m->m[0] - m->m[4] - m->m[8] ) * 2.0;

			q.x = 0.5 / s;
			q.y = (m->m[1] + m->m[3]) / s;
			q.z = (m->m[2] + m->m[6]) / s;
			q.w = (m->m[5] + m->m[7]) / s;
		}
		else if( scaler_abs(m->m[4] - max_diagonal_elem) < SCALAR_EPSILON )
		{
			scaler_t s = scaler_sqrt( 1.0 + m->m[4] - m->m[0] - m->m[8] ) * 2.0;

			q.x = (m->m[1] + m->m[3]) / s;
			q.y = 0.5 / s;
			q.z = (m->m[5] + m->m[7]) / s;
			q.w = (m->m[2] + m->m[6]) / s;
		}
		else
		{
			scaler_t s = scaler_sqrt( 1.0 + m->m[8] - m->m[0] - m->m[4] ) * 2.0;

			q.x = (m->m[2] + m->m[6]) / s;
			q.y = (m->m[5] + m->m[7]) / s;
			q.x = 0.5 / s;
			q.w = (m->m[1] + m->m[3]) / s;
		}
	}

	return q;
}

quat_t quat_from_mat4( const mat4_t* m )
{
	quat_t q;

	scaler_t trace = m->m[0] + m->m[5] + m->m[10] + 1; /* add the diagonal values */

	if( trace > 0.0f )
	{
		scaler_t s = 0.5 / scaler_sqrt( trace );

		q.w = 0.25 / s;
		q.x = (m->m[9] - m->m[6]) * s;
		q.y = (m->m[2] - m->m[8]) * s;
		q.z = (m->m[4] - m->m[1]) * s;
	}
	else
	{
		scaler_t max_diagonal_elem = scaler_max( m->m[0], scaler_max( m->m[5], m->m[10] ) );

		if( scaler_abs(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		{
			scaler_t s = scaler_sqrt( 1.0 + m->m[0] - m->m[5] - m->m[10] ) * 2.0;

			q.x = 0.5 / s;
			q.y = (m->m[1] + m->m[4]) / s;
			q.z = (m->m[2] + m->m[8]) / s;
			q.w = (m->m[6] + m->m[9]) / s;
		}
		else if( scaler_abs(m->m[5] - max_diagonal_elem) < SCALAR_EPSILON )
		{
			scaler_t s = scaler_sqrt( 1.0 + m->m[5] - m->m[0] - m->m[10] ) * 2.0;

			q.x = (m->m[1] + m->m[4]) / s;
			q.y = 0.5 / s;
			q.z = (m->m[6] + m->m[9]) / s;
			q.w = (m->m[2] + m->m[8]) / s;
		}
		else
		{
			scaler_t s = scaler_sqrt( 1.0 + m->m[10] - m->m[0] - m->m[5] ) * 2.0;

			q.x = (m->m[2] + m->m[8]) / s;
			q.y = (m->m[6] + m->m[9]) / s;
			q.x = 0.5 / s;
			q.w = (m->m[1] + m->m[4]) / s;
		}
	}

	return q;
}


quat_t quat_slerp( const quat_t* q, const quat_t* r, scaler_t t )
{
	const scaler_t theta     = scaler_acos( vec4_dot_product( q, r ) );
	const scaler_t sin_theta = scaler_sin( theta );
	const scaler_t alpha     = scaler_sin( theta * (1 - t) ) / sin_theta;
	const scaler_t beta      = scaler_sin( theta * t ) / sin_theta;

	return vec4_add( &QUAT(alpha * q->x,  alpha * q->y,  alpha * q->z,  alpha * q->w),
	                 &QUAT(beta * r->x, beta * r->y, beta * r->z, beta * r->w) );
}


