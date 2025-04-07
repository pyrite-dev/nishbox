#!/bin/sh
LUASRC=""
ZLIBSRC=""

cd engine

for i in `ls -d ../external/lua/*.c`; do
	if [ ! "$i" = "../external/lua/lua.c" ]; then
		LUASRC="$LUASRC $i"
	fi
done

for i in `ls -d ../external/zlib/*.c`; do
	ZLIBSRC="$ZLIBSRC $i"
done

mv Makefile.am Makefile.am.old
while IFS= read -r a; do
	echo "$a" >> Makefile.am
	if [ "$a" = "#AUTOGEN" ]; then
		break
	fi
done < Makefile.am.old
echo "# DO NOT EDIT BELOW THIS COMMENT!!!" >> Makefile.am
echo "# They are auto-generated using /tool/autogen.sh" >> Makefile.am
echo "LUASRC =$LUASRC" >> Makefile.am
echo "ZLIBSRC =$ZLIBSRC" >> Makefile.am

rm -f Makefile.am.old
