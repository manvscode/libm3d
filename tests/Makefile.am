if ENABLE_TESTS

AM_CFLAGS = -std=c11 -pg -g -ggdb -O0 -I$(top_builddir)/src/ -I. -I.. -I/usr/local/include/
AM_CXXFLAGS = -std=c++0x -pg -g -ggdb -O0 -I$(top_builddir)/src/ -I. -I.. -I/usr/local/include/
LDADD = -lm 

bin_PROGRAMS = \
$(top_builddir)/bin/test-math \
$(top_builddir)/bin/test-mat3 \
$(top_builddir)/bin/test-random-numbers

__top_builddir__bin_test_math_SOURCES              = test-math.c
__top_builddir__bin_test_math_LDFLAGS              = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_mat3_SOURCES              = test-mat3.c
__top_builddir__bin_test_mat3_LDFLAGS              = -lm $(top_builddir)/lib/lib3dmath.la
__top_builddir__bin_test_random_numbers_SOURCES    = test-random-numbers.c
__top_builddir__bin_test_random_numbers_LDFLAGS    = -lm $(top_builddir)/lib/lib3dmath.la

endif
