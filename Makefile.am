SUBDIRS = src tests


Android.mk: Makefile.am
	@androgenizer -:PROJECT lib3dmath \
    -:REL_TOP $(top_srcdir)/src -:ABS_TOP $(abs_top_srcdir)/src \
    -:SHARED lib3dmath \
    -:SOURCES src/shaders.c \
    -:CFLAGS -std=c99 -Wall -O3 \
    -:LDFLAGS -lGL \
    > $@

android: Android.mk
	ndk-build V=1 NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_OUT=./lib

android-clean:
	@ndk-build clean NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_OUT=./lib
	echo "Removing Android.mk"; rm -f Android.mk

