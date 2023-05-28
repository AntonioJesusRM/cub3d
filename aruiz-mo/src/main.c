/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/28 21:47:49 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_dates	*init_dates(t_dates *dates)
{
	dates->no = (char *) malloc(sizeof(char));
	dates->no[0] = '\0';
	dates->so = (char *) malloc(sizeof(char));
	dates->so[0] = '\0';
	dates->we = (char *) malloc(sizeof(char));
	dates->we[0] = '\0';
	dates->ea = (char *) malloc(sizeof(char));
	dates->ea[0] = '\0';
	dates->c = (char **) malloc(sizeof(char *));
	dates->c[0] = NULL;
	dates->f = (char **) malloc(sizeof(char *));
	dates->f[0] = NULL;
	dates->map = (char **) malloc(sizeof(char *));
	dates->map[0] = NULL;
	return (dates);
}

t_dates	*free_dates(t_dates *dates)
{
	free (dates->no);
	free (dates->so);
	free (dates->we);
	free (dates->ea);
	ft_free_table(dates->c);
	free(dates->c);
	ft_free_table(dates->f);
	free(dates->f);
	ft_free_table(dates->map);
	free(dates->map);
	return (dates);
}

int	clash_wall(int x, int y, t_game *game)
{
	int ctrl;
	double	dmc;
	double	dmf;
	int	tx;
	int	ty;

	ctrl = 1;
	dmc = (double)(game->dates->mc);
	dmf = (double)(game->dates->mf);
	tx = floor((dmc/(double)WIDTH) * (double)x);
	ty = floor((dmf/(double)HEIGHT) * (double)y);
	if (game->dates->map[ty][tx] != '0')
		ctrl = 0;
	return (ctrl);
}

void print_pixel(int x[5], int y[5], t_game *game)
{
	mlx_image_t *img;
	int			i;

	i = 0;
	img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!img
		|| (mlx_image_to_window(game->mlx, img, x[i], y[i])
			< 0))
		exit(EXIT_FAILURE);
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);
	mlx_put_pixel(img, x[1] - x[0], y[1] + y[0], 0xFF0000FF);
}

void point_inter_vert(t_game *game, double g)
{
	int	step_y;
	int	step_x;
	int	i;
	int	inter_y[5];
	int	inter_x[5];
	double	rad;

	step_y = HEIGHT / game->dates->mf;
	rad = calc_rad(g);
	step_x = step_y / tan (rad);
	inter_y[0] = game->player->y * (HEIGHT / game->dates->mf);
	inter_x[0] = (inter_y[0]) / tan (rad);
	if (g > 180 &&  g < 360)
		inter_y[0] += step_y;
	i = 1;
	while ( inter_y[i] > 0 && inter_x[i] > 0 && inter_y[i] < 600 && inter_x[i] < 800)
	{
		if (g > 180 && g < 360)
			inter_y[i] += step_y;
		else
			inter_y[i] -= step_y;
		inter_x[i] += step_x;
		i++;
	}
	print_pixel(inter_x, inter_y, game);
}

void	print_player(t_game *game)
{
	t_player 	*p;
	t_dates		*d;

	p = game->player;
	d = game->dates;
	mlx_image_to_window(game->mlx, p->img, p->x * (WIDTH / d->mc), p->y * (HEIGHT / d->mf));
	point_inter_vert(game, 60);
}


void	put_map(char **map, t_game *game, t_dates *dates)
{
	int32_t	i;
	int32_t	j;
    mlx_image_t *img;
	uint32_t	y;
	uint32_t	x;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			mlx_image_to_window(game->mlx, game->img, j * (WIDTH/dates->mc), i * (HEIGHT/dates->mf));
			if (map[i][j] == '1')
			{
				img = mlx_new_image(game->mlx, (WIDTH/dates->mc), HEIGHT/dates->mf);
				if (!img
					|| (mlx_image_to_window(game->mlx, img, j * (WIDTH/dates->mc), i * (HEIGHT/dates->mf))
						< 0))
					exit(EXIT_FAILURE);
				y = 0;
				while (y < img->height)
				{
					x = 0;
					while (x < img->width)
					{
						mlx_put_pixel(img, x, y, 0x000000FF);
						x++;
					}
					y++;
				}
			}
		}
	}
	game->img = img;
	print_player(game);
}

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

t_player	*init_player(t_dates **dates, t_player *player, t_game *game)
{
	int ctrl;
	int	i;
	mlx_texture_t *texture;
	int	j;

	i = -1;
	ctrl = 1;
	while (ctrl == 1 && (*dates)->map[++i])
	{
		j = -1;
		while(ctrl == 1 && (*dates)->map[i][++j])
		{
			if ((*dates)->map[i][j] == 'N' || (*dates)->map[i][j] == 'S'
				|| (*dates)->map[i][j] == 'W' || (*dates)->map[i][j] == 'E')
					ctrl = 0;
		}
	}
	player->y = i;
	player->x = j;
	if ((*dates)->map[i][j] == 'N')
		player->grade = 90;
	else if ((*dates)->map[i][j] == 'E')
		player->grade = 360;
	else if ((*dates)->map[i][j] == 'S')
		player->grade = 270;
	else if ((*dates)->map[i][j] == 'W')
		player->grade = 180;
	(*dates)->map[i][j] = '0';
	texture = mlx_load_png("/home/antonio/Escritorio/mlx/avoid.png");
	if (!texture)
		printf("NOP\n");
	player->img = mlx_texture_to_image(game->mlx, texture);
	return (player);
}

void	hook(mlx_key_data_t keydata, t_game *game)
{
	int	*x;
	int	*y;

	x = &game->player->img->instances[0].x;
	y = &game->player->img->instances[0].y;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT) && (clash_wall((*x), (*y) - 5, game)))
		game->player->img->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT) && (clash_wall((*x), (*y) + 25, game)))
		game->player->img->instances[0].y += 5;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT) && (clash_wall((*x) - 5, (*y), game)))
		game->player->img->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT) && (clash_wall((*x) + 25, (*y), game)))
		game->player->img->instances[0].x += 5;
}

int	main(int argc, char **argv)
{
	t_dates		*dates;
	t_game		*game;
	t_player	*player;

	dates = malloc(sizeof(t_dates));
	if (!dates)
		return (EXIT_SUCCESS);
	dates = init_dates(dates);
	if (argv_validate(argc, argv, &dates) == 0)
	{
		dates = free_dates(dates);
		free(dates);
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
		ft_error();
	player = init_player(&dates, player, game);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->player = player;
	game->dates = dates;
	put_map(dates->map, game, dates);
	mlx_key_hook(game->mlx, (mlx_keyfunc)hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	dates = free_dates(dates);
	free(dates);
	return (EXIT_SUCCESS);
}
