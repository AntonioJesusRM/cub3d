/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:12:11 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/17 18:14:54 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	calc_rad(double g)
{
	return (g * (PI / 180));
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
	calc_wall_height(&ray, game);
	ray = print_col(ray, game);
	draw_line(game, ray);
	return (ray);
}

void	calc_wall_height(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_x);
		if (ray->ray_x > 0)
			ray->color = 3;
		else
			ray->color = 2;
		ray->wall_x = game->player->pos.y + ray->perp_wall_dist * ray->ray_y;
	}
	else
	{
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_y);
		if (ray->ray_y > 0)
			ray->color = 1;
		else
			ray->color = 0;
		ray->wall_x = game->player->pos.x + ray->perp_wall_dist * ray->ray_x;
	}
	ray->line_h = (int)(HEIGHT / ray->perp_wall_dist);
	ray->y_init = -ray->line_h / 2 + HEIGHT / 2;
	if (ray->y_init < 0)
		ray->y_init = 0;
	ray->y_end = ray->line_h / 2 + HEIGHT / 2;
	if (ray->y_end >= HEIGHT)
		ray->y_end = HEIGHT - 1;
}
