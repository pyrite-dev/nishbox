#!/bin/sh
PACK="music font texture"
if [ "x${WINE}" = "x" ]; then
	exec ./engine/bin/*/*/pack base.pak ${PACK}
else
	exec ${WINE} ./engine/bin/*/*/pack.exe base.pak ${PACK}
fi
