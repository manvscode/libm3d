# Add new files in alphabetical order. Thanks.
lib3dmath_src = vec2.c vec3.c vec4.c mat2.c mat3.c mat4.c mathematics.c

# Add new files in alphabetical order. Thanks.
lib3dmath_headers = vec2.h vec3.h vec4.h mat2.h mat3.h mat4.h mathematics.h 

library_includedir      = $(includedir)/lib3dmath/
library_include_HEADERS = $(lib3dmath_headers)

# Library
lib_LTLIBRARIES                          = $(top_builddir)/lib/lib3dmath.la
__top_builddir__lib_lib3dmath_la_SOURCES = $(lib3dmath_src)
__top_builddir__lib_lib3dmath_la_LDFLAGS = -lm 
