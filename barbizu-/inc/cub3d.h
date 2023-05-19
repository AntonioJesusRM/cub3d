/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:11:15 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/19 09:40:44 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define SPACE '0'
# define WALL '1'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'
# include <stdio.h>
# include <stdlib.h>
# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

typedef struct s_game
{
    mlx_t           *mlx;
    char            **map;
    int             width;
    int             height;
    mlx_texture_t   *texture;
    mlx_image_t     *space;
    mlx_image_t     *wall;
    mlx_image_t     *player;
}   t_game;

#endif