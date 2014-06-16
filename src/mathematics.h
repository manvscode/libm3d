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
#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include "lib3dmath-config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HALF_PI               (M_PI_2)
#define PI                    (M_PI)
#define TWO_PI                (2*M_PI)
#define RADIANS_PER_DEGREE    (M_PI / 180.0)
#define DEGREES_PER_RANDIAN   (180.0 / M_PI)
#define EASING_EPSILON        (0.0001)

#define to_radians( degrees )  ((degrees)*RADIANS_PER_DEGREE)
#define to_degrees( radians )  ((radians)*DEGREES_PER_RANDIAN)

#define integer_max( x, y )    ((x) ^ (((x) ^ (y)) & -((x) < (y))))
#define integer_min( x, y )    ((y) ^ (((x) ^ (y)) & -((x) < (y))))

float         uniformf           ( void ); /* [0.0f, 1.0f] */
double        uniformd           ( void ); /* [0.0, 1.0] */
long double   uniformld          ( void ); /* [0.0, 1.0] */
int           uniform_rangei     ( int min, int max ); /* [min. max] */
long          uniform_rangel     ( long min, long max ); /* [min. max] */
float         uniform_rangef     ( float min, float max ); /* [min. max] */
double        uniform_ranged     ( double min, double max ); /* [min. max] */
float         uniform_unitf      ( void ); /* [-1.0f, 1.0f]; */
double        uniform_unitd      ( void ); /* [-1.0, 1.0]; */
long double   uniform_unitld     ( void ); /* [-1.0, 1.0]; */
float         guassianf          ( float mean, float stddev );
double        guassiand          ( double mean, double stddev );
long double   guassianld         ( long double mean, long double stddev );
int           maxi               ( int x, int y );
long          maxl               ( long x, long y );
float         maxf               ( float x, float y );
double        maxd               ( double x, double y );
long double   maxld              ( long double x, long double y );
int           mini               ( int x, int y );
long          minl               ( long x, long y );
float         minf               ( float x, float y );
double        mind               ( double x, double y );
long double   minld              ( long double x, long double y );
unsigned int  clampui            ( unsigned int value, unsigned int min, unsigned int max );
unsigned long clampul            ( unsigned long value, unsigned long min, unsigned long max );
int           clampi             ( int value, int min, int max );
int           clampi             ( int value, int min, int max );
long          clampl             ( long value, long min, long max );
float         clampf             ( float value, float min, float max );
double        clampd             ( double value, double min, double max );
long double   clampld            ( long double value, long double min, long double max );


static inline bool is_even( int n )
{
	return (n & 1) == 0;
}

static inline bool is_odd( int n )
{
	return (n & 1) == 1;
}

static inline bool is_power_of_2( int x )
{
	return (x & (x - 1)) == 0;
}

static inline int next_power_of_2( int v )
{
	int r = v;
	r--;
	r |= r >> 1;
	r |= r >> 2;
	r |= r >> 4;
	r |= r >> 8;
	r |= r >> 16;
	r++;
	return r;
}



#if 0
static inline scaler_t lerp( scaler_t a, scaler_t x0, scaler_t x1 )
{
	return x0 + (x1 - x0) * a;
}

static inline scaler_t bilerp( scaler_t a, scaler_t b, scaler_t x0, scaler_t x1, scaler_t x2, scaler_t x3 )
{
	return lerp( b, lerp( a, x0, x1 ), lerp( a, x2, x3 ) );
}
#endif

#if 1
#define lerp                                           linear_interpolation
#define linear_interpolation( a, x0, x1 )              ((x0) + (a) * ((x1) - (x0)))
#define bilear_interpolation( a, b, x0, x1, x2, x3 )   (lerp( b, lerp( a, x0, x1 ), lerp( a, x2, x3 ) ))
#define bilerp                                         bilear_interpolation
#endif

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
#define max(a, b) _Generic( (a), \
	int:     maxi, \
	long:    maxl, \
	float:   maxf, \
	double:  maxd, \
	long double:  maxld, \
	default: maxf \
);
#define min(a, b) _Generic( (a), \
	int:     mini, \
	long:    minl, \
	float:   minf, \
	double:  mind, \
	long double:  minld, \
	default: minf \
);

#define clamp(a, b) _Generic( (a), \
	int:     clampi, \
	long:    clampl, \
	float:   clampf, \
	double:  mind, \
	long double:  clampld, \
	default: clampf \
);
#endif


#if defined(LIB3DMATH_USE_LONG_DOUBLE)
#include "scaler-long-double.h"
#elif defined(LIB3DMATH_USE_DOUBLE)
#include "scaler-double.h"
#else /* default: use float */
#include "scaler-float.h"
#endif


static inline scaler_t fast_inverse_sqrt( scaler_t number )
{
	long i;
	scaler_t x2, y;
	const scaler_t threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * (long *) &y;                       /* evil floating point bit level hacking */
	i  = 0x5f3759df - ( i >> 1 );               /* what the fuck? */
	y  = * (scaler_t *) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   /* 1st iteration */
	#if 1
	y  = y * ( threehalfs - ( x2 * y * y ) );   /* 2nd iteration, this can be removed */
	#endif

	return y;
}

#ifdef __cplusplus
} /* C linkage */
#endif
#endif /* _MATHEMATICS_H_ */
