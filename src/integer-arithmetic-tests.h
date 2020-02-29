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
#ifndef _INTEGER_ARITHMETIC_TESTS_H_
#define _INTEGER_ARITHMETIC_TESTS_H_
#include <stdbool.h>

#define m3d_signed_integer_overflow_test(result, a, b, max_val) \
	if( (a) ^ (b) < 0 ) (result) = false; \ // opposite signs can't overflow
	else if( (a) > 0 )  (result) = (b) > max_val - (a); \
	else                (result) = (b) < max_val - (a);

#define m3d_unsigned_integer_overflow_test(result, a, b) \
	(result) = (a) + (b) < (a);

#endif /* _INTEGER_ARITHMETIC_TESTS_H_ */
