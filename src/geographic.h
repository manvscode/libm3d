/* Copyright (C) 2013-2025 by Joseph A. Marrero, http://joemarrero.com/
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
#ifndef _GEOGRAPHIC_H_
#define _GEOGRAPHIC_H_
#include <stddef.h>
#include <stdbool.h>

#define WGS84_SEMI_MAJOR_AXIS         (6378137.0) /* center to equator */
#define WGS84_SEMI_MINOR_AXIS         (6356752.314245) /* center to pole */
#define WGS84_FLATTENING_FACTOR       (1.0 - (WGS84_SEMI_MINOR_AXIS / WGS84_SEMI_MAJOR_AXIS))
#define WGS84_ECCENTRICITY_SQUARED    (2.0 * WGS84_FLATTENING_FACTOR - WGS84_FLATTENING_FACTOR * WGS84_FLATTENING_FACTOR)

typedef struct geo_coord {
	double lat;
	double lon;
	double alt;
} geo_coord_t;

void   wgs84_geographic_to_cartesian( double lon, double lat, double alt, double* x, double* y, double* z );
void   wgs84_cartesian_to_geographic_with_epsilon( double x, double y, double z, double* lon, double* lat, double* alt, double epsilon );
void   wgs84_geographic_to_mercator( double lon, double lat, double central_meridian, double* x, double* y );
void   wgs84_mercator_to_geographic( double x, double y, double central_meridian, double* lon, double* lat );
double wgs84_geographic_geodesic_distance_vincenty( double lon1, double lat1, double lon2, double lat2 );
double wgs84_geographic_geodesic_distance_lamberts( double lon1, double lat1, double lon2, double lat2 );
double wgs84_geographic_geodesic_distance_haversine( double lon1, double lat1, double lon2, double lat2 );

static inline void wgs84_cartesian_to_geographic( double x, double y, double z, double* lon, double* lat, double* alt )
{
	wgs84_cartesian_to_geographic_with_epsilon(x, y, z, lon, lat, alt, DBL_EPSILON );
}

static inline void wgs84_geographic_to_mercator_standard( double lon, double lat, double* x, double* y )
{
	wgs84_geographic_to_mercator( lon, lat, 180.0, x, y );
}

static inline void wgs84_mercator_to_geographic_standard( double x, double y, double* lon, double* lat )
{
	wgs84_mercator_to_geographic( x, y, 180.0, lon, lat );
}

#endif /* _GEOGRAPHIC_H_ */
