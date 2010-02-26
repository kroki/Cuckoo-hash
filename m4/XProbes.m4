# XPROBES()
#
# Add --with-xprobes[=DIR] option to configure.  When given, update
# LIBS, CPPFLAGS and LDFLAGS.  Also define WITH_XPROBES CPP macro, and
# WITH_XPROBES automake conditional.
#
AC_DEFUN([XPROBES],
  [AC_ARG_WITH([xprobes],
    [AC_HELP_STRING([--with-xprobes@<:@=DIR@:>@],
      [use XProbes framework @<:@default=no@:>@.  You can provide DIR
       prefix to where XProbes is installed.])],
    [],
    [with_xprobes=no])
   AM_CONDITIONAL([WITH_XPROBES], [test x"$with_xprobes" != x"no"])
   AM_COND_IF([WITH_XPROBES],
     [AC_DEFINE([WITH_XPROBES], [1], [Use XProbes.])
      LIBS="$LIBS -lxprobes"
      AS_IF([test x"$with_xprobes" != x"yes"],
        [CPPFLAGS="$CPPFLAGS -I$with_xprobes/include"
         LDFLAGS="$LDFLAGS -L$with_xprobes/lib64 -L$with_xprobes/lib"])
      AC_TRY_LINK([#include <xprobes/site.h>],
        [XPROBES_SITE(xprobes, site, (void), ());],
        [],
        [AS_IF([test x"$with_xprobes" != x"yes"],
          [xprobes_dir=$with_xprobes],
          [xprobes_dir='standard locations'])
         AC_MSG_ERROR([no XProbes installation is found in $xprobes_dir])])])])
