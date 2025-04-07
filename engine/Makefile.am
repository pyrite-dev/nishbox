include $(top_srcdir)/common-automake.mk
lib_LIBRARIES = libnishbox.a
libnishbox_a_SOURCES = \
		       nb_core.c nb_draw_common.c nb_font.c nb_log.c nb_math.c nb_mesh.c nb_model.c nb_physics.c nb_stb_image.c nb_texture.c nb_version.c \
		       graphic/@NB_DRIVER@/nb_driver.c graphic/@NB_DRIVER@/nb_graphic.c \
		       graphic/@NB_DRIVER@/@NB_BACKEND@/nb_draw.c \
		       thread/@NB_THREAD@/nb_thread.c \
		       $(LUASRC) $(ZLIBSRC)
#AUTOGEN
# DO NOT EDIT BELOW THIS COMMENT!!!
# They are auto-generated using /tool/autogen.sh
LUASRC = ../external/lua/lapi.c ../external/lua/lauxlib.c ../external/lua/lbaselib.c ../external/lua/lcode.c ../external/lua/lcorolib.c ../external/lua/lctype.c ../external/lua/ldblib.c ../external/lua/ldebug.c ../external/lua/ldo.c ../external/lua/ldump.c ../external/lua/lfunc.c ../external/lua/lgc.c ../external/lua/linit.c ../external/lua/liolib.c ../external/lua/llex.c ../external/lua/lmathlib.c ../external/lua/lmem.c ../external/lua/loadlib.c ../external/lua/lobject.c ../external/lua/lopcodes.c ../external/lua/loslib.c ../external/lua/lparser.c ../external/lua/lstate.c ../external/lua/lstring.c ../external/lua/lstrlib.c ../external/lua/ltable.c ../external/lua/ltablib.c ../external/lua/ltests.c ../external/lua/ltm.c ../external/lua/lundump.c ../external/lua/lutf8lib.c ../external/lua/lvm.c ../external/lua/lzio.c ../external/lua/onelua.c
ZLIBSRC = ../external/zlib/adler32.c ../external/zlib/compress.c ../external/zlib/crc32.c ../external/zlib/deflate.c ../external/zlib/gzclose.c ../external/zlib/gzlib.c ../external/zlib/gzread.c ../external/zlib/gzwrite.c ../external/zlib/infback.c ../external/zlib/inffast.c ../external/zlib/inflate.c ../external/zlib/inftrees.c ../external/zlib/trees.c ../external/zlib/uncompr.c ../external/zlib/zutil.c
