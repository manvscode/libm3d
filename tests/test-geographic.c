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
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <assert.h>
#include "../src/geographic.h"
#include "test.h"


bool test_geographic_to_cartesian   ( void );
bool test_cartesian_to_geographic   ( void );
bool test_geographic_to_mercator    ( void );
bool test_mercator_to_geographic    ( void );
bool test_distance                  ( void );

const test_feature_t geographic_tests[] = {
	{ "Testing WGS84 Geographic to Cartesian",     test_geographic_to_cartesian },
	{ "Testing WGS84 Cartesian to Geographic",     test_cartesian_to_geographic },
	{ "Testing WGS84 Geographic to Mercator",      test_geographic_to_mercator },
	{ "Testing WGS84 Mercator to Geographic",      test_mercator_to_geographic },
	{ "Testing WGS84 Geodesic Distance",           test_distance },
};

size_t geographic_test_suite_size( void )
{
	return sizeof(geographic_tests) / sizeof(geographic_tests[0]);
}


#ifdef TEST_GEOGRAPHIC_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "Geographic Functions", geographic_tests, geographic_test_suite_size() );
	return 0;
}
#endif


bool test_geographic_to_cartesian( void )
{
	double lat = 25.7753;
	double lon = 80.2089;
	double x = 0.0, y = 0.0, z = 0.0;
	wgs84_geographic_to_cartesian( lon, lat, 0.0, &x, &y, &z );
	//printf( "Miami at (%.4f N, %.4f W) = (%.4f, %.4f, %.4f)\n", lat, lon, x, y, z );
	return fabs( x - 977346.827770 ) < 0.000001 &&
	       fabs( y - 5663479.560864 ) < 0.000001 &&
	       fabs( z - 2756666.317698 ) < 0.000001;
}

bool test_cartesian_to_geographic( void )
{
	double x = 977346.827769572;
	double y = 5663479.56086437;
	double z = 2756666.31765847;
	double lon = 0.0, lat = 0.0, alt = 0.0;
	wgs84_cartesian_to_geographic( x, y, z, &lon, &lat, &alt );
	//printf( "(%.4f, %.4f, %.4f) = Miami at (%.4f N, %.4f W)\n", x, y, z, lat, lon );
	return fabs( lon - 80.2089 ) < 0.000001 &&
	       fabs( lat - 25.7753 ) < 0.000001 &&
	       fabs( alt - 0.0 ) < 0.000001;
}

bool test_geographic_to_mercator( void )
{
	double lat = 25.7753;
	double lon = 80.2089;
	double x = 0.0, y = 0.0;
	wgs84_geographic_to_mercator_standard( lon, lat, &x, &y );
	//printf( "Miami at (%.4f N, %.4f W) = (%.4f, %.4f)\n", lat, lon, x, y );
	bool result1 = fabs( x + 11108694.4377 ) < 0.0001 &&
	               fabs( y - 2961315.2670 )  < 0.0001;

	lat = 0.0;
	lon = 0.0;
	x = 0.0;
   	y = 0.0;
	wgs84_geographic_to_mercator_standard( lon, lat, &x, &y );
	//printf( "(%.4f N, %.4f W) = (%.4f, %.4f)\n", lat, lon, x, y );
	bool result2 = fabs( x + 20037508.3428 ) < 0.0001 &&
	               fabs( y - 0.0 )  < 0.0001;

	return result1 && result2;
}

bool test_mercator_to_geographic( void )
{
	double x = -11108694.4377;
	double y = 2961315.2670;
	double lon = 0.0, lat = 0.0;
	wgs84_mercator_to_geographic_standard( x, y, &lon, &lat );
	//printf( "(%.4f, %.4f) = Miami at (%.4f N, %.4f W)\n", x, y, lat, lon );
	bool result1 = fabs( lon - 80.2089 ) < 0.0001 &&
	               fabs( lat - 25.7753 )  < 0.1;

	x = 0.0;
	y = 0.0;
	wgs84_mercator_to_geographic_standard( x, y, &lon, &lat );
	//printf( "(%.4f, %.4f) = (%.4f N, %.4f W)\n", x, y, lat, lon );
	bool result2 = fabs( lon - 180.0 ) < 0.0001 &&
	               fabs( lat - 0.0 )  < 0.1;

	return result1 && result2;
}

bool test_distance( void )
{
	double miami_lon = -80.1918;
	double miami_lat = 25.7617;

	double london_lon = -0.1278;
	double london_lat = 51.5074;

	// TODO: Fix Vincenty method
	double miami_london_distance = //wgs84_geographic_geodesic_distance_vincenty( miami_lon, miami_lat, london_lon, london_lat );
	wgs84_geographic_geodesic_distance_lamberts( miami_lon, miami_lat, london_lon, london_lat );

	// haversine 7134873.449671
	// lamberts  7140928.774804
	//           7122228.213423586
	//printf( "%lf", miami_london_distance);

	return true;
}
