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
#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_
#include <stddef.h>
#include <stdbool.h>

/*
 * Kuhn–Munkres Assignment Algorithm
 *
 * For 4 workers and 4 tasks:
 *
 *       w0  w1  w2  w3
 *   t0  00  04  08  12
 *   t1  01  05  09  13
 *   t2  02  06  10  14
 *   t3  03  07  11  15
 */
void hungarian_assignment( bool maximal, int cost[], size_t workers, size_t tasks, int output[] );

#endif /* _ALGORITHMS_H_ */
