#!/bin/sh
ODE_VERSION=0.13

BASE=`pwd`

mkdir -p contrib
cd contrib

if [ -d cmake-files ]; then
	cd cmake-files
	git pull
	cd ..
else
	git clone https://github.com/nishiowo/cmake cmake-files --depth=1
fi

if [ ! -d ode-${ODE_VERSION} ]; then
	wget https://sourceforge.net/projects/opende/files/ODE/${ODE_VERSION}/ode-${ODE_VERSION}.tar.gz/download -O - | tar xvzf -
fi
cd ode-${ODE_VERSION}
if [ ! -f .configured ]; then
	./configure --host=${ARCH}-w64-mingw32 --prefix=/ --disable-demos --without-drawstuff --enable-shared || exit 1
	touch .configured
fi
if [ ! -f .made ]; then
	${MAKE} -j4 || exit 1
	touch .made
fi
if [ ! -f .installed ]; then
	${MAKE} install DESTDIR=${BASE}/deps
	touch .installed
fi
cd ..

if [ -d pawn ]; then
	cd pawn
	git pull
	cd build
else
	git clone https://github.com/nishiowo/pawn --depth=1
	cd pawn
	mkdir build
	cd build
fi
if [ ! -f ../.configured ]; then
	cmake -DCMAKE_TOOLCHAIN_FILE=../../cmake-files/windows.cmake -DARCH=${ARCH} .. -DCMAKE_INSTALL_PREFIX=/ || exit 1
	touch ../.configured
fi
if [ ! -f ../.made ]; then
	${MAKE} -j4 || exit 1
	touch ../.made
fi
if [ ! -f ../.installed ]; then
	${MAKE} install DESTDIR=${BASE}/deps
	touch ../.installed
fi
cd ../..

cd ..

${MAKE} PLATFORM=win${BITS}
cp `${MAKE} PLATFORM=win${BITS} print-deps` ./
