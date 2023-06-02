/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/01 11:17:18 by aruiz-mo         ###   ########.fr       */
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
	int	ctrl;

	ctrl = 1;
	if (y >= game->data->mf || x >= game->data->mc)
		return (0);
	if (game->data->map[x][y] != '0')
		ctrl = 0;
	return (ctrl);
}
void	print_ray(t_game *game, uint32_t x_col, uint32_t y_col)
{
	//printf("Valores del punto final: (%i, %i)\n", (int)x_col, (int)y_col);
	mlx_image_t	*img;
	uint32_t	y;
	uint32_t	x;
	int			p_x;
	int			p_y;

	img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(game->mlx, img, 0, 0) < 0))
		printf("ERROR\n");
	y = (uint32_t)game->player->img->instances->y;
	x = (uint32_t)game->player->img->instances->x;
	p_x = ((int)x_col - (int)x);
	p_y = ((int)y_col - (int)y);
	/* printf("Valores del punto inicial: (%i, %i)\n", (int)x, (int)y);
	printf("Valores de la pendiente: (%i, %i)\n", (int)p_x, (int)p_y); */
	mlx_put_pixel(img, x, y, 0xFF0000FF);
	if (p_x != 0)
	{
		p_x = p_x/2;
	}
	if (p_y != 0)
	{
		p_y = p_y/2;
	}	
	mlx_put_pixel(img, x + p_x, y + p_y, 0xFF0000FF);
	if (p_x != 0)
	{
		p_x = p_x/2;
	}
	if (p_y != 0)
	{
		p_y = p_y/2;
	}
	mlx_put_pixel(img, x + p_x, y + p_y, 0xFF0000FF);
	mlx_put_pixel(img, x_col, y_col, 0xFF0000FF);
}
void point_inter_horiz(t_game *game, double g, t_ray **ray)
{
	int			step_x;
	int			step_y;
	int			inter_x;
	int			inter_y;
	double		rad;
	int			x;
	int			y;
	int			nextx_hor;
	int			nexty_hor;

	if (g == 90 || g == 270)
		return ;
	step_x = floor(WIDTH / game->data->mc);
	inter_x = game->player->img->instances->x;
	if (!(g > 90 && g < 270))
		inter_x += step_x;
	rad = calc_rad(g);
	inter_y = game->player->img->instances->y;
	step_y = floor(step_x * tan (rad));
	if (g > 90 && g < 270)
		step_x = - step_x;
	if ((step_y > 0 && (g > 0 && g < 180)) || (!(g > 0 && g < 180) && step_y < 0))
		step_y = -step_y;
	nextx_hor = inter_x;
	nexty_hor = inter_y;
	if (g > 90 && g < 270)
		nextx_hor--;
	while (nextx_hor >= 0 && nextx_hor <= 800 && nexty_hor >= 0 && nexty_hor <= 600)
	{
		x = floor(nextx_hor * game->data->mc / WIDTH);
		y = floor(nexty_hor * game->data->mf / HEIGHT);
		if (y == 5)
			y--;
		if (clash_wall(y, x, game) == 0)
		{
			(*ray)->c_hor = 1;
			if (y >= game->data->mf || x >= game->data->mc)
				(*ray)->c_hor = 0;
			if (!(g > 90 && g < 270))
				nextx_hor -= step_x;
			(*ray)->x_hor = nextx_hor;
			(*ray)->y_hor = nexty_hor;
			break ;
		}
		else
		{
			nextx_hor += step_x;
			nexty_hor += step_y;
		}
	}
}
void point_inter_vert(t_game *game, double g, t_ray **ray)
{
	int			step_y;
	int			step_x;
	int			inter_y;
	int			x;
	int			y;
	int			inter_x;
	int			nextx_vert;
	int			nexty_vert;
	double		rad;

	if (g == 180 || g == 0)
		return ;
	step_y = HEIGHT / game->data->mf;
	rad = calc_rad(g);
	step_x = step_y / tan (rad);
	inter_y = game->player->img->instances->y;
	inter_x = game->player->img->instances->x;
	if ((g > 0 && g < 180))
		step_y = -step_y;
	if ((step_x > 0 && (g > 90 && g < 270)) || (!(g > 90 && g < 270) && step_x < 0))
			step_x = -step_x;
	nextx_vert = inter_x;
	nexty_vert = inter_y;
	if ((g > 0 && g < 180))
		nexty_vert--;
	while (nextx_vert >= 0 && nextx_vert <= 800 && nexty_vert >= 0 && nexty_vert <= 600)
	{
		x = round(nextx_vert * game->data->mc / WIDTH);
		y = round(nexty_vert * game->data->mf / HEIGHT);
		if (clash_wall(y, x, game) == 0)
		{
			(*ray)->c_ver = 1;
			if (y >= game->data->mf || x >= game->data->mc)
				(*ray)->c_ver = 1;
			(*ray)->x_ver = nextx_vert;
			(*ray)->y_ver = nexty_vert; 
			break;
		}
		else
		{
			nextx_vert += step_x;
			nexty_vert += step_y;
		}
	}
}
t_ray	*init_ray(t_ray *ray)
{
	ray->c_hor = 0;
	ray->c_ver = 0;
	ray->x_hor = -1;
	ray->x_ver = -1;
	ray->y_hor = -1;
	ray->y_ver = -1;
	return (ray);
}

