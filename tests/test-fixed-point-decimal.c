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
#include <stdbool.h>
#include "../src/fixed-point-decimal.h"
#include "test.h"

bool test_fpdec_create( void );
bool test_fpdec_add( void );
bool test_fpdec_mult( void );
bool test_fpdec_div( void );

const test_feature_t fixed_point_decimal_tests[] = {
	{ "Testing fpdec_t creation",       test_fpdec_create },
	{ "Testing fpdec_t addition",       test_fpdec_add },
	{ "Testing fpdec_t multiplication", test_fpdec_mult },
	{ "Testing fpdec_t division",       test_fpdec_div },
};

size_t fixed_point_decimal_test_suite_size( void )
{
	return sizeof(fixed_point_decimal_tests) / sizeof(fixed_point_decimal_tests[0]);
}

#ifdef TEST_STANDALONE
int main( int argc, char* argv[] )
{
	srand( time(NULL) );
	bool result = test_features( "Fixed Point Decimal Functions", fixed_point_decimal_tests, fixed_point_decimal_test_suite_size() );
	return result ? 0 : 1;
}
#endif


bool test_fpdec_create( void )
{
	fpdec_t a = m3d_fixed_point_decimal_create( 89999999999999, 99999 ); // $89,999,999,999,999.99999
	//char str[64];
	//m3d_fixed_point_decimal_string(str, sizeof(str), a);
	//printf( "%s\n", str);
                    //9223372036854775807
	return a.val == 8999999999999999999LL;
}

bool test_fpdec_add( void )
{
	fpdec_t a = m3d_fixed_point_decimal_create( 0, 1 );
	fpdec_t b = m3d_fixed_point_decimal_create( 0, 2 );
	bool result = true;
	fpdec_t c = m3d_fixed_point_decimal_add( a, b, &result );
	//char str[64];
	//m3d_fixed_point_decimal_string(str, sizeof(str), c);
	//printf( "%s\n", str);
	return result && c.val == 30000;
}

bool test_fpdec_mult( void )
{
	//char str[64];

	fpdec_t a = m3d_fixed_point_decimal_create( 1, 1 );

	//m3d_fixed_point_decimal_string(str, sizeof(str), a);
	//printf( "%s\n", str);

	fpdec_t b = m3d_fixed_point_decimal_create( 1, 2 );

	//m3d_fixed_point_decimal_string(str, sizeof(str), b);
	//printf( "%s\n", str);

	bool result = true;
	fpdec_t c = m3d_fixed_point_decimal_multiply( a, b, &result );

	//m3d_fixed_point_decimal_string(str, sizeof(str), c);
	//printf( "%s\n", str);

	//printf( "%ld %s\n", c.val, result ? "true" : "false");
	return result && c.val == 132000;
}


bool test_fpdec_div( void )
{
	//char str[64];

	fpdec_t a = m3d_fixed_point_decimal_create( 1, 2 );

	//m3d_fixed_point_decimal_string(str, sizeof(str), a);
	//printf( "%s\n", str);

	fpdec_t b = m3d_fixed_point_decimal_create( 0, 3 );

	//m3d_fixed_point_decimal_string(str, sizeof(str), b);
	//printf( "%s\n", str);

	bool result = true;
	fpdec_t c = m3d_fixed_point_decimal_divide( a, b, &result );

	//m3d_fixed_point_decimal_string(str, sizeof(str), c);
	//printf( "%s\n", str);

	//printf( "%ld %s\n", c.val, result ? "true" : "false");
	return result && c.val == 400000;
}

