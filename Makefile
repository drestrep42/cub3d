# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 12:51:47 by drestrep          #+#    #+#              #
#    Updated: 2025/03/07 17:38:45 by drestrep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3d

CC				=	gcc
CFLAGS			=	-g3 -Wall -Wextra -Werror -fsanitize=address -I$(LIBFT_DIR) #-Ofast -DDEBUG=1

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

BASE_SRC		=	main.c  cube_init.c  parsing.c  ft_free.c  ft_exit.c

OBJS			=	${BASE_DIR:.c=.o} \

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARIES) $(INCLUDES)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C MLX42

exe: all
					valgrind --leak-check=full --track-origins=yes ./$(NAME)

clean:
					@rm -rf $(OBJS)
	
fclean: clean	
					@rm -rf $(NAME)

re:					fclean all

.PHONY: 			all clean fclean re