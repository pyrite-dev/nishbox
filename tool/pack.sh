#!/bin/sh

rm -rf nishbox
rm -rf nishbox.zip
mkdir -p nishbox/bin
mkdir -p nishbox/lib
cp `./tool/deps.sh` ./nishbox/bin/
cp bin/*/*/nishbox.exe ./nishbox/bin/
${STRIP} ./nishbox/bin/*.dll ./nishbox/bin/*.exe
zip -rv nishbox.zip nishbox
rm -rf nishbox
