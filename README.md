# libm3d
A fully-tested math library for computer graphics applications and games.

## Supported Constructs
* 2D vectors
* 3D vectors
* 4D vectors
* 2x2 matrices
* 3x3 matrices
* 4x4 matrices
* Quaternions
* Transformations
* Projections
* Geometric tools
* Numerical Methods for root-finding and least squares fitting.
* Geographic WGS84 transformations and distance calculations.

##  Build Instructions
You can compile *libm3d* with either float or double precision.
### If you want to build the float version of libm3d:
* autoreconf -i
* ./configure
* make
* make install

### If you want to build the double version of libm3d:
* autoreconf -i
* ./configure --enable-use-double
* make
* make install

### If you want to build the long double version of libm3d:
* autoreconf -i
* ./configure --enable-use-long-double
* make
* make install

##  Testing
If you want to enable the test programs, you just need to use the
--enable-tests configure flag.

# License
You may use *libm3d* in a commercial product as long as the below copyright is retained in the source directory and on all source files.

    Copyright (C) 2013-2015 by Joseph A. Marrero, http://www.manvscode.com/
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
