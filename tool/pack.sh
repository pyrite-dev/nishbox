#!/bin/sh

rm -rf nishbox
rm -rf nishbox.zip
mkdir -p nishbox/
cp bin/*/*/*.exe ./nishbox/
cp engine/bin/*/*/*.exe ./nishbox/
cp engine/lib/*/*/*.dll ./nishbox/
cp base.pak ./nishbox/
zip -rv nishbox.zip nishbox
rm -rf nishbox
