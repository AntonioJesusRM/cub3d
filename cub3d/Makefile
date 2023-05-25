# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 10:13:51 by aruiz-mo          #+#    #+#              #
#    Updated: 2023/05/21 14:50:07 by aruiz-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
SRCS	=	src/main.c src/argv_validate.c src/color_validate.c \
			src/texture_validate.c src/map_validate.c src/read_map.c \
			src/char_array_utils.c src/print.c
CC		=	gcc
CFLAGS	=	-Wextra -Wall -Werror
RM		=	rm -rf
LIBFT	=	./libs/libft
MLX42	=	./libs/MLX42
HEADERS	=	-I include -I $(MLX42)/include/MLX42
#HEADERS =	-I include -ldl -lglfw -pthread -lm
LIBS	=	-lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(MLX42)/libmlx42.a $(LIBFT)/libft.a
#LIBS	=	$(MLX42)/libmlx42.a $(LIBFT)/libft.a
OBJS	=	$(SRCS:%.c=%.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			@make -C $(MLX42)
			@make -C $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBS) -o $(NAME)

clean:
			@make -C $(MLX42) clean
			@make -C $(LIBFT) clean
			$(RM) $(OBJS)

fclean:		
		@make -C $(MLX42) fclean
		@make -C $(LIBFT) fclean
		$(RM) $(OBJS) $(NAME)

re:		fclean all

run:	all
		./$(NAME)

.PHONY:	all clean fclean re