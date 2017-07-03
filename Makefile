# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/15 17:38:19 by rhoffsch          #+#    #+#              #
#    Updated: 2017/07/03 16:41:53 by rhoffsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	rtv1
CC				=	gcc
CFLAGS			=	-Wall -Wextra

SDL_DST			=	SDL
INCLUDE			=	-I includes -I libft/includes -I ./$(SDL_DST)/include
SDL				=	`./$(SDL_DST)/bin/sdl2-config --cflags --libs` -lSDL2_image

CFILE			=	main.c \
					init.c \
					scene.c \
					remove_list.c \
					ft_strtrim_extended.c \
					ft_atof.c \
					build.c \
					building_algo.c \
					build_win.c \
					build_amblight.c \
					build_cam.c \
					build_light.c \
					build_objects.c \
					build_properties.c \
					adjust_objects.c \
					ft_tabdel.c \
					raytracer.c \
					sdl_putpixel.c \
					calc.c \
					rot_vector.c

HFILE			=	rtv1.h

HDIR			=	includes/
HDR				=	$(patsubst %.h, $(HDIR)%.h, $(HFILE))
SDIR			=	src/
SRC				=	$(patsubst %.c, $(SDIR)%.c, $(CFILE))
ODIR			=	obj/
OBJ				=	$(patsubst %.c, $(ODIR)%.o, $(CFILE))

.PHONY: all compile lib norm clean fclean nosdl re

all: compile

compile: lib sdl
	@mkdir -p obj/
	@$(MAKE) $(NAME)

lib:
	@$(MAKE) -C libft/

sdl:
	@$(MAKE) -f Makefile.sdl

$(NAME): $(SRC) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L libft/ -lft -lm $(SDL)
	@echo "\033[33;32m$(NAME) \033[33;37mcompiled"
	@echo "\033[33;35m$(NAME) End\033[33;37m"

$(ODIR)%.o: $(SDIR)%.c $(HDR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[33;33m\t$@ compiled\033[33;37m"


norm:
	norminette $(SRC) $(HDR)

clean:
	@rm -rf $(ODIR)
	@echo "\033[33;33mAll objects \033[33;31mdeleted\033[33;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33;32m$(NAME) \033[33;31mdeleted\033[33;37m"

nosdl:
	make fclean -C ./
	make fclean -C ./libft/
	make fclean -f Makefile.sdl

re: fclean all
