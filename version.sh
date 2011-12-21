#! /bin/sh

if test -d .git; then
    TAG=`git describe --dirty 2>/dev/null`
    if [ $? != 0 ]; then
        COUNT=$[$(git rev-list --count HEAD) - 1]
        TAG="0.0-$COUNT-g$(git describe --dirty --always)"
    fi
    TAG=`echo $TAG | sed -e '/-.*-/! s/\(-\|$\)/-0\1/; s/-/_/g; s/_/-/'`
    echo "m4_define([VERSION_STRING], [$TAG])" > version.m4.tmp
    if test -e version.m4 && cmp -s version.m4.tmp version.m4; then
        rm version.m4.tmp
    else
        mv version.m4.tmp version.m4
    fi
fi
