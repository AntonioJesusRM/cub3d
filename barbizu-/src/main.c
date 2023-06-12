/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/29 13:01:49 by aruiz-mo         ###   ########.fr       */
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

int	clash_wall(int x, int y, t_game *game)
{
	int		ctrl;
	double	dmc;
	double	dmf;
	int		tx;
	int		ty;

	ctrl = 1;
	dmc = (double)(game->data->mc);
	dmf = (double)(game->data->mf);
	tx = floor((dmc/(double)WIDTH) * (double)x);
	ty = floor((dmf/(double)HEIGHT) * (double)y);
	if (game->data->map[tx][ty] != '0')
		ctrl = 0;
	return (ctrl);
}

void point_inter_vert(t_game *game, double g)
{
	int			step_y;
	int32_t			i_y;
	int32_t			i_x;
	int		ctrl;
	int			step_x;
	int			inter_y;
	int			inter_x;
	double		rad;
	mlx_image_t	*img;
	uint32_t		y;
	uint32_t		x;

	step_y = HEIGHT / game->data->mf;
	rad = calc_rad(g);
	step_x = step_y / tan (rad);
	inter_y = game->player->img->instances->y;
	inter_x = game->player->img->instances->x;
	if (g > 180 && g < 360)
		inter_y += step_y;
	i_y = inter_y;
	i_x = inter_x;
	ctrl = 1;
	while (ctrl)
	{
		if (g > 180 && g < 360)
			inter_y += step_y;
		else
			inter_y -= step_y;
		if (step_x > 0 && (g > 90 && g < 270))
			step_x = -step_x;
		else if (step_x < 0 && (g < 90 || g > 270))
			step_x = -step_x;
		inter_x += step_x;
		ctrl = clash_wall(inter_x, inter_y, game);
	}
	img = mlx_new_image(game->mlx, HEIGHT, WIDTH);
	//printf("step_x:%d, step_y:%d, inter_x:%d, inter_y:%d, i_x:%d, i_y:%d\n", step_x, step_y, inter_x, inter_y, i_x, i_y);
	mlx_image_to_window(game->mlx, img, 0, 0);
	y = (uint32_t)i_y;
	x = i_x;
	while (y > (uint32_t)inter_y)
	{
		mlx_put_pixel(img, x, y, 0xFF0000FF);
		if (i_x > inter_x)
			x--;
		else if (i_x < inter_x)
			x++;
		if (i_y > inter_y)
			y--;
		else if (i_y < inter_y)
			y++;
	}

}

