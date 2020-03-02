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
#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_

#if defined(_MSC_VER) || defined(__WIN32__) || defined(__WIN64__)
# include "libm3d-config-windows.h"
#else
# include "libm3d-config.h"
#endif

/* Compiler Intrinsics */
#if defined(_MSC_VEC)
# include <intrin.h>  /* Microsoft C/C++-compatible compiler */
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
# include <x86intrin.h> /* GCC-compatible compiler, targeting x86/x86-64 */
#elif defined(__GNUC__) && defined(__ARM_NEON__)
# include <arm_neon.h> /* GCC-compatible compiler, targeting ARM with NEON */
#elif defined(__GNUC__) && defined(__IWMMXT__)
# include <mmintrin.h> /* GCC-compatible compiler, targeting ARM with WMMX */
#elif (defined(__GNUC__) || defined(__xlC__)) && (defined(__VEC__) || defined(__ALTIVEC__))
# include <altivec.h> /* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
#elif defined(__GNUC__) && defined(__SPE__)
# include <spe.h> /* GCC-compatible compiler, targeting PowerPC with SPE */
#endif
#include <math.h>
#include <float.h>
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
# include <stdbool.h>
#else
# error "Need a C99 compiler."
#endif

#if defined(LIBM3D_USE_LONG_DOUBLE)
# ifndef M_PI
#  define M_PI   3.141592653589793238462643383279502884L
# endif
# ifndef M_PI_2
#  define M_PI_2 1.570796326794896619231321691639751442L
# endif
#elif defined(LIBM3D_USE_DOUBLE)
# ifndef M_PI
#  define M_PI   3.14159265358979323846
# endif
# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923
# endif
#else
# ifndef M_PI
#  define M_PI   3.14159265358979323846f
# endif
# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923f
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define M3D_HALF_PI               (M_PI_2)
#define M3D_PI                    (M_PI)
#define M3D_TWO_PI                (2*M_PI)
#define M3D_RADIANS_PER_DEGREE    (M_PI / 180.0)
#define M3D_DEGREES_PER_RANDIAN   (180.0 / M_PI)
#define M3D_EASING_EPSILON        (0.0001)

#define m3d_to_radians( degrees )  ((degrees) * M3D_RADIANS_PER_DEGREE)
#define m3d_to_degrees( radians )  ((radians) * M3D_DEGREES_PER_RANDIAN)

#define m3d_integer_max( x, y )    ((x) ^ (((x) ^ (y)) & -((x) < (y))))
#define m3d_integer_min( x, y )    ((y) ^ (((x) ^ (y)) & -((x) < (y))))

float         m3d_uniformf           ( void ); /* [0.0f, 1.0f] */
double        m3d_uniformd           ( void ); /* [0.0, 1.0] */
long double   m3d_uniformld          ( void ); /* [0.0, 1.0] */
int           m3d_uniform_rangei     ( int min, int max ); /* [min. max] */
long          m3d_uniform_rangel     ( long min, long max ); /* [min. max] */
float         m3d_uniform_rangef     ( float min, float max ); /* [min. max] */
double        m3d_uniform_ranged     ( double min, double max ); /* [min. max] */
float         m3d_uniform_unitf      ( void ); /* [-1.0f, 1.0f]; */
double        m3d_uniform_unitd      ( void ); /* [-1.0, 1.0]; */
long double   m3d_uniform_unitld     ( void ); /* [-1.0, 1.0]; */
float         m3d_guassianf          ( float mean, float stddev );
double        m3d_guassiand          ( double mean, double stddev );
long double   m3d_guassianld         ( long double mean, long double stddev );
int           m3d_maxi               ( int x, int y );
long          m3d_maxl               ( long x, long y );
float         m3d_maxf               ( float x, float y );
double        m3d_maxd               ( double x, double y );
long double   m3d_maxld              ( long double x, long double y );
int           m3d_mini               ( int x, int y );
long          m3d_minl               ( long x, long y );
float         m3d_minf               ( float x, float y );
double        m3d_mind               ( double x, double y );
long double   m3d_minld              ( long double x, long double y );
unsigned int  m3d_clampui            ( unsigned int value, unsigned int min, unsigned int max );
unsigned long m3d_clampul            ( unsigned long value, unsigned long min, unsigned long max );
int           m3d_clampi             ( int value, int min, int max );
int           m3d_clampi             ( int value, int min, int max );
long          m3d_clampl             ( long value, long min, long max );
float         m3d_clampf             ( float value, float min, float max );
double        m3d_clampd             ( double value, double min, double max );
long double   m3d_clampld            ( long double value, long double min, long double max );
int           m3d_powi               ( int b, unsigned int e );
long int      m3d_powli              ( long b, unsigned long e );

static inline bool m3d_is_even( int n )
{
	return (n & 1) == 0;
}

static inline bool m3d_is_odd( int n )
{
	return (n & 1) == 1;
}

static inline bool m3d_is_power_of_2( int x )
{
	return (x & (x - 1)) == 0;
}

static inline int m3d_next_power_of_2( int v )
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
#define m3d_lerp                                           m3d_linear_interpolation
#define m3d_linear_interpolation( a, x0, x1 )              ((x0) + (a) * (x1) * (1.0 - (a)))
#define m3d_bilear_interpolation( a, b, x0, x1, x2, x3 )   (m3d_lerp( b, m3d_lerp( a, x0, x1 ), m3d_lerp( a, x2, x3 ) ))
#define m3d_bilerp                                         m3d_bilear_interpolation
#endif

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
/*
 * C11 generic functions
 */
#define m3d_uniform_range(min_num, max_num) _Generic( (min_num), \
	int:     m3d_uniform_rangei, \
	long:    m3d_uniform_rangel, \
	float:   m3d_uniform_rangef, \
	double:  m3d_uniform_ranged, \
	default: m3d_uniform_rangef \
);
#define m3d_uniform(type) _Generic( (type), \
	float:   m3d_uniformf, \
	double:  m3d_uniformd, \
	default: m3d_uniformf \
);
#define m3d_guassian(mean, stddev) _Generic( (mean), \
	float:   m3d_guassianf, \
	double:  m3d_guassiand, \
	default: m3d_guassianf \
);
#define m3d_max(a, b) _Generic( (a), \
	int:     m3d_maxi, \
	long:    m3d_maxl, \
	float:   m3d_maxf, \
	double:  m3d_maxd, \
	long double:  m3d_maxld, \
	default: m3d_maxf \
);
#define m3d_min(a, b) _Generic( (a), \
	int:     m3d_mini, \
	long:    m3d_minl, \
	float:   m3d_minf, \
	double:  m3d_mind, \
	long double:  m3d_minld, \
	default: m3d_minf \
);
#define m3d_clamp(a, b) _Generic( (a), \
	int:     m3d_clampi, \
	long:    m3d_clampl, \
	float:   m3d_clampf, \
	double:  m3d_mind, \
	long double:  m3d_clampld, \
	default: m3d_clampf \
);
#define m3d_power(b, e) _Generic( (b), \
	int:     m3d_powi, \
	long:    m3d_powli, \
	float:   powf, \
	double:  pow, \
	long double:  powl, \
	default: powf \
);
#endif


#if defined(LIBM3D_USE_LONG_DOUBLE)
# include "scaler-long-double.h"
#elif defined(LIBM3D_USE_DOUBLE)
# include "scaler-double.h"
#else /* default: use float */
# include "scaler-float.h"
#endif


static inline scaler_t m3d_fast_inverse_sqrt( scaler_t number )
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
