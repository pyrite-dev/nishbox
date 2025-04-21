#!/bin/sh
old="`pwd`"

rm -rf /tmp/respack
mkdir -p /tmp/respack
cp -rf music /tmp/respack/music

exec ./engine/bin/*/*/pack -d /tmp/respack resource.pak
