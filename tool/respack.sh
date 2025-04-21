#!/bin/sh
old="`pwd`"

rm -rf /tmp/respack
mkdir -p /tmp/respack
cp -rf music /tmp/respack/music
cp -rf font /tmp/respack/font
cp font/helvR24.bdf /tmp/respack/font/default.bdf

exec ./engine/bin/*/*/pack -d /tmp/respack base.pak
