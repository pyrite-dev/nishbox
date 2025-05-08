# Building the game

Building NishBox is simple.

## *nix

1. Run `premake5 gmake --opengl=x11` or `premake5 gmake --opengl=rgfw`.
2. Run `gmake` or `make`, depending on the platform.

## MSVC

1. Run `premake5 vs<version> --opengl=gdi --cc=msc` or `premake5 vs<version> --opengl=rgfw --cc=msc`.
   
   `<version>` depends on the Visual Studio version. On VS2008, it should be `2008`.
   
   GLFW backend is untested.
2. Run `msbuild NishBox.sln`.

## Classic Mac OS

1. Install [Retro68](https://github.com/autc04/Retro68)
2. Run `premake5 gmake --opengl=agl`
3. copy `engine/external/OpenGLOnMacOS9/lib/libgl.a` to your Retro68 toolchain's lib directory, making sure to capitalize it when you do so (i.e. `/opt/Retro68/toolchain/powerpc-apple-macos/lib/libGL.a`) 
3. Run `CC=powerpc-apple-macos-gcc CXX=powerpc-apple-macos-g++ make -j$(nproc) config=debug_classicmacos`
## Note

\*nix ones are tested on NetBSD/amd64 and Debian GNU/Linux 12 x86_64.

MSVC ones are tested on VS2008/VS2010.

Classic Mac OS requires System 8.6+ or above and is only avaliable for PowerPC.
