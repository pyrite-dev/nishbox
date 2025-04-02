ifeq ($(PLATFORM),win32)
TARGET_PREFIX = i686-w64-mingw32-
WINDOWS = YES
endif

ifeq ($(PLATFORM),win64)
TARGET_PREFIX = x86_64-w64-mingw32-
WINDOWS = YES
endif

ifeq ($(WINDOWS),YES)
BACKEND = WGL

ODE_CFLAGS = -I../deps/include
ODE_LIBS = -L../deps/lib -lode
ifeq ($(BACKEND),WGL)
GL_CFLAGS =
GL_LIBS = -lopengl32 -lglu32 -lgdi32
endif
ifeq ($(BACKEND),GLFW)
GL_CFLAGS = -I../deps/include
GL_LIBS = -L../deps/lib -lglfw -lopengl32 -lglu32 -lgdi32
endif
SOCKET_LIBS = -lws2_32

EXEC = .exe
endif
