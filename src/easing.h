/* Copyright (C) 2013 by Joseph A. Marrero, http://www.manvscode.com/
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
#include <stdlib.h>
#include <math.h>
#include "mathematics.h"

static inline scaler_t easing_lerp( scaler_t start, scaler_t end, scaler_t value )
{
	//return ((1.0f - value) * start) + (value * end);
	return lerp( value, start, end );
}

static inline scaler_t easing_hermite( scaler_t start, scaler_t end, scaler_t value )
{
	return lerp( value * value * (3.0f - 2.0f * value), start, end );
}

static inline scaler_t easing_sinerp( scaler_t start, scaler_t end, scaler_t value )
{
	return lerp( sinf(value * PI * 0.5f), start, end );
}

static inline scaler_t easing_coserp( scaler_t start, scaler_t end, scaler_t value )
{
	return lerp( 1.0f - cosf(value * PI * 0.5f), start, end );
}

/* Overshoots and then bounces at the end */
static inline scaler_t easing_berp( scaler_t start, scaler_t end, scaler_t value )
{
	value = clampf( value, 0.0f, 1.0f );
	value = ( sinf(value * PI * (0.2f + 2.5f * value * value * value)) * powf(1.0f - value, 2.2f) + value) * (1.0f + (1.2f * (1.0f - value)));
	return start + (end - start) * value;
}

static inline scaler_t easing_smooth_step( scaler_t x, scaler_t min, scaler_t max )
{
	x = clampf( x, min, max );
	scaler_t v1 = (x - min) / (max - min);
	scaler_t v2 = (x - min) / (max - min);
	return -2*v1 * v1 *v1 + 3*v2 * v2;
}

scaler_t easing_bounce( scaler_t x )
{
	return fabs( sinf(6.28f*(x+1.0f)*(x+1.0f)) * (1.0f-x) );
}
 

static inline scaler_t easing_linear( scaler_t step )
{
	return step;
}

static inline scaler_t easing_in_quadratic( scaler_t step, scaler_t acceleration )
{
	return lerp( fabs(acceleration), step, step * step );
}

static inline scaler_t easing_out_quadratic( scaler_t step, scaler_t acceleration )
{
	return lerp( fabs(acceleration), step, (1.0 - step) * (1.0 - step) );
}

static inline scaler_t easing_inout_quadratic( scaler_t step, scaler_t acceleration )
{
	return lerp( fabs(acceleration), step, (1.0 - step) * (1.0 - step) );
}

/*
// http://gizma.com/easing/
simple linear tweening - no easing, no acceleration


Math.linearTween = function (t, b, c, d) {
	return c*t/d + b;
	// return (e-b)*t
};
		

// quadratic easing in - accelerating from zero velocity


Math.easeInQuad = function (t, b, c, d) {
	t /= d;
	return c*t*t + b;
};
		

// quadratic easing out - decelerating to zero velocity


Math.easeOutQuad = function (t, b, c, d) {
	t /= d;
	return -c * t*(t-2) + b;
};

		

// quadratic easing in/out - acceleration until halfway, then deceleration


Math.easeInOutQuad = function (t, b, c, d) {
	t /= d/2;
	if (t < 1) return c/2*t*t + b;
	t--;
	return -c/2 * (t*(t-2) - 1) + b;
};


// cubic easing in - accelerating from zero velocity


Math.easeInCubic = function (t, b, c, d) {
	t /= d;
	return c*t*t*t + b;
};

		

// cubic easing out - decelerating to zero velocity


Math.easeOutCubic = function (t, b, c, d) {
	t /= d;
	t--;
	return c*(t*t*t + 1) + b;
};

		

// cubic easing in/out - acceleration until halfway, then deceleration


Math.easeInOutCubic = function (t, b, c, d) {
	t /= d/2;
	if (t < 1) return c/2*t*t*t + b;
	t -= 2;
	return c/2*(t*t*t + 2) + b;
};
	

// quartic easing in - accelerating from zero velocity


Math.easeInQuart = function (t, b, c, d) {
	t /= d;
	return c*t*t*t*t + b;
};

		

// quartic easing out - decelerating to zero velocity


Math.easeOutQuart = function (t, b, c, d) {
	t /= d;
	t--;
	return -c * (t*t*t*t - 1) + b;
};

		

// quartic easing in/out - acceleration until halfway, then deceleration


Math.easeInOutQuart = function (t, b, c, d) {
	t /= d/2;
	if (t < 1) return c/2*t*t*t*t + b;
	t -= 2;
	return -c/2 * (t*t*t*t - 2) + b;
};


// quintic easing in - accelerating from zero velocity


Math.easeInQuint = function (t, b, c, d) {
	t /= d;
	return c*t*t*t*t*t + b;
};

		

// quintic easing out - decelerating to zero velocity


Math.easeOutQuint = function (t, b, c, d) {
	t /= d;
	t--;
	return c*(t*t*t*t*t + 1) + b;
};

		

// quintic easing in/out - acceleration until halfway, then deceleration


Math.easeInOutQuint = function (t, b, c, d) {
	t /= d/2;
	if (t < 1) return c/2*t*t*t*t*t + b;
	t -= 2;
	return c/2*(t*t*t*t*t + 2) + b;
};
		

// sinusoidal easing in - accelerating from zero velocity


Math.easeInSine = function (t, b, c, d) {
	return -c * Math.cos(t/d * (Math.PI/2)) + c + b;
};

		

// sinusoidal easing out - decelerating to zero velocity


Math.easeOutSine = function (t, b, c, d) {
	return c * Math.sin(t/d * (Math.PI/2)) + b;
};

		

// sinusoidal easing in/out - accelerating until halfway, then decelerating


Math.easeInOutSine = function (t, b, c, d) {
	return -c/2 * (Math.cos(Math.PI*t/d) - 1) + b;
};

		

// exponential easing in - accelerating from zero velocity


Math.easeInExpo = function (t, b, c, d) {
	return c * Math.pow( 2, 10 * (t/d - 1) ) + b;
};

		

// exponential easing out - decelerating to zero velocity


Math.easeOutExpo = function (t, b, c, d) {
	return c * ( -Math.pow( 2, -10 * t/d ) + 1 ) + b;
};

		

// exponential easing in/out - accelerating until halfway, then decelerating


Math.easeInOutExpo = function (t, b, c, d) {
	t /= d/2;
	if (t < 1) return c/2 * Math.pow( 2, 10 * (t - 1) ) + b;
	t--;
	return c/2 * ( -Math.pow( 2, -10 * t) + 2 ) + b;
};
		

// circular easing in - accelerating from zero velocity


Math.easeInCirc = function (t, b, c, d) {
	t /= d;
	return -c * (Math.sqrt(1 - t*t) - 1) + b;
};

		

// circular easing out - decelerating to zero velocity


Math.easeOutCirc = function (t, b, c, d) {
	t /= d;
	t--;
	return c * Math.sqrt(1 - t*t) + b;
};

		

// circular easing in/out - acceleration until halfway, then deceleration


Math.easeInOutCirc = function (t, b, c, d) {
	t /= d/2;
	if (t < 1) return -c/2 * (Math.sqrt(1 - t*t) - 1) + b;
	t -= 2;
	return c/2 * (Math.sqrt(1 - t*t) + 1) + b;
};
*/
