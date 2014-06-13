AC_PREREQ(2.67)
AC_INIT([lib3dmath], [1.0], [manvscode@manvscode.com], [lib3dmath], [http://www.manvscode.com/])
AM_INIT_AUTOMAKE([1.13 foreign silent-rules -Wall -Werror])

AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([src/lib3dmath-config.h])

AC_PROG_CC
AC_PROG_CC_C99
AC_C_INLINE
AC_HEADER_STDC

AH_TOP([
#ifndef _LIB3DMATH_H_
#define _LIB3DMATH_H_
])
AH_BOTTOM([
#endif /* _LIB3DMATH_H_ */
])

DFLAGS="$DFLAGS"

CFLAGS="$DFLAGS $CFLAGS"
#CFLAGS="-Wall -g -ggdb -O0 $DFLAGS $CFLAGS"
LDFLAGS="-lm $LDFLAGS"


AM_PROG_AR
LT_INIT([static])
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL


# -------------------------------------------------
AC_ARG_ENABLE([use_double],
	[AS_HELP_STRING([--enable-use-double], [Enable scaler types to be double instead of float.])],
	[:],
	[enable_use_double=no])
AM_CONDITIONAL([ENABLE_USE_DOUBLE], [test "x$enable_use_double" = "xyes"])

AM_COND_IF([ENABLE_USE_DOUBLE],
	[AC_DEFINE([LIB3DMATH_USE_DOUBLE], [1], [All scalar types are double.])
	 AC_MSG_NOTICE([scaler_t is a double.])],
	[AC_DEFINE([LIB3DMATH_USE_FLOAT], [0], [All scalar types are float.])
	AC_MSG_NOTICE([scaler_t is a float.])
])
# -------------------------------------------------
AC_ARG_ENABLE([tests],
	[AS_HELP_STRING([--enable-tests], [Enable test programs.])],
	[:],
	[enable_tests=no])

AM_CONDITIONAL([ENABLE_TESTS], [test "x$enable_tests" = "xyes"])
# -------------------------------------------------

AC_PROG_INSTALL

echo " ------------------------------ "
echo ""
echo "   CFLAGS = $CFLAGS"
echo "  LDFLAGS = $LDFLAGS"
echo ""
echo " ------------------------------ "

AC_CONFIG_FILES([
        Makefile
        src/Makefile
        tests/Makefile
])

AC_OUTPUT

