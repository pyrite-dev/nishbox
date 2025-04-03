TARGET = libnishbox.a
OBJS = nb_version.o nb_core.o nb_draw.o nb_log.o nb_font.o nb_math.o nb_physics.o nb_mesh.o nb_model.o nb_texture.o
OBJS += $(DRIVER)/nb_driver.o $(DRIVER)/nb_graphic.o
OBJS += $(DRIVER)/$(BACKEND)/nb_draw.o
OBJS += nb_stb_image.o

include ../common.mk

-include ext_lua.mk

$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)

nb_stb_image.c: ../external/stb/stb_image.h
