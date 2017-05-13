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
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "mathematics.h"
#include "geographic.h"

#define DEGREES_TO_RADIANS(degs)     ((degs) * M_PI / 180.0)
#define RADIANS_TO_DEGREES(rads)     ((rads) * 180.0 / M_PI)

void wgs84_geographic_to_cartesian( double lon, double lat, double alt, double* x, double* y, double* z )
{
	double r_lon = DEGREES_TO_RADIANS( lon );
	double r_lat = DEGREES_TO_RADIANS( lat );
	double N = WGS84_SEMI_MAJOR_AXIS / sqrt(1.0 - WGS84_ECCENTRICITY_SQUARED * sin( r_lat ) * sin( r_lat ));

	*x = (N + alt) * cos( r_lat ) * cos( r_lon );
	*y = (N + alt) * cos( r_lat ) * sin( r_lon );
	*z = ((1.0 - WGS84_ECCENTRICITY_SQUARED) * N + alt) * sin( r_lat );
}

void wgs84_cartesian_to_geographic_with_epsilon( double x, double y, double z, double* lon, double* lat, double* alt, double epsilon )
{
	double p = sqrt( x * x + y * y );
	*lon = RADIANS_TO_DEGREES( atan( y / x ) );

	// initial value
	double lat_i = atan( z / ((1.0 - WGS84_ECCENTRICITY_SQUARED) * p ) );
	double alt_i = 0.0;

	do {
		*lat = lat_i;
		*alt = alt_i;

		double N_i = WGS84_SEMI_MAJOR_AXIS / sqrt( 1.0 - WGS84_ECCENTRICITY_SQUARED * sin( lat_i ) * sin( lat_i ) );
		double alt_i = (p / cos(lat_i)) - N_i;

		lat_i = atan( z / ((1.0 - WGS84_ECCENTRICITY_SQUARED * (N_i / (N_i + alt_i))) * p));

	} while( fabs(*lat - lat_i) > epsilon &&
	         fabs(*alt - alt_i) > epsilon );

	*lat = RADIANS_TO_DEGREES( lat_i );
	*alt = alt_i;
}

void wgs84_geographic_to_mercator( double lon, double lat, double central_meridian, double* x, double* y )
{
	lat = clampd( lat, -89.5, 89.5 );
	central_meridian = clampd( central_meridian, -180.0, 180.0 );
	*x = WGS84_SEMI_MAJOR_AXIS * DEGREES_TO_RADIANS(lon - central_meridian);
	*y = WGS84_SEMI_MINOR_AXIS * log( tan( M_PI_4 + 0.5 * DEGREES_TO_RADIANS(lat) ) );
}

void wgs84_mercator_to_geographic( double x, double y, double central_meridian, double* lon, double* lat )
{
	*lon = RADIANS_TO_DEGREES(x / WGS84_SEMI_MAJOR_AXIS) + central_meridian;
	*lat = RADIANS_TO_DEGREES(2.0 * atan( exp(y / WGS84_SEMI_MAJOR_AXIS) ) - M_PI_2);
}

double wgs84_geographic_geodesic_distance( double lon1, double lat1, double alt1, double lon2, double lat2, double alt2 )
{
	double distance = 0.0;

	if( true )
	{
		// Lambert's formula for long lines
		double beta1 = atan( (1 -  WGS84_FLATTENING_FACTOR) * tan(lat1) );
		double beta2 = atan( (1 -  WGS84_FLATTENING_FACTOR) * tan(lat2) );

		double p = (beta1 + beta2) / 2.0;
		double q = (beta2 - beta1) / 2.0;
		// central angle between (beta1, lon1) and (beta2, lon2)
		double central_angle = 0.1; // TODO: haversine formula
		double sin_p = sin(p);
		double sin_q = sin(q);
		double cos_q = cos(q);
		double cos_p = cos(p);
		double cos_ca2 = cos( central_angle / 2.0 );

		double x = ((central_angle - sin(central_angle)) * sin_p * sin_p * cos_q * cos_q) / cos_ca2;
		double y = ((central_angle + sin(central_angle)) * cos_p * cos_p * sin_q * sin_q) / cos_ca2;

		distance = WGS84_SEMI_MAJOR_AXIS * (central_angle - (WGS84_FLATTENING_FACTOR / 2.0) * (x + y));
	}
	else
	{
	}
}
