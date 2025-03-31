AC_PREREQ([2.69])
AC_INIT([egt-samples],[1.7-rc1])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_MACRO_DIR([m4])
AC_USE_SYSTEM_EXTENSIONS
AC_CANONICAL_TARGET
PKG_PROG_PKG_CONFIG

AM_INIT_AUTOMAKE([1.10 foreign subdir-objects])

# Enable quiet compiles on automake 1.11.
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Initialize libtool
LT_PREREQ([2.2])
LT_INIT([win32-dll])

AC_LANG(C++)
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX([17], [noext])
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_UINT32_T

AC_MSG_CHECKING([for native ARM])
case "$host" in
  arm*)
      egt_cpu_arm=yes
      ;;
  *)
      egt_cpu_arm=no
      ;;
esac
AC_MSG_RESULT([$egt_cpu_arm])
AM_CONDITIONAL(CPU_ARM, test "$egt_cpu_arm" = "yes")

AX_PTHREAD([LIBS="$PTHREAD_LIBS $LIBS"
            CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
            CXXFLAGS="$CXXFLAGS $PTHREAD_CFLAGS"],
            AC_MSG_ERROR(Can not find pthreads.  This is required.))

AC_ARG_ENABLE(rtti,
  AS_HELP_STRING([--disable-rtti], [Disable RTTI]))
AM_CONDITIONAL(DISABLE_RTTI, test x"$enable_rtti" = x"no")
if test x"$enable_rtti" = x"no"; then
  AC_DEFINE(DISABLE_RTTI, 1, [define if not using RTTI])
  CXXFLAGS="$CXXFLAGS -fno-rtti"
fi

PKG_CHECK_MODULES(LIBEGT, [libegt >= 1.11-rc1], [], [
   AC_MSG_ERROR(libegt not found.  This is required.)
])

PKG_CHECK_MODULES(JSONCPP, [jsoncpp], [have_jsoncpp=yes], [have_jsoncpp=no])
if test "x${have_jsoncpp}" = xyes; then
   AC_DEFINE(HAVE_JSONCPP, 1, [Have jsoncpp support])
fi
AM_CONDITIONAL([HAVE_JSONCPP], [test "x${have_jsoncpp}" = xyes])

save_CXXFLAGS="${CXXFLAGS}"
save_CPPFLAGS="${CPPFLAGS}"
save_LDFLAGS="${LDFLAGS}"
CXXFLAGS="${LIBEGT_CFLAGS} ${CXXFLAGS}"
CPPFLAGS="${LIBEGT_CFLAGS} ${CPPFLAGS}"
LDFLAGS="${LIBEGT_LIBS} ${LDFLAGS}"

AC_CHECK_HEADERS([egt/network/http.h], have_egt_network_http_h=yes, have_egt_network_http_h=no)
AM_CONDITIONAL([HAVE_EGT_NETWORK_HTTP_H], [test "x${have_egt_network_http_h}" = xyes])

AC_CHECK_HEADERS([egt/video.h], have_egt_video_h=yes, have_egt_video_h=no)
AM_CONDITIONAL([HAVE_EGT_VIDEO_H], [test "x${have_egt_video_h}" = xyes])

CXXFLAGS="${save_CXXFLAGS}"
CPPFLAGS="${save_CPPFLAGS}"
LDFLAGS="${save_LDFLAGS}"

AC_CONFIG_FILES([Makefile
		external/Makefile
		icon/Makefile
		drop/Makefile
		ragdoll/Makefile
		gallery/Makefile
		weather/Makefile
		water/Makefile
		newsfeed/Makefile
		layout/Makefile
		brick/Makefile
		AngryMeatballs/Makefile])
AC_OUTPUT
