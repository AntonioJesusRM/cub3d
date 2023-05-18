# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 19:35:33 by aruiz-mo          #+#    #+#              #
#    Updated: 2023/05/17 19:38:05 by aruiz-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#PROGRAMS NAMES
NAME = cub3d

LIBFT_NAME = libft.a

#COMPILER AND FLAGS

CC = gcc

CFLAGS = -Wall -Wextra -Werror

#SOURCE ITEMS

SRC = src/main.c

#MAKE RULE

MAKE = make

COLOR = \033[1;32m

#CREATE OBJ

OBJS = $(SRC:%.c=%.o)

#RULES EXECUTED

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(LIBFT_NAME):
	@$(MAKE) all -sC ./libs/libft
	@cp -r $(addprefix ./libs/libft/, $(LIBFT_NAME)) $(LIBFT_NAME)

$(NAME): $(LIBFT_NAME) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(LIB) -o $(NAME) $(LIBFT_NAME)
	@echo "$(COLOR)cub3d compiled successfully"

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -sC ./libs/libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_NAME)
	@$(MAKE) fclean -sC ./libs/libft
	@echo "$(COLOR)Fclean successfully"

re:	fclean
	$(MAKE)

.PHONY: clean fclean re