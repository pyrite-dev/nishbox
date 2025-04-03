TARGET = libnishbox.a
OBJS = nb_version.o nb_core.o nb_draw.o nb_log.o nb_font.o nb_math.o nb_physics.o nb_mesh.o nb_model.o nb_texture.o
OBJS += nb_$(DRIVER)_driver.o
OBJS += nb_$(BACKEND)_draw.o
OBJS += nb_stb_image.o

include ../common.mk

-include ext_lua.mk

$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)

nb_stb_image.c nb_draw.c: ext_stb_image.h

ext_stb_image.h:
	wget https://github.com/nothings/stb/raw/refs/heads/master/stb_image.h -O $@
