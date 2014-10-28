/* src/lib3dmath-config.h.  Generated from lib3dmath-config.h.in by configure.  */
/* src/lib3dmath-config.h.in.  Generated from configure.ac by autoheader.  */


#ifndef _LIB3DMATH_H_
#define _LIB3DMATH_H_


/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* All scalar types are double. */
/* #undef LIB3DMATH_USE_DOUBLE */

/* All scalar types are float. */
#define LIB3DMATH_USE_FLOAT 0

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "lib3dmath"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "manvscode@manvscode.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "lib3dmath"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "lib3dmath 1.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "lib3dmath"

/* Define to the home page for this package. */
#define PACKAGE_URL "http://www.manvscode.com/"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.0"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "1.0"

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#define inline __inline

/* Define to `__restrict' if that's what the C compiler
   calls it, or to nothing if 'restrict' is not supported under any name.  */
#if _MSC_VER >= 1800
#define restrict __restrict
#endif

#if _MSC_VER >= 1800
#define __STDC_VERSION__  199901L
#endif

#if _MSC_VER >= 1800
#define snprintf sprintf_s
#endif


#ifndef __cplusplus
/* #undef inline */
#endif


#endif /* _LIB3DMATH_H_ */
