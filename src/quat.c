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
		#if defined(LIB3DMATH_USE_LONG_DOUBLE)
		scaler_t s = 0.5 / sqrtl( trace );
		#elif defined(LIB3DMATH_USE_DOUBLE)
		scaler_t s = 0.5 / sqrt( trace );
		#else
		scaler_t s = 0.5 / sqrtf( trace );
		#endif

		q.w = 0.25 / s;
		q.x = (m->m[7] - m->m[5]) * s;
		q.y = (m->m[2] - m->m[6]) * s;
		q.z = (m->m[3] - m->m[1]) * s;
	}
	else
	{
		#if defined(LIB3DMATH_USE_LONG_DOUBLE)
		scaler_t max_diagonal_elem = maxld( m->m[0], maxld( m->m[4], m->m[8] ) );
		#elif defined(LIB3DMATH_USE_DOUBLE)
		scaler_t max_diagonal_elem = maxd( m->m[0], maxd( m->m[4], m->m[8] ) );
		#else
		scaler_t max_diagonal_elem = maxf( m->m[0], maxf( m->m[4], m->m[8] ) );
		#endif

		#if defined(LIB3DMATH_USE_LONG_DOUBLE)
		if( fabsl(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#elif defined(LIB3DMATH_USE_DOUBLE)
		if( fabs(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#else
		if( fabsf(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#endif
		{
			#if defined(LIB3DMATH_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[0] - m->m[4] - m->m[8] ) * 2.0;
			#elif defined(LIB3DMATH_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[0] - m->m[4] - m->m[8] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[0] - m->m[4] - m->m[8] ) * 2.0;
			#endif

			q.x = 0.5 / s;
			q.y = (m->m[1] + m->m[3]) / s;
			q.z = (m->m[2] + m->m[6]) / s;
			q.w = (m->m[5] + m->m[7]) / s;
		}
		#if defined(LIB3DMATH_USE_LONG_DOUBLE)
		else if( fabsl(m->m[4] - max_diagonal_elem) < SCALAR_EPSILON )
		#elif defined(LIB3DMATH_USE_DOUBLE)
		else if( fabs(m->m[4] - max_diagonal_elem) < SCALAR_EPSILON )
		#else
		else if( fabsf(m->m[4] - max_diagonal_elem) < SCALAR_EPSILON )
		#endif
		{
			#if defined(LIB3DMATH_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[4] - m->m[0] - m->m[8] ) * 2.0;
			#elif defined(LIB3DMATH_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[4] - m->m[0] - m->m[8] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[4] - m->m[0] - m->m[8] ) * 2.0;
			#endif

			q.x = (m->m[1] + m->m[3]) / s;
			q.y = 0.5 / s;
			q.z = (m->m[5] + m->m[7]) / s;
			q.w = (m->m[2] + m->m[6]) / s;
		}
		else
		{
			#if defined(LIB3DMATH_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[8] - m->m[0] - m->m[4] ) * 2.0;
			#elif defined(LIB3DMATH_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[8] - m->m[0] - m->m[4] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[8] - m->m[0] - m->m[4] ) * 2.0;
			#endif

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
		#if defined(LIB3DMATH_USE_LONG_DOUBLE)
		scaler_t s = 0.5 / sqrtl( trace );
		#elif defined(LIB3DMATH_USE_DOUBLE)
		scaler_t s = 0.5 / sqrt( trace );
		#else
		scaler_t s = 0.5 / sqrtf( trace );
		#endif

		q.w = 0.25 / s;
		q.x = (m->m[9] - m->m[6]) * s;
		q.y = (m->m[2] - m->m[8]) * s;
		q.z = (m->m[4] - m->m[1]) * s;
	}
	else
	{
		#if defined(LIB3DMATH_USE_LONG_DOUBLE)
		scaler_t max_diagonal_elem = maxld( m->m[0], maxld( m->m[5], m->m[10] ) );
		#elif defined(LIB3DMATH_USE_DOUBLE)
		scaler_t max_diagonal_elem = maxd( m->m[0], maxd( m->m[5], m->m[10] ) );
		#else
		scaler_t max_diagonal_elem = maxf( m->m[0], maxf( m->m[5], m->m[10] ) );
		#endif

		#if defined(LIB3DMATH_USE_LONG_DOUBLE)
		if( fabsl(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#elif defined(LIB3DMATH_USE_DOUBLE)
		if( fabs(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#else
		if( fabsf(m->m[0] - max_diagonal_elem) < SCALAR_EPSILON )
		#endif
		{
			#if defined(LIB3DMATH_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[0] - m->m[5] - m->m[10] ) * 2.0;
			#elif defined(LIB3DMATH_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[0] - m->m[5] - m->m[10] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[0] - m->m[5] - m->m[10] ) * 2.0;
			#endif

			q.x = 0.5 / s;
			q.y = (m->m[1] + m->m[4]) / s;
			q.z = (m->m[2] + m->m[8]) / s;
			q.w = (m->m[6] + m->m[9]) / s;
		}
		#if defined(LIB3DMATH_USE_LONG_DOUBLE)
		else if( fabsl(m->m[5] - max_diagonal_elem) < SCALAR_EPSILON )
		#elif defined(LIB3DMATH_USE_DOUBLE)
		else if( fabs(m->m[5] - max_diagonal_elem) < SCALAR_EPSILON )
		#else
		else if( fabsf(m->m[5] - max_diagonal_elem) < SCALAR_EPSILON )
		#endif
		{
			#if defined(LIB3DMATH_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[5] - m->m[0] - m->m[10] ) * 2.0;
			#elif defined(LIB3DMATH_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[5] - m->m[0] - m->m[10] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[5] - m->m[0] - m->m[10] ) * 2.0;
			#endif

			q.x = (m->m[1] + m->m[4]) / s;
			q.y = 0.5 / s;
			q.z = (m->m[6] + m->m[9]) / s;
			q.w = (m->m[2] + m->m[8]) / s;
		}
		else
		{
			#if defined(LIB3DMATH_USE_LONG_DOUBLE)
			scaler_t s = sqrtl( 1.0 + m->m[10] - m->m[0] - m->m[5] ) * 2.0;
			#elif defined(LIB3DMATH_USE_DOUBLE)
			scaler_t s = sqrt( 1.0 + m->m[10] - m->m[0] - m->m[5] ) * 2.0;
			#else
			scaler_t s = sqrtf( 1.0 + m->m[10] - m->m[0] - m->m[5] ) * 2.0;
			#endif

			q.x = (m->m[2] + m->m[8]) / s;
			q.y = (m->m[6] + m->m[9]) / s;
			q.x = 0.5 / s;
			q.w = (m->m[1] + m->m[4]) / s;
		}
	}

	return q;
}


quat_t quat_slerp( const quat_t* a, const quat_t* b, scaler_t t )
{
	scaler_t dot = a->w * b->w + a->x * b->x + a->y * b->y + a->z * b->z;

	if( fabs(dot) > 1.0f )
	{
		return *a;
	}

	//scaler_t sin_of_omega = sqrt( 1.0f - dot * dot );

	quat_t result;

	// TODO: Implement this!
	assert( false );

	return result;
}


