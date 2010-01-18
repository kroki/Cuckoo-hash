## Process this file with automake to produce Makefile.in.
##

include $(top_srcdir)/Makefile.common


include_HEADERS =				\
	cuckoo_hash.h


lib_LTLIBRARIES =				\
	libcuckoo_hash.la


libcuckoo_hash_la_SOURCES =			\
	cuckoo_hash.c				\
	lookup3.c


## Here's an excerpt from 'info libtool versioning updating' on when
## and how to update shared library version:
##
##   1. Start with version information of `0:0:0' for each libtool library.
##
##   2. Update the version information only immediately before a public
##      release of your software.  More frequent updates are unnecessary,
##      and only guarantee that the current interface number gets larger
##      faster.
##
##   3. If the library source code has changed at all since the last
##      update, then increment REVISION (`C:R:A' becomes `C:R+1:A').
##
##   4. If any interfaces have been added, removed, or changed since the
##      last update, increment CURRENT, and set REVISION to 0.
##
##   5. If any interfaces have been added since the last public release,
##      then increment AGE.
##
##   6. If any interfaces have been removed since the last public release,
##      then set AGE to 0.

libcuckoo_hash_la_LDFLAGS = -version-info 0:0:0
