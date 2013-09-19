#include <stdlib.h>
#include <math.h>
#include "mathematics.h"

float uniform_unit( void )
{
	return (float) ((rand( ) << 1) - RAND_MAX); // 2.0f * rand() - RAND_MAX
}

float uniformf( void )
{
	return ((float)rand( )) / RAND_MAX;
}

double uniformd( void )
{
	return ((double)rand( )) / RAND_MAX;
}


float guassianf( float mean, float stddev )
{
	float ux;
	float uy;
	float s;
	static float spare;
	static bool spare_ready = false;

	if( spare_ready )
	{
		spare_ready = false;
		return mean + stddev * spare;
	}
	else
	{
		do {
			ux = uniformf( ) * 2.0f - 1;
			uy = uniformf( ) * 2.0f - 1;
			s = ux * ux + uy * uy;
		} while( s >= 1.0f || s <= 0.0f );

		float mul = sqrtf( -2.0f * logf(s) / s );

		spare = uy * mul;
		spare_ready = true;

		return mean + stddev * ux * mul;
	}
}

double guassiand( double mean, double stddev )
{
	double ux;
	double uy;
	double s;
	static double spare;
	static bool spare_ready = false;

	if( spare_ready )
	{
		spare_ready = false;
		return mean + stddev * spare;
	}
	else
	{
		do {
			ux = uniformd( ) * 2.0 - 1;
			uy = uniformd( ) * 2.0 - 1;
			s = ux * ux + uy * uy;
		} while( s >= 1.0f || s <= 0.0f );

		double mul = sqrt( -2.0f * log(s) / s );

		spare = uy * mul;
		spare_ready = true;

		return mean + stddev * ux * mul;
	}
}
