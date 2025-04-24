#!/bin/sh

rm -rf nishbox
rm -rf nishbox.zip
mkdir -p nishbox
mkdir -p nishbox/bin
mkdir -p nishbox/lib
mkdir -p nishbox/include

cat > nishbox/README.txt << EOF
 - GoldFish DLL
 - NishBox executables
 - GoldFish executables
are in bin/

 - GoldFish headers
is in include/

 - GoldFish .lib
is in lib/
EOF
cp engine/LICENSE nishbox/LICENSE.txt

cp -rf engine/include/* nishbox/include/
cp engine/lib/*/*/*.lib nishbox/lib/
cp bin/*/*/*.exe ./nishbox/bin/
cp engine/bin/*/*/*.exe ./nishbox/bin/
cp engine/lib/*/*/*.dll ./nishbox/bin/
cp base.pak ./nishbox/bin/

rm -f ./nishbox/include/*.txt

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
