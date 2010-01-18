#! /bin/sh

/bin/sh ./version.sh
test -d m4 || mkdir m4
autoreconf --install
