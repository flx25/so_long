# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 09:42:12 by fvon-nag          #+#    #+#              #
#    Updated: 2023/02/08 09:45:06 by fvon-nag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES =

OBJECTS = $(SOURCES:.c=.o)

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME) : all

all: $(NAME)

$(NAME): $(OBJECTS) libft printf
	$(CC) $(CFLAGS) -o $@ $< -Llibft -lft -Lft_printf -lftprintf

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft
printf:
	make -C ft_printf

clean:
	rm -f $(OBJECTS)
	make -C libft clean
	make -C ft_printf clean

fclean: clean
	rm -f so_long libft/libft.a ft_printf/libftprintf.a

re: fclean all

.PHONY: all bonus libft clean fclean re
