# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/15 17:38:19 by rhoffsch          #+#    #+#              #
#    Updated: 2017/05/24 14:20:38 by rhoffsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	rtv1
CC				=	gcc
CFLAGS			=	-Wall -Wextra

INCLUDE			=	-I includes -I libft/includes -I ./$(LIB_SDL)/include -I ./$(LIB_SDL)/lib/
LIB_SDL			=	SDL
PATH_SDL		=	SDL2-2.0.5
PATH_SDL_IMG	=	SDL2_image-2.0.1
SDL				=	`./$(LIB_SDL)/bin/sdl2-config --cflags --libs` -lSDL2_image

CFILE			=	main.c \
					init.c \
					scene.c

HFILE			=	rtv1.h

HDIR			=	includes/
HDR				=	$(patsubst %.h, $(HDIR)%.h, $(HFILE))
SDIR			=	src/
SRC				=	$(patsubst %.c, $(SDIR)%.c, $(CFILE))
ODIR			=	obj/
OBJ				=	$(patsubst %.c, $(ODIR)%.o, $(CFILE))

.PHONY: all compile lib aff norm clean fclean re

#all: sdl compile
all: compile

$(NAME): $(SRC) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L libft/ -lft #$(SDL)
	@echo "\033[33;32m$(NAME) \033[33;37mcreated"
	@echo "\033[33;35m$(NAME) End\033[33;37m"

$(ODIR)%.o: $(SDIR)%.c $(HDR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[33;33m\t$@ compiled\033[33;37m"

sdl:
	@echo "\033[32mDownloading SDL ...\033[0m"
	@curl https://www.libsdl.org/release/SDL2-2.0.5.tar.gz -o $(PATH_SDL).tar.gz
	@curl https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.1.tar.gz -o $(PATH_SDL_IMG).tar.gz
	@echo "\033[32mCompiling SDL ...\033[0m"
	@mkdir -p $(LIB_SDL)
	@tar -xf $(PATH_SDL).tar.gz
	@tar -xf $(PATH_SDL_IMG).tar.gz
	@cd $(PATH_SDL) && ./configure --prefix=`cd ../$(LIB_SDL) && pwd` && make -j 8 && make -j 8 install
	@cd $(PATH_SDL_IMG) && ./configure --prefix=`cd ../$(LIB_SDL) && pwd` && make -j 8 && make -j 8 install
	@rm -rf $(PATH_SDL)
	@rm -rf $(PATH_SDL_IMG)
	@rm -rf $(PATH_SDL_IMG).tar.gz
	@rm -rf $(PATH_SDL).tar.gz
	export DYLD_LIBRARY_PATH=`pwd`/$(LIB_SDL)

compile: lib
	@mkdir -p obj/
	@$(MAKE) $(NAME)

lib:
	@$(MAKE) -C libft/

norm:
	norminette $(SRC) $(HDR)

clean:
	@rm -f $(OBJ)
	@echo "\033[33;33mAll objects \033[33;31mdeleted\033[33;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33;32m$(NAME) \033[33;31mdeleted\033[33;37m"

re: fclean all
