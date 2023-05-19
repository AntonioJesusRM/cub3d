/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:11:15 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/19 11:16:08 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

typedef struct s_game
{
	char	**no;
	char	**so;
	char	**we;
	char	**ea;
	int		*f;
	int		*c;
}	t_game;

//functions argv_validate
int		read_file(char *file_name, t_game **game);
int		check_file(char *file_name);
char	*parse_file(int fd, t_game **game, char	*line);

#endif