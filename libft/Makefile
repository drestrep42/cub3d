# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/03 00:07:08 by drestrep          #+#    #+#              #
#    Updated: 2025/04/21 20:56:55 by igvisera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	libft.a

OBJ_DIR				=	obj/
CC					=	gcc
RM					=	rm -rf
CFLAGS				=	-Wall -Wextra -Werror -I.

LIBFT_DIR			=	src/
LIBFT_SRC			=	ft_isalnum.c			ft_isalpha.c			ft_isascii.c			ft_isdigit.c			\
						ft_isprint.c			ft_memcpy.c				ft_memset.c				ft_strchr.c				\
						ft_strlen.c				ft_strncmp.c			ft_strrchr.c			ft_issign.c				\
						ft_tolower.c			ft_toupper.c			ft_bzero.c				ft_memmove.c			\
						ft_strlcpy.c			ft_memchr.c				ft_memcmp.c				ft_strlcat.c			\
						ft_strnstr.c			ft_atoi.c				ft_calloc.c				ft_strdup.c				\
						ft_substr.c				ft_strjoin.c			ft_strtrim.c			ft_split.c				\
						ft_itoa.c				ft_strmapi.c			ft_striteri.c			ft_putchar_fd.c			\
						ft_putstr_fd.c			ft_putendl_fd.c			ft_putnbr_fd.c			ft_lstnew_bonus.c		\
						ft_lstadd_front_bonus.c	ft_lstsize_bonus.c		ft_lstlast_bonus.c		ft_lstadd_back_bonus.c	\
						ft_lstdelone_bonus.c	ft_lstclear_bonus.c		ft_lstiter_bonus.c		ft_lstmap_bonus.c		\
						ft_get_string.c			ft_atoi_base.c			ft_hexadecimal.c		ft_printf.c				\
						ft_putchar.c			ft_putnbr.c				ft_putptr.c				ft_putstr.c				\
						ft_unsigned_int.c		get_next_line.c			get_next_line_utils.c	ft_malloc.c				\
						ft_exit.c				ft_strcmp.c

SRC 				=	$(addprefix $(LIBFT_DIR), $(LIBFT_SRC))

OBJ					=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all:					$(NAME)

$(NAME):				$(OBJ)
						@ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)%.o:			$(SRC_DIR)%.c
						@mkdir -p $(dir $@)
						@$(CC) $(CFLAGS) -c $< -o $@

clean:	
						@$(RM) $(OBJ_DIR) $(NAME)

fclean:					clean
						@$(RM) $(NAME)

re:						fclean $(NAME)

.PHONY:					all clean fclean re bonus
