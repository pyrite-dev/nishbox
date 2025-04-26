#!/bin/sh
FILES="font scripts"
cd data
if [ "x${WINE}" = "x" ]; then
	exec ../engine/bin/*/*/pack ../base.pak $FILES
else
	exec ${WINE} ../engine/bin/*/*/pack.exe ../base.pak $FILES
fi
