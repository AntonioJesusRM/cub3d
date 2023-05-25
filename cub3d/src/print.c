/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:27:55 by barbizu-          #+#    #+#             */
/*   Updated: 2023/05/24 11:27:58 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/cub3d.h"

void	print_player(t_game *game)
{
	int32_t	i;
	int32_t	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == NORTH)
				mlx_image_to_window(game->mlx, game->player, j * 30, i * 30);
			else if (game->map[i][j] == SOUTH)
				mlx_image_to_window(game->mlx, game->player, j * 30, i * 30);
			else if (game->map[i][j] == EAST)
				mlx_image_to_window(game->mlx, game->player, j * 30, i * 30);
			else if (game->map[i][j] == WEST)
				mlx_image_to_window(game->mlx, game->player, j * 30, i * 30);
		}
	}
}

uint32_t get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	print_map(t_game *game)
{
	int32_t	i;
	int32_t	j;
    mlx_image_t *img;
	uint32_t	color;
	uint32_t	y;
	uint32_t	x;

	color = get_rgba(255, 0, 0, 255); //rojo
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			mlx_image_to_window(game->mlx, game->space, j * 30, i * 30);
			if (game->map[i][j] == WALL)
			{
                img = mlx_new_image(game->mlx, 30, 30);
                if (!img || (mlx_image_to_window(game->mlx, img, j * 30, i * 30) < 0))
                    exit(EXIT_FAILURE);
				y = 0;
				while (y < img->height)
				{
					x = 0;
					while (x < img->width)
					{
						mlx_put_pixel(img, x, y, color);
						x++;
					}
					y++;
				}
                mlx_image_to_window(game->mlx, game->wall, j * 30, i * 30);
            }	
		}
	}
	print_player(game);
}
