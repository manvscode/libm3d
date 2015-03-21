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
#ifndef _NUMERICAL_METHODS_H_
#define _NUMERICAL_METHODS_H_
#include <stddef.h>
#include <math.h>


/*
 * Given a list of (x,y) coordinates, least_squares_linear() will find the least
 * sqaures linear equation y = mx + b that has the minimal error.
 */
void   least_squares_linear( const double x[], const double y[], size_t count, double* m, double* b );
double least_squares_linear_error( const double x[], const double y[], size_t count, double m, double b );

/*
 * Given a list of (x,y) coordinates, least_squares_quadratic() will find the least
 * sqaures quadratic equation y = ax^2 + bx + c that has the minimal error.
 */
void   least_squares_quadratic( const double x[], const double y[], size_t count, double* a, double* b, double* c );
double least_squares_quadratic_error( const double x[], const double y[], size_t count, double a, double b, double c );


void   table_dump( FILE* stream, const double x[], const double y[], size_t count, const char* label_x, const char* label_y );

static inline float absolute_errorf( float actual, float measured )
{
	return fabsf( actual - measured );
}

static inline double absolute_errord( double actual, double measured )
{
	return fabs( actual - measured );
}

static inline long double absolute_errorld( long double actual, long double measured )
{
	return fabsl( actual - measured );
}

static inline float relative_errorf( float actual, float measured )
{
	return fabsf( actual - measured ) / fabsf(actual);
}

static inline double relative_errord( double actual, double measured )
{
	return fabs( actual - measured ) / fabs(actual);
}

static inline long double relative_errorld( long double actual, long double measured )
{
	return fabsl( actual - measured ) / fabsl(actual);
}




#endif /* _NUMERICAL_METHODS_H_ */
