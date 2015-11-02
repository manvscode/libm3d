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
#include "../src/algorithms.h"
#include "test.h"

static double f(double x);

bool test_hungarian_assignment          ( void );

const test_feature_t algorithms_tests[] = {
	{ "Testing Hungarian Assignment",            test_hungarian_assignment },
};

size_t algorithms_test_suite_size( void )
{
	return sizeof(algorithms_tests) / sizeof(algorithms_tests[0]);
}


#ifdef TEST_ALGORITHMS_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	test_features( "Algorithm Functions", algorithms_tests, algorithms_test_suite_size() );
	return 0;
}
#endif


bool test_hungarian_assignment( void )
{
	double root = 0.0;
	bool result = true;
	int output1[ 4 ] = {0};

	int cost1[] = {
		 4,  7,  3,  5,
		 6,  2, 13,  2,
		14,  8,  1,  0,
		11,  9,  4, 13
	};
	int cost1_cpy[] = {
		 4,  7,  3,  5,
		 6,  2, 13,  2,
		14,  8,  1,  0,
		11,  9,  4, 13
	};

	hungarian_assignment( false, cost1, 4, 4, output1 );

	printf( "output1 = [" );
	int total_cost1 = 0;
	for( size_t i = 0; i < 4; i++ )
	{
		printf( "%d ", output1[ i ] );
		total_cost1 += cost1_cpy[ 4 * i + output1[ i ] ];
	}
	printf( "] ==> Cost = %d\n", total_cost1 );
	printf( "-------------------------------\n" );

	int output2[ 4 ] = {0};
	int cost2[] = {
		 6,  5,  2,  4,
		 8,  8,  8, 12,
		 2, 13, 10,  8,
		 7,  9,  9, 11
	};
	int cost2_cpy[] = {
		 6,  5,  2,  4,
		 8,  8,  8, 12,
		 2, 13, 10,  8,
		 7,  9,  9, 11
	};

	hungarian_assignment( true, cost2, 4, 4, output2 );

	printf( "output2 = [" );
	int total_cost2 = 0;
	for( size_t i = 0; i < 4; i++ )
	{
		printf( "%d ", output2[ i ] );
		total_cost2 += cost2_cpy[ 4 * i + output2[ i ] ];
	}
	printf( "] ==> Cost = %d\n", total_cost2 );

	//return result && relative_errord(1.36523, root) < 0.001;
	return result;
}

