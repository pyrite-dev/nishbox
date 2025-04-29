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

## Note

*nix ones are tested on NetBSD/amd64 and Debian GNU/Linux 12 x86_64.

MSVC ones are tested on VS2008/VS2010.
