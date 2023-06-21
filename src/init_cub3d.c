/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:21:22 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/17 18:14:23 by aruiz-mo         ###   ########.fr       */
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

t_game	*init_textures(t_game *game)
{
	int			i;

	game->textures = (t_texture *)malloc (sizeof(t_texture) * 5);
	game->textures[0].texture = mlx_load_png(game->data->no);
	game->textures[1].texture = mlx_load_png(game->data->so);
	game->textures[2].texture = mlx_load_png(game->data->ea);
	game->textures[3].texture = mlx_load_png(game->data->we);
	i = 0;
	while (i < 4)
	{
		if (!game->textures[i].texture)
			exit(EXIT_SUCCESS);
		game->textures[i].buffer = texture_to_color(game->textures[i].texture);
		i++;
	}
	game->textures[i].buffer = NULL;
	game->textures[i].texture = NULL;
	return (game);
}

t_game	*init_game(t_data **data, t_player **player, t_game *game)
{
	*player = init_player(data, *player);
	game->data = *data;
	game->player = *player;
	game = init_textures(game);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx || !game->textures)
		return (EXIT_SUCCESS);
	print_map(game);
	return (game);
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
	player->pos = (t_vector){j + 0.5, i + 0.5};
	player->turn = calc_rad(2);
	player = init_player_aux(data, player, i, j);
	(*data)->map[i][j] = '0';
	return (player);
}

t_player	*init_player_aux(t_data **data, t_player *player, int i, int j)
{
	if ((*data)->map[i][j] == 'N')
	{
		player->dir = (t_vector){0, -1};
		player->plane = (t_vector){0.64, 0};
		player->start_dir = 'N';
	}
	else if ((*data)->map[i][j] == 'E')
	{
		player->dir = (t_vector){1, 0};
		player->plane = (t_vector){0, -0.64};
		player->start_dir = 'E';
	}
	else if ((*data)->map[i][j] == 'S')
	{
		player->dir = (t_vector){0, 1};
		player->plane = (t_vector){-0.64, 0};
		player->start_dir = 'S';
	}
	else if ((*data)->map[i][j] == 'W')
	{
		player->dir = (t_vector){-1, 0};
		player->plane = (t_vector){0, 0.64};
		player->start_dir = 'W';
	}
	return (player);
}
