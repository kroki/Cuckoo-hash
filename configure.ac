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
                  dist-bzip2 no-dist-gzip color-tests])

AC_PREFIX_DEFAULT([/usr/local])

AC_CONFIG_SRCDIR([src/Makefile.am])

LT_INIT

AC_PROG_MAKE_SET
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_CXX_C_O

AC_CHECK_FUNCS([mallinfo])

AC_LANG_PUSH([C++])

AC_MSG_CHECKING([whether $CXX runtime has std::unordered_map])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM([#include <unordered_map>],
                   [std::unordered_map<int, int> cont;])],
  [cxx_unordered_map=yes],
  [save_CXX=$CXX
   CXX="$CXX -std=c++0x"
   AC_COMPILE_IFELSE(
     [AC_LANG_PROGRAM([#include <unordered_map>],
                      [std::unordered_map<int, int> cont;])],
     [cxx_unordered_map='with -std=c++0x'],
     [CXX=$save_CXX
      cxx_unordered_map=no])])
AC_MSG_RESULT([$cxx_unordered_map])
AM_CONDITIONAL([HAVE_UNORDERED_MAP], [test x"$cxx_unordered_map" != x"no"])

AM_COND_IF([HAVE_UNORDERED_MAP],
  [AC_CACHE_CHECK([whether $CXX has std::__unordered_map<..., cache>],
    [ac_cv_cxx_unordered_map_cache],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM([#include <unordered_map>],
                       [std::__unordered_map<int, int,
                             std::hash<int>,
                             std::equal_to<int>,
                             std::allocator<std::pair<int, int> >,
                             true> cont;])],
      [ac_cv_cxx_unordered_map_cache=yes],
      [ac_cv_cxx_unordered_map_cache=no])])])
AM_CONDITIONAL([HAVE_UNORDERED_MAP_CACHE],
               [test x"$ac_cv_cxx_unordered_map_cache" != x"no"])

AC_LANG_POP

XPROBES

AC_CACHE_SAVE

AC_CONFIG_FILES([
Makefile
src/Makefile
test/Makefile
])
AC_CONFIG_FILES([stamp-h], [echo timestamp > stamp-h])

AC_OUTPUT
