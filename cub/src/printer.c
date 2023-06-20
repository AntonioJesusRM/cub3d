/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:20:14 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/17 18:13:27 by aruiz-mo         ###   ########.fr       */
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

t_ray	print_col(t_ray ray, t_game *game)
{
	ray.wall_x -= floor(ray.wall_x);
	ray.tex_x = (int)(ray.wall_x * (double)game->textures->texture->width);
	if (ray.side == 0 && ray.ray_x > 0)
		ray.tex_x = game->textures->texture->width - ray.tex_x - 1;
	if (ray.side == 1 && ray.ray_y < 0)
		ray.tex_x = game->textures->texture->width - ray.tex_x - 1;
	ray.step = 1.0 * game->textures->texture->height / ray.line_h;
	ray.tex_pos = (ray.y_init - HEIGHT / 2 + ray.line_h / 2) * ray.step;
	ray.y = ray.y_init;
	while (ray.y < ray.y_end)
	{
		ray.tex_y = (int)ray.tex_pos;
		if (ray.tex_pos > game->textures->texture->height - 1)
			ray.tex_pos = game->textures->texture->height - 1;
		ray.tex_pos += ray.step;
		mlx_put_pixel(ray.img, ray.x,
			ray.y, game->textures[ray.color].buffer[ray.tex_y][ray.tex_x]);
		ray.y++;
	}
	return (ray);
}

void	draw_line(t_game *game, t_ray ray)
{
	int	i;

	i = 0;
	while (i < ray.y_init)
	{
		mlx_put_pixel(ray.img, ray.x, i, get_rgba(game->data->c));
		i++;
	}
	i = ray.y_end;
	while (i < HEIGHT)
	{
		mlx_put_pixel(ray.img, ray.x, i, get_rgba(game->data->f));
		i++;
	}
}
