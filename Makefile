# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/18 21:24:52 by bkabbas           #+#    #+#              #
#    Updated: 2016/07/09 19:45:20 by Rakiah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libr3d.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OPTIMIZE = yes
PROF = no
DEBUG = no

# Paths
PATH_SDL2 = ../SDL2
PATH_RSTD = ../rstd
PATH_RMATH = ../rmath
PATH_PORNYGONZ = ../pornygonz
PATH_RCONTAINERS = ../rcontainers

PATH_HEADERS = includes
PATH_SRC = sources
PATH_SUB = input transform mesh loaders core_components .
PATH_OBJ = objects

# Dependencies
CFLAGS += -I $(PATH_SDL2)/includes
CFLAGS += -I $(PATH_RSTD)/includes
CFLAGS += -I $(PATH_RMATH)/includes
CFLAGS += -I $(PATH_PORNYGONZ)/includes
CFLAGS += -I $(PATH_RCONTAINERS)/includes

CFLAGS += -I $(PATH_HEADERS)

# Debug
ifeq ($(DEBUG), yes)
	CFLAGS += -g -O0
endif

# Prof
ifeq ($(PROF), yes)
	CFLAGS += -pg
endif

# Optimization
ifeq ($(OPTIMIZE), yes)
	CFLAGS += -O3
endif

vpath %.c $(addprefix $(PATH_SRC)/,$(PATH_SUB))

# Sources
CORE += core.c
CORE += utilities.c
CORE += resources.c
CORE += internal_behavior.c
CORE += error.c

LOADERS += loader.c
LOADERS += obj_loader.c
LOADERS += obj_model.c
LOADERS += rs_loader.c
LOADERS += ro_loader.c
LOADERS += bmp_loader.c

TRANSFORM += trs_manipulations.c
TRANSFORM += trs_operators_pos.c
TRANSFORM += trs_operators_rot.c
TRANSFORM += trs_operators_scale.c
TRANSFORM += trs_hierarchy.c

MESH += mesh_draw.c
MESH += mesh_inits.c

COMPONENTS += behaviour.c
COMPONENTS += texture.c
COMPONENTS += material.c
COMPONENTS += object.c
COMPONENTS += camera.c

INPUT += mouse_motion.c
INPUT += key_down.c
INPUT += key_up.c
INPUT += mouse_down.c
INPUT += mouse_up.c
INPUT += mouse_pos.c

KEYCODES += keycode_handler.c
KEYCODES += keycode_keypad.c
KEYCODES += keycode_alphabet.c
KEYCODES += keycode_special.c

SOURCES += $(CORE)
SOURCES += $(MESH)
SOURCES += $(LOADERS)
SOURCES += $(TRANSFORM)
SOURCES += $(COMPONENTS)
SOURCES += $(INPUT)
SOURCES += $(KEYCODES)

INCLUDES += r3d.h
INCLUDES += r3d_structs.h
INCLUDES += r3d_typedefs.h
INCLUDES += r3d_defines.h
INCLUDES += r3d_core.h
INCLUDES += r3d_camera.h
INCLUDES += r3d_mesh.h
INCLUDES += r3d_object.h
INCLUDES += r3d_material.h
INCLUDES += r3d_resources.h
INCLUDES += r3d_texture.h
INCLUDES += r3d_behaviour.h
INCLUDES += r3d_transform.h
INCLUDES += r3d_loader.h
INCLUDES += r3d_input.h
INCLUDES += r3d_enums.h

# Headers
HEADERS += $(addprefix $(PATH_HEADERS)/, $(INCLUDES))

# Objects
OBJECTS += $(addprefix $(PATH_OBJ)/, $(CORE:%.c=%.o))
OBJECTS += $(addprefix $(PATH_OBJ)/, $(MESH:%.c=%.o))
OBJECTS += $(addprefix $(PATH_OBJ)/, $(LOADERS:%.c=%.o))
OBJECTS += $(addprefix $(PATH_OBJ)/, $(TRANSFORM:%.c=%.o))
OBJECTS += $(addprefix $(PATH_OBJ)/, $(COMPONENTS:%.c=%.o))
OBJECTS += $(addprefix $(PATH_OBJ)/, $(INPUT:%.c=%.o))
OBJECTS += $(addprefix $(PATH_OBJ)/, $(KEYCODES:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)
	@echo library correctly linked

$(OBJECTS): $(HEADERS) | $(PATH_OBJ)
$(OBJECTS): $(PATH_OBJ)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(PATH_OBJ):
	@-mkdir -p $@

%.o: %.c
	$(CC) $(CFLAGS) $(PATH_HEADERS) -o $@ -c $<

clean:
	@rm -rf $(PATH_OBJ)
	@echo removed binary files

fclean: clean
	@rm -f $(NAME)
	@echo removed library

re: fclean all

.PHONY: all clean fclean re
