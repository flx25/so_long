# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 09:42:12 by fvon-nag          #+#    #+#              #
#    Updated: 2023/02/24 10:12:10 by fvon-nag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = main.c \
			map.c \
			map2.c \
			map3.c \
			map4.c \
			map5.c \
			images.c \
			move.c

OBJECTS = $(SOURCES:.c=.o)

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx

all: $(NAME)

$(NAME): $(OBJECTS) libft mlx
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	+make -C libft

mlx:
	+make -C mlx
clean:
	rm -f $(OBJECTS)
	+make -C libft clean
fclean: clean
	rm -f so_long libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re

noflags: $(OBJECTS) libft
	$(CC) -o $@ $< -Llibft -lft -lmlx -framework OpenGL -framework AppKit


