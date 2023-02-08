# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 09:42:12 by fvon-nag          #+#    #+#              #
#    Updated: 2023/02/08 11:05:03 by fvon-nag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME) : all

all: $(NAME)

$(NAME): $(OBJECTS) libft
	$(CC) $(CFLAGS) -o $@ $< -Llibft -lft -lmlx -framework OpenGL -framework AppKit


%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft
clean:
	rm -f $(OBJECTS)
	make -C libft clean

fclean: clean
	rm -f so_long libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re
