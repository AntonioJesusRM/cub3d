/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/13 13:49:37 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void print_map(t_game *game)
{
	t_ray	ray;
	int		map_x;
	int		map_y;
	double	camera_x;
	double	ray_x;
	double	ray_y;
	double	delta_x;
	double	delta_y;
	double	side_dist_x;
    double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
    int		side;
	int		line_h;
	double	perp_wall_dist;

	ray.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!ray.img || mlx_image_to_window(game->mlx, ray.img, 0, 0) < 0)
		printf("ERROR\n");
	ray.x = 0;
	while (ray.x < WIDTH)
	{
		hit = 0;
		delta_x = pow(10, 30);
		delta_y = pow(10, 30);
		map_x = (int)game->player->pos.x;
		map_y = (int)game->player->pos.y;
		camera_x = 2 * ray.x / (double)WIDTH - 1;
		ray_x = game->player->dir.x + game->player->plane.x * camera_x;
		ray_y = game->player->dir.y + game->player->plane.y * camera_x;
		if (ray_x != 0)
			delta_x = fabs(1 / ray_x);
		if (ray_y != 0)
			delta_y = fabs(1 / ray_y);
		if (ray_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->player->pos.x - map_x) * delta_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player->pos.x) * delta_x;
		}
		if (ray_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player->pos.y - map_y) * delta_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player->pos.y) * delta_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_y;
				map_y += step_y;
				side = 1;
			}
			if (game->data->map[map_y][map_x] != '0')
				hit = 1;
		}
		if (side == 0)
		{
			perp_wall_dist = (side_dist_x - delta_x);
			ray.color = 0x0000FFFF;
		}
		else
		{
			perp_wall_dist = (side_dist_y - delta_y);
			ray.color = 0x000000FF;
		}
		line_h = (int)(HEIGHT / perp_wall_dist);
		ray.y_init = -line_h / 2 + HEIGHT / 2;
		if (ray.y_init < 0)
			ray.y_init = 0;
		ray.y_end = line_h / 2 + HEIGHT / 2;
		if (ray.y_end >= HEIGHT)
			ray.y_end = HEIGHT - 1;
		draw_line(game, ray);
		ray.x++;
	}
}

void	hook(mlx_key_data_t keydata, t_game **game)
{
	double	oldx;
	double	newx;
	double	newy;

	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		oldx = (*game)->player->dir.x;
		(*game)->player->dir.x = (*game)->player->dir.x * cos((*game)->player->turn) - (*game)->player->dir.y * sin((*game)->player->turn);
		(*game)->player->dir.y = oldx * sin((*game)->player->turn) + (*game)->player->dir.y * cos((*game)->player->turn);
		oldx = (*game)->player->plane.x;
		(*game)->player->plane.x = (*game)->player->plane.x * cos((*game)->player->turn) - (*game)->player->plane.y * sin((*game)->player->turn);
		(*game)->player->plane.y = oldx * sin((*game)->player->turn) + (*game)->player->plane.y * cos((*game)->player->turn);
		print_map(*game);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		oldx = (*game)->player->dir.x;
		(*game)->player->dir.x = (*game)->player->dir.x * cos(-(*game)->player->turn) - (*game)->player->dir.y * sin(-(*game)->player->turn);
		(*game)->player->dir.y = oldx * sin(-(*game)->player->turn) + (*game)->player->dir.y * cos(-(*game)->player->turn);
		oldx = (*game)->player->plane.x;
		(*game)->player->plane.x = (*game)->player->plane.x * cos(-(*game)->player->turn) - (*game)->player->plane.y * sin(-(*game)->player->turn);
		(*game)->player->plane.y = oldx * sin(-(*game)->player->turn) + (*game)->player->plane.y * cos(-(*game)->player->turn);
		print_map(*game);
	}
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		mlx_close_window((*game)->mlx);
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

int	main(int argc, char **argv)
{
	t_data		*data;
	t_game		*game;
	t_player	*player;

	data = malloc(sizeof(t_data));
	game = malloc(sizeof(t_game));
	player = malloc(sizeof(t_player));
	if (!data || !game || !player)
		return (EXIT_SUCCESS);
	data = init_data(data);
	if (argv_validate(argc, argv, &data) == 0)
	{
		data = free_data(data);
		free(data);
		return (EXIT_SUCCESS);
	}
	game = init_game(&data, &player, game);
	mlx_key_hook(game->mlx, (mlx_keyfunc)hook, &game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	data = free_data(data);
	free(data);
	free(player);
	free(game);
	return (EXIT_SUCCESS);
}
