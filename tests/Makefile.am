AM_CFLAGS = -std=c99 -pg -g -ggdb -O0 -I$(top_builddir)/src/ -I. -I.. -I/usr/local/include/ -L$(top_builddir)/lib/ 
AM_CXXFLAGS = -std=c++0x -pg -g -ggdb -O0 -I$(top_builddir)/src/ -I. -I.. -I/usr/local/include/ -L$(top_builddir)/lib/
LDADD = -lm #-lGL

bin_PROGRAMS = \
$(top_builddir)/bin/test-math 

__top_builddir__bin_test_math_SOURCES    = test-math.c
__top_builddir__bin_test_math_LDFLAGS    = -lGL $(top_builddir)/lib/.libs/lib3dmath.a