void	calculate_ray (t_game *game, double g)
{
	t_ray	*ray;
	double	x_clash;
	double	disthor;
	double	distver;
	double	y_clash;

	ray = malloc (sizeof(ray));
	ray = init_ray(ray);
	point_inter_vert(game, g, &ray);
	point_inter_horiz(game, g, &ray);
	if (ray->c_hor == 1 && ray->c_ver == 0)
	{
		printf("Para %f el choque es con el eje Y.\n", g);
		x_clash = ray->x_hor;
		y_clash = ray->y_hor;
	}
	else if (ray->c_hor == 0 && ray->c_ver == 1)
	{
		printf("Para %f el choque es con el eje X.\n", g);
		x_clash = ray->x_ver;
		y_clash = ray->y_ver;
	}
	else
	{
		x_clash = (double)(game->player->img->instances->x - ray->x_hor);
		y_clash = (double)(game->player->img->instances->y - ray->y_hor);
		disthor = sqrt(pow(x_clash,2) + pow(y_clash,2));
		x_clash = (double)(game->player->img->instances->x - ray->x_ver);
		y_clash = (double)(game->player->img->instances->y - ray->y_ver);
		distver = sqrt(pow(x_clash,2) + pow(y_clash,2));
		if (disthor < distver)
		{
			printf("Para %f el choque mas cercano es con el eje Y.\n", g);
			x_clash = ray->x_hor;
			y_clash = ray->y_hor;
		}
		else
		{
			printf("Para %f el choque mas cercano es con el eje X.\n", g);
			x_clash = ray->x_ver;
			y_clash = ray->y_ver;
		}
	}
	print_ray(game,(uint32_t)x_clash,(uint32_t)y_clash);
}

void	print_player(t_game *game)
{
	t_player	*p;
	t_data		*d;
	//int			i;
	double			g;

	//i = 0;
	g = game->player->grade - 30;
	//g = 249.75;
	p = game->player;
	d = game->data;
	mlx_image_to_window (game->mlx, p->img, p->x * (WIDTH / d->mc), p->y * (HEIGHT / d->mf));
	calculate_ray(game, g);
	calculate_ray(game, g + 30);
	if (g + 60 > 360)
		calculate_ray(game, g + 60 - 360);
	else
		calculate_ray(game, g + 60);
	/* while (i < WIDTH)
	{
		if (g + 0.075 >= 360)
			g = g - 360;
		g += 0.075;
		calculate_ray(game, g);
		i++;
	} */
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
	mlx_texture_t	*texture;
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
	if ((*data)->map[i][j] == 'N')
		player->grade = 90;
	else if ((*data)->map[i][j] == 'E')
		player->grade = 360;
	else if ((*data)->map[i][j] == 'S')
		player->grade = 270;
	else if ((*data)->map[i][j] == 'W')
		player->grade = 180;
	(*data)->map[i][j] = '0';
	texture = mlx_load_png("avoid.png");
	if (!texture)
		printf("NOP\n");
	player->img = mlx_texture_to_image(game->mlx, texture);
	return (player);
}

void	hook(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT) )
		game->player->img->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->img->instances[0].y += 5;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->img->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->img->instances[0].x += 5;
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
