/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/26 10:35:22 by aruiz-mo         ###   ########.fr       */
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

void	put_map(char **map, t_game *game)
{
	int			i;
	int			j;
	mlx_image_t	*img;
	uint32_t	x;
	uint32_t	y;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			mlx_image_to_window(game->mlx, game->img, j * 30, i * 30);
			if (map[i][j] == '1')
			{
				printf("%c", map[i][j]);
				img = mlx_new_image(game->mlx, 30, 30);
				if (!img
					|| (mlx_image_to_window(game->mlx, img, j * 30, i * 30)
						< 0))
					exit(EXIT_FAILURE);
				y = 0;
				while (y < img->height)
				{
					x = 0;
					while (x < img->width)
					{
						mlx_put_pixel(img, x, y, 0xFF0000FF);
						x++;
					}
					y++;
				}
				mlx_image_to_window(game->mlx, img, j * 30, i * 30);
			}
		}
	}
}

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_dates	*dates;
	t_game	*game;

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
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		ft_error();
	game->img = mlx_new_image(game->mlx, 800, 600);
	put_map(dates->map, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	dates = free_dates(dates);
	free(dates);
	return (EXIT_SUCCESS);
}
