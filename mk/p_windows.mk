WINDOWS = NO
ifeq ($(PLATFORM),win32)
TARGET_PREFIX = i686-w64-mingw32-
WINDOWS = YES
endif

ifeq ($(PLATFORM),win64)
TARGET_PREFIX = x86_64-w64-mingw32-
WINDOWS = YES
endif

ifeq ($(WINDOWS),YES)
ODE_CFLAGS = -I../deps/include
ODE_LIBS = -L../deps/lib -lode
AMX_CFLAGS = -I../deps/include
AMX_LIBS = -L../deps/lib -lamx
PAWNC_CFLAGS = -I../deps/include
PAWNC_LIBS = -L../deps/lib -lpawnc
GL_CFLAGS =
GL_LIBS = -lopengl32 -lgdi32

BACKEND = WGL

EXEC = .exe
endif
