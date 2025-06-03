#!/bin/sh
set -e
mkdir -p /usr/local/lib
mkdir -p /usr/local/bin
mkdir -p /usr/local/share/nishbox
cp ./engine/lib/*/*/*.so /usr/local/lib/ >/dev/null 2>&1 || echo 'Failed to copy engine, but it is okay'
cp ./bin/*/*/nishbox /usr/local/bin/
cp ./base.pak /usr/local/share/nishbox/
echo 'Installation success'
