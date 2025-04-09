#!/bin/sh

CC=${CC:-${GCC_PREFIX}gcc}
OBJDUMP=${OBJDUMP:-${GCC_PREFIX}objdump}

solve () {
	path=""
	$OBJDUMP -p $1 | grep "DLL Name:" | rev | cut -d" " -f1 | rev | while read a; do
		if [ -e "./deps/bin/$a" ]; then
			path="./deps/bin/$a"
		else
			path="`$CC -print-file-name=$a`"
		fi
		if [ ! "x$path" = "x" ]; then
			if [ -e "$path" ]; then
				echo $path
				solve $path
			fi
		fi
	done
}

solve bin/*/*/nishbox.exe
