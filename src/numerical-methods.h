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
#include <stdbool.h>
#include <float.h>
#include <math.h>


/* Find the root of a function f(x) within an interval of [a, b] with a
 * tolerance of epsilon. A solution should converge within a certain number
 * of iterations, otherwise, a solution will not be found. Returns true
 * when a solution is found and false otherwise.
 */
bool bissection_method( double a, double b, double epsilon, size_t iterations, double (*f)(double x), double* root );
bool bissection_method_max_precision( double a, double b, double (*f)(double x), double* root );

/* Find the root of a function f(x). Given f(x) = 0, transform f(x) to form a
 * fixed point equation of the form x = g(x). If |g'(x)| < 1, then g(x) will
 * converge to a solution. If it a solution is found, the function returns
 * true and false otherwise. This method is equivalent to the Newton-Ralphson
 * method when g(x) = x - f(x)/f'(x). If the derivative of f is known then
 * g(x) should be constructed in this form.
 *
 * Examples:
 *
 *  Given f(x) = sin(2x)
 *
 *      0 = sin(2x) <==> 0 + x = sin(2x) + x <==> x = sin(2x) + x
 *
 *  Given f(x) = x^3 + 4x^2 - 10
 *
 *      0 = x^3 + 4x^2 - 10 <==> 10 = x^2 * (x + 4) <==> sqrt(10 / (x + 4)) = x
 */
bool fixed_point_iteration( double estimate, double epsilon, size_t iterations, double (*g)(double x), double* root );
bool fixed_point_iteration_max_precision( double estimate, double (*g)(double x), double* root );

/* Find the root of a function f(x) given two initial estimates a and b. This
 * method is similar to Newton-Ralphson method but does not require knowing f'(x).
 * This method is better than the bissection_method(). Returns true when a
 * solution is found and false otherwise.
 */
bool secant_method( double a, double b, double epsilon, size_t iterations, double (*f)(double x), double* root );

/*
 * Given a list of (x,y) coordinates, least_squares_linear() will find the least
 * sqaures linear equation y = mx + b that has the minimal error.
 */
void   least_squares_linear       ( const double x[], const double y[], size_t count, double* m, double* b );
double least_squares_linear_error ( const double x[], const double y[], size_t count, double m, double b );

/*
 * Given a list of (x,y) coordinates, least_squares_quadratic() will find the least
 * sqaures quadratic equation y = ax^2 + bx + c that has the minimal error.
 */
void   least_squares_quadratic       ( const double x[], const double y[], size_t count, double* a, double* b, double* c );
double least_squares_quadratic_error ( const double x[], const double y[], size_t count, double a, double b, double c );


/*
 * Write out the coordinates in a tabular layout.
 */
void table_dump( FILE* stream, const double x[], const double y[], size_t count, const char* label_x, const char* label_y );




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
