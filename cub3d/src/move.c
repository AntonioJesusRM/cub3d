/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:12:00 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/14 12:12:26 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_player_vert(mlx_key_data_t keydata, t_game **game,
	double newx, double newy)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		newx = (*game)->player->pos.x + (*game)->player->dir.x * SPEED;
		newy = (*game)->player->pos.y + (*game)->player->dir.y * SPEED;
		if (!is_wall((int)newx, (int)newy, (*game)->data->map))
		{
			(*game)->player->pos.x = newx;
			(*game)->player->pos.y = newy;
			print_map(*game);
		}
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		newx = (*game)->player->pos.x - (*game)->player->dir.x * SPEED;
		newy = (*game)->player->pos.y - (*game)->player->dir.y * SPEED;
		if (!is_wall((int)newx, (int)newy, (*game)->data->map))
		{
			(*game)->player->pos.x = newx;
			(*game)->player->pos.y = newy;
			print_map(*game);
		}
	}
}

void	move_player_hor(mlx_key_data_t keydata, t_game **game,
	double newx, double newy)
{
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		newx = (*game)->player->pos.x + (*game)->player->dir.y * SPEED;
		newy = (*game)->player->pos.y - (*game)->player->dir.x * SPEED;
		if (!is_wall((int)newx, (int)newy, (*game)->data->map))
		{
			(*game)->player->pos.x = newx;
			(*game)->player->pos.y = newy;
			print_map(*game);
		}
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		newx = (*game)->player->pos.x - (*game)->player->dir.y * SPEED;
		newy = (*game)->player->pos.y + (*game)->player->dir.x * SPEED;
		if (!is_wall((int)newx, (int)newy, (*game)->data->map))
		{
			(*game)->player->pos.x = newx;
			(*game)->player->pos.y = newy;
			print_map(*game);
		}
	}
}

void	move_cam_left(mlx_key_data_t keydata, t_game **game)
{
	double	oldx;

	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		oldx = (*game)->player->dir.x;
		(*game)->player->dir.x = (*game)->player->dir.x
			* cos(-(*game)->player->turn) - (*game)->player->dir.y
			* sin(-(*game)->player->turn);
		(*game)->player->dir.y = oldx * sin(-(*game)->player->turn)
			+ (*game)->player->dir.y * cos(-(*game)->player->turn);
		oldx = (*game)->player->plane.x;
		(*game)->player->plane.x = (*game)->player->plane.x
			* cos(-(*game)->player->turn) - (*game)->player->plane.y
			* sin(-(*game)->player->turn);
		(*game)->player->plane.y = oldx * sin(-(*game)->player->turn)
			+ (*game)->player->plane.y * cos(-(*game)->player->turn);
		print_map(*game);
	}
}

void	move_cam_right(mlx_key_data_t keydata, t_game **game)
{
	double	oldx;

	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		oldx = (*game)->player->dir.x;
		(*game)->player->dir.x = (*game)->player->dir.x
			* cos((*game)->player->turn) - (*game)->player->dir.y
			* sin((*game)->player->turn);
		(*game)->player->dir.y = oldx * sin((*game)->player->turn)
			+ (*game)->player->dir.y * cos((*game)->player->turn);
		oldx = (*game)->player->plane.x;
		(*game)->player->plane.x = (*game)->player->plane.x
			* cos((*game)->player->turn) - (*game)->player->plane.y
			* sin((*game)->player->turn);
		(*game)->player->plane.y = oldx * sin((*game)->player->turn)
			+ (*game)->player->plane.y * cos((*game)->player->turn);
		print_map(*game);
	}
}
