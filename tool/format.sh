#!/bin/sh
exec clang-format --verbose -i `find engine src "(" -name "*.c" -or -name "*.h" ")" -and -not -path "engine/external/*"` engine/external/jar/*.h
