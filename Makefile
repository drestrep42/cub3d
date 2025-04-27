# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 12:51:47 by drestrep          #+#    #+#              #
#    Updated: 2025/04/27 19:27:36 by igvisera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3d

CC				=	gcc
CFLAGS			=	-g3 -Wall -Wextra -Werror -I$(LIBFT_DIR) -fsanitize=address #-Ofast -DDEBUG=1

LIBFT_DIR		= 	libft
LIBFT			= 	$(LIBFT_DIR)/libft.a

MINILIBX_DIR	= 	MLX42/build/
MLX				= 	$(MINILIBX_DIR)/libmlx42.a


LIBRARIES 	=		-L$(LIBFT_DIR) -lft \
					-L$(MINILIBX_DIR) -lmlx42 \
					-Iinclude -ldl -lglfw -pthread -lm

INCLUDES		=	-I ./inc

PATH_BASE 		=	./src/

BASE_DIR   		=	$(addprefix $(PATH_BASE), $(BASE_SRC))

BASE_SRC		=	main.c		cube_init.c			parsing.c	ft_free.c		\
					file_init.c	parse_textures.c	utils01.c	utils02.c		\
					parse_map.c	parse_elements.c	parse_floor_and_ceiling.c	\
					print_utils.c	player.c		walls.c	\
					calculate_dda.c	\

OBJS			=	${BASE_DIR:.c=.o} \

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARIES) $(INCLUDES)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	make -C MLX42

exe: all
					valgrind --leak-check=full --track-origins=yes ./$(NAME)

clean:
					@rm -rf $(OBJS)
					@$(MAKE) -s -C $(LIBFT_DIR) clean
	
fclean: clean	
					@rm -rf $(NAME)

re:					fclean all

.PHONY: 			all clean fclean re