void	print_player(t_game *game)
{
	t_player	*p;
	t_data		*d;
	int			i;
	double			g;
	uint32_t	y;
	uint32_t	x;
	uint32_t	newx;
	uint32_t	newy;

	i = 0;
	g = game->player->grade - 30;
	p = game->player;
	d = game->data;
	mlx_image_to_window(game->mlx, p->img, p->pos.x * (WIDTH / d->mc), p->pos.y * (HEIGHT / d->mf));
	y = 0;
	while (y < p->img->height)
	{
		x = 0;
		while (x < p->img->width)
		{
			mlx_put_pixel(p->img, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}
	newx = p->img->instances->x + cos(p->turn) * 20;
	newy = p->img->instances->y - sin(p->turn) * 20;
	printf("y:%d, x:%d, newy:%d, nx:%d\n", game->player->img->instances->y, game->player->img->instances->x, newy, newx);
	mlx_image_to_window(game->mlx, p->line, 0, 0);
	y = p->img->instances->y;
	while (y > newy)
	{
		x = p->img->instances->x;
		while (x > newx)
		{
			mlx_put_pixel(p->line, x, y, 0xFFFFFFFF);
			x--;
		}
		y--;
	}
}


void	put_map(char **map, t_game *game, t_data *data)
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
			mlx_image_to_window(game->mlx, game->img, j * (WIDTH/data->mc), i * (HEIGHT/data->mf));
			if (map[i][j] == '1')
			{
				img = mlx_new_image(game->mlx, (WIDTH/data->mc), HEIGHT/data->mf);
				if (!img
					|| (mlx_image_to_window(game->mlx, img, j * (WIDTH/data->mc), i * (HEIGHT/data->mf))
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

t_player	*init_player(t_data **data, t_player *player, t_game *game)
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
	player->y = i;
	player->x = j;
	player->pos.x = j;
	player->pos.y = i;
	player->turn = calc_rad(SPEED);
	if ((*data)->map[i][j] == 'N')
	{
		player->grade = 90;
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 1;
		player->plane.y = 0;
	}
	else if ((*data)->map[i][j] == 'E')
	{
		player->grade = 0;
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -1;
	}
	else if ((*data)->map[i][j] == 'S')
	{
		player->grade = 270;
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -1;
		player->plane.y = 0;
	}
	else if ((*data)->map[i][j] == 'W')
	{
		player->grade = 180;
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 1;
	}
	(*data)->map[i][j] = '0';
	player->img = mlx_new_image(game->mlx, 4, 4);
	if (!player->img)
		exit(EXIT_FAILURE);
	player->line = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!player->line)
		exit(EXIT_FAILURE);
	return (player);
}

void	hook(mlx_key_data_t keydata, t_game *game)
{
	int	*x;
	int	*y;
	int			i;
	double			g;
	double	oldx;

	i = 0;
	g = 60.0000;
	x = &game->player->img->instances->x;
	y = &game->player->img->instances->y;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		oldx = game->player->dir.x;
		game->player->dir.x = game->player->dir.x * cos(-game->player->turn) - game->player->dir.y * sin(-game->player->turn);
		game->player->dir.y = oldx * sin(-game->player->turn) + game->player->dir.y * cos(-game->player->turn);
		printf("dir_x:%f, dir_y:%f\n", game->player->dir.x, game->player->dir.y);
		oldx = game->player->plane.x;
		game->player->plane.x = game->player->plane.x * cos(-game->player->turn) - game->player->plane.y * sin(-game->player->turn);
		game->player->plane.y = oldx * sin(-game->player->turn) + game->player->plane.y * cos(-game->player->turn);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		oldx = game->player->dir.x;
		game->player->dir.x = game->player->dir.x * cos(game->player->turn) - game->player->dir.y * sin(game->player->turn);
		game->player->dir.y = oldx * sin(game->player->turn) + game->player->dir.y * cos(game->player->turn);
		printf("dir_x:%f, dir_y:%f\n", game->player->dir.x, game->player->dir.y);
		oldx = game->player->plane.x;
		game->player->plane.x = game->player->plane.x * cos(game->player->turn) - game->player->plane.y * sin(game->player->turn);
		game->player->plane.y = oldx * sin(game->player->turn) + game->player->plane.y * cos(game->player->turn);
	}
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		game->player->pos.x = game->player->dir.x * SPEED;
		game->player->pos.y = game->player->dir.y * SPEED;
		printf("pos_x:%f, pos_y:%f\n", game->player->pos.x, game->player->pos.y);
		printf("ins_x:%d, ins_y:%d\n", game->player->img->instances->x, game->player->img->instances->y);
		game->player->img->instances->x += game->player->pos.x;
		game->player->img->instances->y += game->player->pos.y;
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		game->player->pos.x = game->player->dir.x * SPEED;
		game->player->pos.y = game->player->dir.y * SPEED;
		printf("pos_x:%f, pos_y:%f\n", game->player->pos.x, game->player->pos.y);
		printf("ins_x:%d, ins_y:%d\n", game->player->img->instances->x, game->player->img->instances->y);
		game->player->img->instances->x -= game->player->pos.x;
		game->player->img->instances->y -= game->player->pos.y;
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		if (game->player->dir.x == 0)
		{
			if (game->player->dir.y < 0)
				game->player->img->instances->x -= SPEED;
			else
				game->player->img->instances->x += SPEED;
		}
		else
		{
			if (game->player->dir.x < 0)
				game->player->img->instances->y += SPEED;
			else
				game->player->img->instances->y -= SPEED; 
		}
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		if (game->player->dir.x == 0)
		{
			if (game->player->dir.y < 0)
				game->player->img->instances->x += SPEED;
			else
				game->player->img->instances->x -= SPEED;
		}
		else
		{
			if (game->player->dir.x < 0)
				game->player->img->instances->y -= SPEED;
			else
				game->player->img->instances->y += SPEED; 
		}
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
		ft_error();
	player = init_player(&data, player, game);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->player = player;
	game->data = data;
	put_map(data->map, game, data);
	mlx_key_hook(game->mlx, (mlx_keyfunc)hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	data = free_data(data);
	free(data);
	return (EXIT_SUCCESS);
}
