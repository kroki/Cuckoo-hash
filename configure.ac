dnl Process this file with autoconf to produce a configure script.
dnl
dnl To bootstrap run './bootstrap.sh'.
dnl

AC_PREREQ(2.59)
m4_include([version.m4])
AC_INIT([Cuckoo hash], [VERSION_STRING], [tomash.brechko@gmail.com],
        [cuckoo_hash])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.9.2 -Wall no-define subdir-objects
                  dist-bzip2 no-dist-gzip])

AC_PREFIX_DEFAULT([/usr/local])

AC_CONFIG_SRCDIR([src/Makefile.am])

LT_INIT

AC_PROG_MAKE_SET
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_CC_C_O

AC_CACHE_SAVE

AC_CONFIG_FILES([
Makefile
src/Makefile
])
AC_CONFIG_FILES([stamp-h], [echo timestamp > stamp-h])

AC_OUTPUT
