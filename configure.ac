AC_INIT([libevio], [1.0], [InnovAnon-Inc@protonmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 src/libevio.pc
 src/evio-test.pc
])

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE([use-submodules],
    AS_HELP_STRING([--enable-use-submodules], [Enable use submodules]))
AM_CONDITIONAL([USE_SUBMODULES], [test x"$enable_use_submodules" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])

AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([ev.h])
#AC_CHECK_HEADERS([glitter.h restart.h])

#AC_CHECK_LIB([stdlib],[])
AC_CHECK_LIB([ev],[ev_run,ev_io_init,ev_io_start,ev_io_stop,ev_break])
#AC_CHECK_LIB([restart],[r_read,r_write,r_close])

PKG_CHECK_MODULES([GLITTER],[glitter],,)
PKG_CHECK_MODULES([RESTART],[librestart],,)

INNOVANON_WARNINGS([])

AC_OUTPUT
