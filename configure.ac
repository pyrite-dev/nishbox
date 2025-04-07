AC_INIT([NishBox], [1.0.0])
AM_INIT_AUTOMAKE([subdir-objects foreign])

AC_ARG_WITH([backend], AS_HELP_STRING([--with-backend=glx|wgl|glfw], [Select backend]))

AM_PROG_AR
AC_PROG_RANLIB
AC_PROG_CC

PKG_PROG_PKG_CONFIG

NB_DRIVER=OPENGL
NB_BACKEND=

AS_IF([test "x$with_backend" = "xglx"], [
	PKG_CHECK_MODULES([GL_MORE], [x11])
	PKG_CHECK_MODULES([GL], [gl])
	PKG_CHECK_MODULES([GLU], [glu])
	NB_BACKEND=GLX
])

AS_IF([test "x$with_backend" = "xwgl"], [
	:
	GL_MORE_LIBS="-lgdi32"
	GL_LIBS="-lopengl32"
	GLU_LIBS="-lglu32"
	NB_BACKEND=WGL
])

AS_IF([test "x$with_backend" = "xglfw"], [
	PKG_CHECK_MODULES([GL], [glfw3])
	PKG_CHECK_MODULES([GLU], [glu])
	NB_BACKEND=GLFW
])

PKG_CHECK_MODULES([ODE], [ode])

AS_IF([test "x$NB_BACKEND" = "x"], [
	AS_ECHO("Backend cannot be empty; see --help")
	AS_EXIT(1)
])

AC_CHECK_HEADER(unistd.h,:,:)
AC_CHECK_HEADER(stdarg.h,:,:)

AC_CHECK_LIB(stdc++,main,STDCXX_LIBS="-lstdc++",:)

AC_CHECK_LIB(ws2_32,socket,SOCKET_LIBS="-lws2_32",:)
AC_CHECK_LIB(socket,socket,SOCKET_LIBS="-lsocket",:)

AC_CHECK_LIB(dl,dlopen,DL_LIBS="-ldl",:)
AC_CHECK_LIB(m,log,MATH_LIBS="-lm",:)

AC_CHECK_LIB(kernel32,CreateThread,[
	NB_THREAD="WIN32"
],[
	AC_CHECK_LIB(pthread,pthread_create,[
		NB_THREAD="POSIX"
		THREAD_LIBS="-lpthread"
	],[
		AS_ECHO("Could not detect thread")
		AS_EXIT(1)
	])
])

NB_CPPFLAGS="$GL_MORE_CFLAGS $GL_CFLAGS $GLU_CFLAGS $ODE_CFLAGS"
NB_LDADD="$STDCXX_LIBS $GL_MORE_LIBS $SOCKET_LIBS $GL_LIBS $GLU_LIBS $ODE_LIBS $THREAD_LIBS $DL_LIBS $MATH_LIBS"

AC_SUBST(NB_THREAD)
AC_SUBST(NB_DRIVER)
AC_SUBST(NB_BACKEND)
AC_SUBST(NB_CPPFLAGS)
AC_SUBST(NB_LDADD)

LUA_SOURCES=""
for i in `ls -d external/lua/*.c`; do
	LUA_SOURCES="$LUA_SOURCES ../$i"
done
AC_SUBST(LUA_SOURCES)

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	engine/Makefile
])
AC_OUTPUT

AS_ECHO("----------------------------------")
AS_ECHO("Driver  : $NB_DRIVER")
AS_ECHO("Backend : $NB_BACKEND")
AS_ECHO("Thread  : $NB_THREAD")
AS_ECHO("----------------------------------")
