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
#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_
#include <math.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#if defined(SIMPLEGL_MATH_USE_LONG_DOUBLE)
	#ifndef SCALAR_T
	#define SCALAR_T 
	typedef long double scaler_t;
	#endif
	#ifndef SCALAR_EPSILON
	#define SCALAR_EPSILON LDBL_EPSILON
	#endif
#elif defined(SIMPLEGL_MATH_USE_DOUBLE)
	#ifndef SCALAR_T
	#define SCALAR_T 
	typedef double scaler_t;
	#endif
	#ifndef SCALAR_EPSILON
	#define SCALAR_EPSILON DBL_EPSILON
	#endif
#else /* default: use float */
	#ifndef SCALAR_T
	#define SCALAR_T 
	typedef float scaler_t;
	#endif
	#ifndef SCALAR_EPSILON
	#define SCALAR_EPSILON FLT_EPSILON
	#endif
#endif

#define PI                    (M_PI)
#define TWO_PI                (2*M_PI)
#define RADIANS_PER_DEGREE    (M_PI / 180.0)
#define DEGREES_PER_RANDIAN   (180.0 / M_PI)

#define to_radians( degrees )  ((degrees)*RADIANS_PER_DEGREE)
#define to_degrees( radians )  ((radians)/RADIANS_PER_DEGREE)

#define integer_max( x, y )    ((x) ^ (((x) ^ (y)) & -((x) < (y))))
#define integer_min( x, y )    ((y) ^ (((x) ^ (y)) & -((x) < (y))))

float        uniformf           ( void ); /* [0.0f, 1.0f] */
double       uniformd           ( void ); /* [0.0, 1.0] */
long double  uniformld          ( void ); /* [0.0, 1.0] */
int          uniform_rangei     ( int min, int max ); /* [min. max] */
long         uniform_rangel     ( long min, long max ); /* [min. max] */
float        uniform_rangef     ( float min, float max ); /* [min. max] */
double       uniform_ranged     ( double min, double max ); /* [min. max] */
float        uniform_unitf      ( void ); /* [-1.0f, 1.0f]; */
double       uniform_unitd      ( void ); /* [-1.0, 1.0]; */
long double  uniform_unitld     ( void ); /* [-1.0, 1.0]; */
float        guassianf          ( float mean, float stddev );
double       guassiand          ( double mean, double stddev );
long double  guassianld         ( long double mean, long double stddev );
int          maxi               ( int x, int y );
long         maxl               ( long x, long y );
float        maxf               ( float x, float y );
double       maxd               ( double x, double y );
long double  maxld              ( long double x, long double y );
int          mini               ( int x, int y );
long         minl               ( long x, long y );
float        minf               ( float x, float y );
double       mind               ( double x, double y );
long double  minld              ( long double x, long double y );
int          clampi             ( int value, int min, int max );
long         clampl             ( int value, int min, int max );
float        clampf             ( float value, float min, float max );
double       clampd             ( double value, double min, double max );
long double  clampld            ( long double value, long double min, long double max );
bool         is_power_of_2      ( int x );
int          next_power_of_2    ( int v );
float        fast_inverse_sqrt  ( float number );


#define linear_interpolation( a, x0, x1 )              ((x0) + (a) * ((x1) - (x0)))
#define lerp                                           linear_interpolation
#define bilear_interpolation( a, b, x0, x1, x2, x3 )   (lerp( b, lerp( a, x0, x1 ), lerp( a, x2, x3 ) ))
#define bilerp                                         bilear_interpolation



#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
/* 
 * C11 generic functions
 */
#define uniform_range(min_num, max_num) _Generic( (min_num), \
	int:     uniform_rangei, \
	long:    uniform_rangel, \
	float:   uniform_rangef, \
	double:  uniform_ranged, \
	default: uniform_rangef \
);
#define uniform(type) _Generic( (type), \
	float:   uniformf, \
	double:  uniformd, \
	default: uniformf \
);
#define guassian(mean, stddev) _Generic( (mean), \
	float:   guassianf, \
	double:  guassiand, \
	default: guassianf \
);
#endif

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat2.h"
#include "mat3.h"
#include "mat4.h"

#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _MATHEMATICS_H_ */
