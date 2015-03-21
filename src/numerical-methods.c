#include <stdio.h>
#include "numerical-methods.h"
#include "mat2.h"
#include "mat3.h"

void least_squares_linear( const double x[], const double y[], size_t count, double* m, double* b )
{
	double alpha = 0.0;
	double beta  = 0.0;
	double gamma = 0.0;
	double delta = 0.0;

	for( size_t i = 0; i < count; i++ )
	{
		alpha += x[ i ];
		beta  += x[ i ] * x[ i ];
		gamma += y[ i ];
		delta += x[ i ] * y[ i ];
	}

	/* A * c = y  <==>  transpose(A) * A * c = transpose(A) * y)
	 * where:
	 *       * c is the vector of coefficients in y_i = c_0 + c_1 * x_i
	 *       * y is the vector y values y = (y_0, y_1, ..., y_n)
	 *       * A is the n * 2 matrix of [ 1, x ] where x = (x_0, x_1, ..., x_n)
	 */
#if 0
	mat2_t Q_inverse = MAT2( // inverse(Q) where Q = transpose(A) * A
		alpha, (double) count,
		beta,  alpha
	);
	mat2_invert(&Q_inverse);

	double P[] = {
		delta,
		gamma
	};

	*b = Q_inverse.m[0] * P[0] + Q_inverse.m[2] * P[1];
	*m = Q_inverse.m[1] * P[0] + Q_inverse.m[3] * P[1];
#else
	double determinant = alpha * alpha - ((double)count) * beta;
	*b = (delta * alpha - gamma * beta) / determinant;
	*m = (-delta * ((double)count) + gamma * alpha) / determinant;
#endif
}

double least_squares_linear_error( const double x[], const double y[], size_t count, double m, double b )
{
	double error = 0.0;

	for( size_t i = 0; i < count; i++ )
	{
		double diff = y[ i ] - (m * x[ i ] + b);
		error += diff * diff;
	}

	return error;
}

void least_squares_quadratic( const double x[], const double y[], size_t count, double* a, double* b, double* c )
{
	double alpha   = 0.0;
	double beta    = 0.0;
	double gamma   = 0.0;
	double delta   = 0.0;
	double epsilon = 0.0;
	double zeta    = 0.0;
	double eta     = 0.0;

	for( size_t i = 0; i < count; i++ )
	{
		double x_sqr = x[ i ] * x[ i ];
		double x_cub = x_sqr * x[ i ];

		alpha   += x[ i ];
		beta    += x_sqr;
		gamma   += x_cub;
		delta   += x_cub * x[ i ];
		epsilon += y[ i ];
		zeta    += y[ i ] * x[ i ];
		eta     += y[ i ] * x_sqr;
	}

	mat3_t Q_inverse = MAT3( // inverse(Q) where Q = transpose(A) * A
		beta, alpha, (double)count,
		gamma, beta, alpha,
		delta, gamma, beta
	);
	mat3_invert(&Q_inverse);

	vec3_t p = VEC3( eta, zeta, epsilon ); // p = transpose(A) * y
	vec3_t coefficients = mat3_mult_vector( &Q_inverse, &p);
	*a = coefficients.z;
	*b = coefficients.y;
	*c = coefficients.x;
}

double least_squares_quadratic_error( const double x[], const double y[], size_t count, double a, double b, double c )
{
	double error = 0.0;

	for( size_t i = 0; i < count; i++ )
	{
		double diff = y[ i ] - (a * x[ i ] * x[ i ] + b * x[ i ] + c);
		error += diff * diff;
	}

	return error;
}

void table_dump( FILE* stream, const double x[], const double y[], size_t count, const char* label_x, const char* label_y )
{
	fprintf( stream, "+--------------+--------------+\n" );
	fprintf( stream, "|%13s | %-13s|\n", label_x, label_y );
	fprintf( stream, "+--------------+--------------+\n" );
	for( size_t i = 0; i < count; i++ )
	{
		fprintf( stream, "|%13.4f | %-13.4f|\n", x[ i ], y[ i ] );
	}
	fprintf( stream, "+--------------+--------------+\n" );
}