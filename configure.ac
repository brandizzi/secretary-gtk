AC_INIT([secretary-gtk], [0.1.1dev], [brandizzi@gmail.com])
AC_PREREQ([2.68])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CC_C99
AM_GNU_GETTEXT([external])
AC_CONFIG_SRCDIR([secretary.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile po/Makefile.in])

PKG_CHECK_MODULES([GTK], [gtk+-2.0])
PKG_CHECK_MODULES([SECRETARY], [libsecretary-0.1])
AC_CHECK_FUNCS([setlocale])
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h string.h])

AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memmove memset setlocale])
AC_DEFINE([_XOPEN_SOURCE], 500, [For using strptime])

AC_OUTPUT
