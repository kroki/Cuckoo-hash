#! /usr/bin/env sh

set -o errexit -o nounset -o noclobber


SRCDIR=$(dirname "$0")
cd "$SRCDIR"
"$SHELL" ./version.sh
test -d m4 || mkdir m4
autoreconf --install
