#! /bin/sh

if test -d .git; then
    TAG=`git describe HEAD`
    if git diff --quiet HEAD; then
        DIRTY=
    else
        DIRTY=-dirty
    fi
    echo "m4_define([VERSION_STRING], [$TAG$DIRTY])" > version.m4.tmp
    if test -e version.m4 && cmp -s version.m4.tmp version.m4; then
        rm version.m4.tmp
    else
        mv version.m4.tmp version.m4
    fi
fi
