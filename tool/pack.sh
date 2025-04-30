#!/bin/sh

TARGET=${1:-"*"}
DIR=${2:-nishbox}
OUTPUT=${3:-$DIR.zip}

rm -rf $DIR
rm -rf $OUTPUT
mkdir -p $DIR
mkdir -p $DIR/bin
mkdir -p $DIR/lib
mkdir -p $DIR/include

cat > $DIR/README.txt << EOF
 - GoldFish DLL
 - NishBox executables
 - GoldFish executables
are in bin/

 - GoldFish headers
is in include/

 - GoldFish .lib
is in lib/

Packed at `date`
EOF
cp engine/LICENSE $DIR/LICENSE.txt

cp -rf engine/include/* $DIR/include/
cp engine/lib/*/$TARGET/*.lib $DIR/lib/
cp bin/*/$TARGET/*.exe ./$DIR/bin/
cp engine/bin/*/$TARGET/*.exe ./$DIR/bin/
cp engine/lib/*/$TARGET/*.dll ./$DIR/bin/
cp base.pak ./$DIR/bin/

rm -f ./$DIR/include/*.txt

zip -zrv $OUTPUT $DIR << EOF
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
rm -rf $DIR
