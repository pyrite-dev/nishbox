# Building the Game

Building NishBox is simple.

## *nix

1. Run `premake5 gmake --opengl=x11` or `premake5 gmake --opengl=rgfw`.
2. Run `gmake` or `make`, depending on your platform.

## MSVC

1. Run `premake5 vs<version> --opengl=gdi --cc=msc` or `premake5 vs<version> --opengl=rgfw --cc=msc`.
   Replace `<version>` with your Visual Studio version (e.g., `2008` for VS2008).
   Note: The RGFW backend is untested on Windows.
2. Run `msbuild NishBox.sln`.

## Classic Mac OS

1. Install [Retro68](https://github.com/autc04/Retro68).
2. Run `premake5 gmake --opengl=agl`.
3. Copy `engine/external/OpenGLOnMacOS9/lib/libgl.a` to your Retro68 toolchain’s lib directory.
   Make sure to capitalize the filename:
   `/opt/Retro68/toolchain/powerpc-apple-macos/lib/libGL.a`.
4. Run:
   `CC=powerpc-apple-macos-gcc CXX=powerpc-apple-macos-g++ make -j$(nproc) config=debug_classicmacos`

## Notes

* \*nix builds have been tested on NetBSD/amd64 and Debian GNU/Linux 12 (x86\_64).
* MSVC builds have been tested with VS2008 and VS2010.
* Classic Mac OS builds require System 8.6 or later and only work on PowerPC.

## Final Step

After building NishBox, make sure to run the following command:
Without this step, NishBox will crash with an error.

```sh
./engine/bin/*/*/pack -d data base.pak
```

