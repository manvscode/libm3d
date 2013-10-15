AC_PREREQ(2.67)
AC_INIT([lib3dmath], [0.1], [manvscode@manvscode.com], [lib3dmath], [http://www.manvscode.com/])
AM_INIT_AUTOMAKE([1.13 foreign silent-rules -Wall -Werror])

AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([src/lib3dmath-config.h])

AC_PROG_CC
AC_PROG_CC_STDC
AC_C_INLINE
AC_HEADER_STDC
AC_PROG_RANLIB


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
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL
LT_INIT([static])

AC_PROG_INSTALL

echo " ------------------------------ "
echo ""
echo "   CFLAGS = $CFLAGS"
echo "  LDFLAGS = $LDFLAGS"
echo ""
echo " ------------------------------ "


AC_ARG_ENABLE([tests],
	[AS_HELP_STRING([--disable-tests], [Enable test programs.])],
	[:],
	[enable_tests=no])

AM_CONDITIONAL([ENABLE_TESTS], [test "$enable_tests" = "yes"])



AC_CONFIG_FILES([
        Makefile
        src/Makefile
        tests/Makefile
])

AC_OUTPUT

