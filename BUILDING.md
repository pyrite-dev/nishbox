# Building the game

Building NishBox is simple.

## *nix

1. Run `premake5 gmake --opengl=glx` or `premake5 gmake --opengl=glfw`.
2. Run `gmake` or `make`, depending on the platform.

## MSVC

1. Run `premake5 gmake --opengl=wgl --cc=msc` or `premake5 gmake --opengl=glfw --cc=msc`.
   GLFW backend is untested.
2. Run `msbuild NishBox.sln`.