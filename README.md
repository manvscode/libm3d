# lib3dmath
A fully-tested math library for computer graphics applications and games.

## Supported Constructs
* 2D Vectors
* 3D Vectors
* 4D Vectors
* 2x2 Matrices
* 3x3 Matrices
* 4x4 Matrices
* Quaternions
* Transformations
* Projections
* Geometric Tools

##  Build Instructions
You can compile *lib3dmath* with either float or double precision.
### If you want to build the float version of lib3dmath:
* autoreconf -i
* ./configure
* make
* make install

### If you want to build the double version of lib3dmath:
* autoreconf -i
* ./configure --enable-use-double
* make
* make install

##  Supported Environments
* Mac OS X
* Linux
* iOS

##  Testing
If you want to enable the test programs, you just need to use the
--enable-tests configure flag.

# License
You may use *lib3dmath* in a commercial product as long as the below copyright is retained in the source directory and on all source files.

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
