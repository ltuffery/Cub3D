# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 09:07:25 by ltuffery          #+#    #+#              #
#    Updated: 2023/09/18 09:05:40 by ltuffery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D

CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g

LIBMLX	:= ./MLX42

HEADERS	:= -I $(LIBMLX)/include -I./libft/includes -I./includes/

LIBS	:= $(LIBMLX)/build/libmlx42.a ./libft/libft.a -ldl -lglfw -pthread -lm

SRCS	:= srcs/main.c \
		   srcs/parsing/textures.c \
		   srcs/parsing/colors.c \
		   srcs/parsing/config.c \
		   srcs/parsing/map.c \
		   srcs/utils/map_utils.c \
		   srcs/exec/launche.c

OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@make -s -C libft
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
