/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/10 15:16:03 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_data	*init_data(t_data *data)
{
	data->no = (char *) malloc(sizeof(char));
	data->no[0] = '\0';
	data->so = (char *) malloc(sizeof(char));
	data->so[0] = '\0';
	data->we = (char *) malloc(sizeof(char));
	data->we[0] = '\0';
	data->ea = (char *) malloc(sizeof(char));
	data->ea[0] = '\0';
	data->c = (char **) malloc(sizeof(char *));
	data->c[0] = NULL;
	data->f = (char **) malloc(sizeof(char *));
	data->f[0] = NULL;
	data->map = (char **) malloc(sizeof(char *));
	data->map[0] = NULL;
	return (data);
}

t_data	*free_data(t_data *data)
{
	free (data->no);
	free (data->so);
	free (data->we);
	free (data->ea);
	ft_free_table(data->c);
	free(data->c);
	ft_free_table(data->f);
	free(data->f);
	ft_free_table(data->map);
	free(data->map);
	return (data);
}

t_player	*init_player(t_data **data, t_player *player)
{
	int				ctrl;
	int				i;
	int				j;

	i = -1;
	ctrl = 1;
	while (ctrl == 1 && (*data)->map[++i])
	{
		j = -1;
		while (ctrl == 1 && (*data)->map[i][++j])
		{
			if ((*data)->map[i][j] == 'N' || (*data)->map[i][j] == 'S'
				|| (*data)->map[i][j] == 'W' || (*data)->map[i][j] == 'E')
					ctrl = 0;
		}
	}
	player->position.y = i;
	player->position.x = j;
	if ((*data)->map[i][j] == 'N')
	{
		player->direction.x = 0;
		player->direction.y = 1;
		player->cam.x = -1;
		player->cam.y = 0;
	}
	else if ((*data)->map[i][j] == 'E')
	{
		player->direction.x = 1;
		player->direction.y = 0;
		player->cam.x = 0;
		player->cam.y = -1;
	}
	else if ((*data)->map[i][j] == 'S')
	{
		player->direction.x = 0;
		player->direction.y = -1;
		player->cam.x = 1;
		player->cam.y = 0;
	}
	else if ((*data)->map[i][j] == 'W')
	{
		player->direction.x = -1;
		player->direction.y = 0;
		player->cam.x = 0;
		player->cam.y = 1;
	}
	(*data)->map[i][j] = '0';
	return (player);
}
uint32_t get_rgba(char **rgb)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
    return (r << 24 | g << 16 | b << 8 | 255);
}
void draw_line(t_game *game, int x, int y_init, int y_end, uint32_t color)
{
	mlx_image_t	*img;
	int			i;

	img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(game->mlx, img, x, 0) < 0))
		printf("ERROR\n");
	i = 0;
	while (i < y_init)
	{
		mlx_put_pixel(img, x, i, get_rgba(game->data->c));
		i++;
	}
	while (i < y_end)
	{
		mlx_put_pixel(img, x, i, color);
		i++;
	}
	while (i < HEIGHT)
	{
		mlx_put_pixel(img, x, i, get_rgba(game->data->f));
		i++;
	}
}
void print_map(t_game *game)
{
	int		x;
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
	int		draw_start;
	int		draw_end;
	uint32_t	color;

	x = 0;
	while(x < WIDTH)
    {
		hit = 0;
		delta_x = pow(1,30);
		delta_y = pow(1,30);
		map_x = (int)game->player->position.x;
		map_y = (int)game->player->position.y;
		camera_x = 2 * x / (double)WIDTH - 1;
		ray_x = game->player->direction.x + game->player->cam.x * camera_x;
		ray_y = game->player->direction.y + game->player->cam.y * camera_x;
		if (ray_x != 0)
			delta_x = sqrt(1 + (ray_y * ray_y) / (ray_x * ray_x));
		if (ray_y != 0)
			delta_y = sqrt(1 + (ray_x * ray_x) / (ray_y * ray_y));
		if (ray_x < 0)
		{
			step_x = 1;
			side_dist_x = (game->player->position.x - map_x) * delta_x;
		}
		else
		{
			step_x = -1;
			side_dist_x = (map_x + 1.0 - game->player->position.x) * delta_x;
		}
		if (ray_y < 0)
		{
			step_y = 1;
			side_dist_y = (game->player->position.y - map_y) * delta_y;
		}
		else
		{
			step_y = -1;
			side_dist_y = (map_y + 1.0 - game->player->position.y) * delta_y;
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
		if(side == 0)
		{
			perp_wall_dist = (side_dist_x - delta_x);
			color = 0x0000FFFF;
		}
		else
		{
			perp_wall_dist = (side_dist_y - delta_y);
			color = 0x000000FF;
		}
		x++;
		line_h = (int)(HEIGHT / perp_wall_dist);
		draw_start = -line_h / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_h / 2 + HEIGHT / 2;
		if(draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		draw_line(game, x, draw_start, draw_end, color);
	}
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_game		*game;
	t_player	*player;

	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_SUCCESS);
	data = init_data(data);
	if (argv_validate(argc, argv, &data) == 0)
	{
		data = free_data(data);
		free(data);
		return (EXIT_SUCCESS);
	}
	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_SUCCESS);
	player = malloc(sizeof(t_player));
	if (!player)
		return (EXIT_SUCCESS);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (EXIT_SUCCESS);
	player = init_player(&data, player);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->player = player;
	game->data = data;
	game->time = 0;
	game->old_time = 0;
	print_map(game);
	//mlx_key_hook(game->mlx, (mlx_keyfunc)hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	data = free_data(data);
	free(data);
	return (EXIT_SUCCESS);
}
