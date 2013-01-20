#! /usr/bin/env sh

set -o errexit -o nounset -o noclobber


if [ -d .git ]; then
    RC=0
    TAG=$(git describe --dirty 2>/dev/null) || RC=$?
    if [ $RC = 0 ]; then
        TAG=$(echo $TAG | awk '{
            tag = $0
            if (match(tag, /^([^-]+-)([0-9]+)(.*)/, m))
              {
                print m[1] m[2] + 1 m[3]
              }
            else
              {
                sub(/(-dirty)?$/, "-1&", tag)
                print tag
              }
        }')
    else
        COUNT=$[$(git rev-list --count HEAD 2>/dev/null || echo 0) + 1]
        GIT=$(git describe --dirty --always 2>/dev/null || :)
        if [ x"$GIT" != x"" ]; then
            GIT="-g$GIT"
        else
            GIT="-dirty"
        fi
        TAG="0.0-$COUNT$GIT"
    fi
    TAG=$(echo $TAG | sed -e 's/-/_/g; s/_/-/')

    echo "m4_define([VERSION_STRING], [$TAG])" >| version.m4.tmp
    if test -e version.m4 && cmp -s version.m4.tmp version.m4; then
        rm version.m4.tmp
    else
        mv version.m4.tmp version.m4
    fi
else
    if [ ! -e version.m4 ]; then
        echo "m4_define([VERSION_STRING], [0.0-1_dirty])" > version.m4
    fi
fi
