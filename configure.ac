AC_INIT([secretary-gtk], [0.1.1dev], [brandizzi@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CC_C99
AM_GNU_GETTEXT([external])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile po/Makefile.in])

PKG_CHECK_MODULES([GTK], [gtk+-2.0])
PKG_CHECK_MODULES([SECRETARY], [libsecretary-0.1])
AC_CHECK_FUNCS([setlocale])
AC_CHECK_HEADERS([libintl.h])

AC_OUTPUT
