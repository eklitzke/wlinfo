#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([wlinfo], [0.1], [evan@eklitzke.org])
AC_CONFIG_SRCDIR([wlinfo.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([dist-bzip2 foreign subdir-objects -Wall -Werror])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT32_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_MALLOC

PKG_CHECK_MODULES([WAYLAND], [wayland-client], [], [])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
