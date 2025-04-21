#!/bin/sh

rm -rf nishbox
rm -rf nishbox.zip
mkdir -p nishbox/bin/
mkdir -p nishbox/lib/
mkdir -p nishbox/include/
cp -rf engine/include/* nishbox/include/
cp engine/lib/*/*/*.lib nishbox/lib/
cp bin/*/*/*.exe ./nishbox/bin/
cp engine/bin/*/*/*.exe ./nishbox/bin/
cp engine/lib/*/*/*.dll ./nishbox/bin/
cp base.pak ./nishbox/
zip -zrv nishbox.zip nishbox << EOF
+---------------------------------------+
| NishBox/GoldFish distribution zipfile |
| Contains:                             |
|    1. NishBox executables             |
|    2. GoldFish executables            |
|    3. GoldFish development kit        |
|                                Enjoy! | 
+---------------------------------------+
.
EOF
rm -rf nishbox
