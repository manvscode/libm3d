AC_PREREQ(2.67)
AC_INIT([lib3dmath], [0.1], [manvscode@manvscode.com], [lib3dmath], [http://www.manvscode.com/])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([src/lib3dmath-config.h])

AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CXX
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


DFLAGS=""

CFLAGS="-std=c99 -Wall -O3 $DFLAGS -I/usr/include -I/usr/local/include -I/usr/include "
#CFLAGS="-Wall -g -ggdb -O0 $DFLAGS -I/usr/include -I/usr/local/include -I/usr/include "
LDFLAGS="-lm"


AM_PROG_AR
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL
LT_INIT([static])

AC_PROG_INSTALL

echo " ------------------------------ "
echo ""
echo "   CFLAGS = $CFLAGS"
echo " CXXFLAGS = $CFLAGS"
echo "  LDFLAGS = $LDFLAGS"
echo ""
echo " ------------------------------ "

AC_CONFIG_FILES([
        Makefile
        src/Makefile
        tests/Makefile
])

AC_OUTPUT

