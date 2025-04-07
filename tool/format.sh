#!/bin/sh
exec clang-format --verbose -i `find engine src -name "*.c" -or -name "*.h"`
