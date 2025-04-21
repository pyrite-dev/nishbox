#!/bin/sh
if [ "x${WINE}" = "x" ]; then
	exec ./engine/bin/*/*/pack -d data base.pak
else
	exec ${WINE} ./engine/bin/*/*/pack.exe -d data base.pak
fi
