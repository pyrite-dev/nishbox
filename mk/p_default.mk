ifeq ($(PLATFORM),)
BACKEND = GLX

ODE_CFLAGS = `pkg-config --cflags ode`
ODE_LIBS = `pkg-config --libs ode`
AMX_CFLAGS = `pkg-config --cflags amx`
AMX_LIBS = `pkg-config --libs amx`
PAWNC_CFLAGS = `pkg-config --cflags pawnc`
PAWNC_LIBS = `pkg-config --libs pawnc`
ifeq ($(BACKEND),GLX)
GL_CFLAGS = `pkg-config --cflags gl` `pkg-config --cflags glu`
GL_LIBS = `pkg-config --libs gl` `pkg-config --libs glu`
endif
ifeq ($(BACKEND),GLFW)
GL_CFLAGS = `pkg-config --cflags glfw3` `pkg-config --cflags glu`
GL_LIBS = `pkg-config --libs glfw3` `pkg-config --libs glu`
endif
SOCKET_LIBS = 

EXEC =
endif
