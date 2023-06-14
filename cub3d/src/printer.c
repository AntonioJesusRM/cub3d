/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:20:14 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/14 11:35:22 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_map(t_game *game)
{
	t_ray	ray;

	ray.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!ray.img || mlx_image_to_window(game->mlx, ray.img, 0, 0) < 0)
		printf("ERROR\n");
	ray.x = 0;
	while (ray.x < WIDTH)
	{
		ray.hit = 0;
		ray.delta_x = pow(10, 30);
		ray.delta_y = pow(10, 30);
		ray.map_x = (int)game->player->pos.x;
		ray.map_y = (int)game->player->pos.y;
		ray.camera_x = 2 * ray.x / (double)WIDTH - 1;
		ray.ray_x = game->player->dir.x + game->player->plane.x * ray.camera_x;
		ray.ray_y = game->player->dir.y + game->player->plane.y * ray.camera_x;
		if (ray.ray_x != 0)
			ray.delta_x = fabs(1 / ray.ray_x);
		if (ray.ray_y != 0)
			ray.delta_y = fabs(1 / ray.ray_y);
		ray = calc_step_dist(game, ray);
		ray = dda(game, ray);
		ray.x++;
	}
}

t_ray	calc_step_dist(t_game *game, t_ray ray)
{
	if (ray.ray_x < 0)
	{
		ray.step_x = -1;
		ray.side_dist_x = (game->player->pos.x - ray.map_x) * ray.delta_x;
	}
	else
	{
		ray.step_x = 1;
		ray.side_dist_x = (ray.map_x + 1.0 - game->player->pos.x)
			* ray.delta_x;
	}
	if (ray.ray_y < 0)
	{
		ray.step_y = -1;
		ray.side_dist_y = (game->player->pos.y - ray.map_y) * ray.delta_y;
	}
	else
	{
		ray.step_y = 1;
		ray.side_dist_y = (ray.map_y + 1.0 - game->player->pos.y)
			* ray.delta_y;
	}
	return (ray);
}

t_ray	dda(t_game *game, t_ray	ray)
{
	while (ray.hit == 0)
	{
		if (ray.side_dist_x < ray.side_dist_y)
		{
			ray.side_dist_x += ray.delta_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist_y += ray.delta_y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		if (game->data->map[ray.map_y][ray.map_x] != '0')
			ray.hit = 1;
	}
	ray = calc_wall_height(ray);
	draw_line(game, ray);
	return (ray);
}

t_ray	calc_wall_height(t_ray ray)
{
	if (ray.side == 0)
	{
		ray.perp_wall_dist = (ray.side_dist_x - ray.delta_x);
		ray.color = 0x0000FFFF;
	}
	else
	{
		ray.perp_wall_dist = (ray.side_dist_y - ray.delta_y);
		ray.color = 0x000000FF;
	}
	ray.line_h = (int)(HEIGHT / ray.perp_wall_dist);
	ray.y_init = -ray.line_h / 2 + HEIGHT / 2;
	if (ray.y_init < 0)
		ray.y_init = 0;
	ray.y_end = ray.line_h / 2 + HEIGHT / 2;
	if (ray.y_end >= HEIGHT)
		ray.y_end = HEIGHT - 1;
	return (ray);
}
