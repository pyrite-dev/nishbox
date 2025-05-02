#!/bin/sh
exec clang-format --verbose -i `find src "(" -name "*.c" -or -name "*.h" ")" 
