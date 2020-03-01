# Add new files in alphabetical order. Thanks.
libm3d_src = \
             algorithms.c \
             fixed-point-decimal.c \
             geographic.c \
             geometric-tools.c \
             mat2.c \
             mat3.c \
             mat4.c \
             mathematics.c \
             numerical-methods.c \
             quat.c \
             transforms.c \
             vec2.c \
             vec3.c \
             vec4.c

# Add new files in alphabetical order. Thanks.
libm3d_headers = \
                 algorithms.h \
                 easing.h \
                 fixed-point-decimal.h \
                 geographic.h \
                 geometric-tools.h \
                 integer-arithmetic-tests.h \
                 libm3d-config.h \
                 mat2.h \
                 mat3.h \
                 mat4.h \
                 mathematics.h \
                 numerical-methods.h \
                 projections.h \
                 quat.h \
                 scaler-double.h \
                 scaler-float.h \
                 scaler-long-double.h \
                 transforms.h \
                 vec2.h \
                 vec3.h \
                 vec4.h

library_includedir      = $(includedir)/m3d-@VERSION@/
library_include_HEADERS = $(libm3d_headers)

# Library
lib_LTLIBRARIES                       = $(top_builddir)/lib/libm3d.la
__top_builddir__lib_libm3d_la_SOURCES = $(libm3d_src)
__top_builddir__lib_libm3d_la_LDFLAGS = -lm
