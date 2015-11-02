if ENABLE_TESTS

AM_CFLAGS = -std=c11 -pg -g -ggdb -O0 -I$(top_builddir)/src/ -I. -I.. -I/usr/local/include/
AM_CXXFLAGS = -std=c++0x -pg -g -ggdb -O0 -I$(top_builddir)/src/ -I. -I.. -I/usr/local/include/
LDADD = -lm

bin_PROGRAMS = $(top_builddir)/bin/3dmath-tests \
			   $(top_builddir)/bin/test-math \
			   $(top_builddir)/bin/test-vec2 \
			   $(top_builddir)/bin/test-vec3 \
			   $(top_builddir)/bin/test-vec4 \
			   $(top_builddir)/bin/test-mat2 \
			   $(top_builddir)/bin/test-mat3 \
			   $(top_builddir)/bin/test-mat4 \
			   $(top_builddir)/bin/test-random-numbers \
			   $(top_builddir)/bin/test-numerical-methods \
			   $(top_builddir)/bin/test-algorithms \
			   $(top_builddir)/bin/test-geographic

__top_builddir__bin_3dmath_tests_SOURCES           = test-all.c test-math.c test-vec2.c test-vec3.c test-vec4.c test-mat2.c test-mat3.c test-mat4.c test-numerical-methods.c test-geographic.c
__top_builddir__bin_3dmath_tests_LDFLAGS           = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_math_SOURCES              = test-math.c
__top_builddir__bin_test_math_CFLAGS               = -DTEST_MATHEMATICS_STANDALONE
__top_builddir__bin_test_math_LDFLAGS              = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_vec2_SOURCES              = test-vec2.c
__top_builddir__bin_test_vec2_CFLAGS               = -DTEST_VEC2_STANDALONE
__top_builddir__bin_test_vec2_LDFLAGS              = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_vec3_SOURCES              = test-vec3.c
__top_builddir__bin_test_vec3_CFLAGS               = -DTEST_VEC3_STANDALONE
__top_builddir__bin_test_vec3_LDFLAGS              = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_vec4_SOURCES              = test-vec4.c
__top_builddir__bin_test_vec4_CFLAGS               = -DTEST_VEC4_STANDALONE
__top_builddir__bin_test_vec4_LDFLAGS              = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_mat2_SOURCES              = test-mat2.c
__top_builddir__bin_test_mat2_CFLAGS               = -DTEST_MAT2_STANDALONE
__top_builddir__bin_test_mat2_LDFLAGS              = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_mat3_SOURCES              = test-mat3.c
__top_builddir__bin_test_mat3_CFLAGS               = -DTEST_MAT3_STANDALONE
__top_builddir__bin_test_mat3_LDFLAGS              = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_mat4_SOURCES              = test-mat4.c
__top_builddir__bin_test_mat4_CFLAGS               = -DTEST_MAT4_STANDALONE
__top_builddir__bin_test_mat4_LDFLAGS              = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_random_numbers_SOURCES    = test-random-numbers.c
__top_builddir__bin_test_random_numbers_LDFLAGS    = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_numerical_methods_SOURCES = test-numerical-methods.c
__top_builddir__bin_test_numerical_methods_CFLAGS  = -DTEST_NUMERICAL_METHODS_STANDALONE
__top_builddir__bin_test_numerical_methods_LDFLAGS = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_algorithms_SOURCES        = test-algorithms.c
__top_builddir__bin_test_algorithms_CFLAGS         = -DTEST_ALGORITHMS_STANDALONE
__top_builddir__bin_test_algorithms_LDFLAGS        = -lm $(top_builddir)/lib/lib3dmath.la

__top_builddir__bin_test_geographic_SOURCES        = test-geographic.c
__top_builddir__bin_test_geographic_CFLAGS         = -DTEST_GEOGRAPHIC_STANDALONE
__top_builddir__bin_test_geographic_LDFLAGS        = -lm $(top_builddir)/lib/lib3dmath.la
endif
