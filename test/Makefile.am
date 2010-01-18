## Process this file with automake to produce Makefile.in.
##

include $(top_srcdir)/Makefile.common


TESTS =						\
	cuckoo_hash.sh


EXTRA_DIST =					\
	test.h					\
	cuckoo_hash.sh


check_PROGRAMS =				\
	cuckoo_hash				\
	std-map


cuckoo_hash_SOURCES =				\
	test.cpp


cuckoo_hash_LDFLAGS =				\
	../src/libcuckoo_hash.la


std_map_SOURCES =				\
	test.cpp


std_map_CPPFLAGS =				\
	-DMAP


if HAVE_UNORDERED_MAP


check_PROGRAMS +=				\
	std-unordered_map


std_unordered_map_SOURCES =			\
	test.cpp


std_unordered_map_CPPFLAGS =			\
	-DUNORDERED_MAP


if HAVE_UNORDERED_MAP_CACHE


check_PROGRAMS +=				\
	std-unordered_map-cache


std_unordered_map_cache_SOURCES =		\
	test.cpp


std_unordered_map_cache_CPPFLAGS =		\
	-DUNORDERED_MAP -DUSE_CACHE


endif  # HAVE_UNORDERED_MAP_CACHE


endif  # HAVE_UNORDERED_MAP
