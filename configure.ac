AC_PREREQ(2.67)
AC_INIT([m3d], [1.0.0], [manvscode@gmail.com], [m3d], [http://www.joemarrero.com/])
AM_INIT_AUTOMAKE([1.13 foreign silent-rules dist-zip -Wall -Werror])
#AC_CONFIG_MACRO_DIRS([m4])

# Enable silent build when possible.
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_CONFIG_HEADERS([src/libm3d-config.h])

AC_PROG_CC
AC_PROG_CC_C11
#AC_PROG_CC_C99
AC_PROG_CC_STDC
AC_HEADER_STDC
AC_C_INLINE
AC_TYPE_SIZE_T

AH_TOP([
#ifndef _LIBM3D_H_
#define _LIBM3D_H_
])
AH_BOTTOM([
#endif /* _LIBM3D_H_ */
])
AX_EXT


AM_PROG_AR
LT_INIT([static])
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL

# -------------------------------------------------
AC_ARG_ENABLE([use_long_double],
	[AS_HELP_STRING([--enable-use-long-double], [Enable scaler types to be long double.])],
	[:],
	[enable_use_long_double=no])
AM_CONDITIONAL([ENABLE_USE_LONG_DOUBLE], [test "x$enable_use_long_double" = "xyes"])

AC_ARG_ENABLE([use_double],
	[AS_HELP_STRING([--enable-use-double], [Enable scaler types to be double.])],
	[:],
	[enable_use_double=no])
AM_CONDITIONAL([ENABLE_USE_DOUBLE], [test "x$enable_use_double" = "xyes"])


AM_COND_IF([ENABLE_USE_LONG_DOUBLE],
	[
		AC_DEFINE([LIBM3D_USE_LONG_DOUBLE], [1], [All scalar types are long double.])
	 	AC_MSG_NOTICE([scaler_t is a long double.])
	],
	[ # else
		AM_COND_IF([ENABLE_USE_DOUBLE],
			[
				AC_DEFINE([LIBM3D_USE_DOUBLE], [1], [All scalar types are double.])
				AC_MSG_NOTICE([scaler_t is a double.])
			],
			[ # else
				AC_DEFINE([LIBM3D_USE_FLOAT], [1], [All scalar types are float.])
				AC_MSG_NOTICE([scaler_t is a float.])
			]
		) # if ENABLE_USE_DOUBLE
	]
) # if ENABLE_USE_LONG_DOUBLE

# -------------------------------------------------
AC_ARG_ENABLE([tests],
	[AS_HELP_STRING([--enable-tests], [Enable test programs.])],
	[:],
	[enable_tests=no])

AM_CONDITIONAL([ENABLE_TESTS], [test "x$enable_tests" = "xyes"])
# -------------------------------------------------

AC_PROG_INSTALL

echo "------------------------------------------------------------------------------"
if [test -z "$CFLAGS"]; then
	echo "  CFLAGS: Not set"
else
	echo "  CFLAGS: $CFLAGS"
fi
if [test -z "$LDFLAGS"]; then
	echo " LDFLAGS: Not set"
else
	echo " LDFLAGS: $LDFLAGS"
fi
echo "------------------------------------------------------------------------------"

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	tests/Makefile
	m3d.pc
])

AC_OUTPUT

