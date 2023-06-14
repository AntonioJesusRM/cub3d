/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:21:22 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/13 13:38:30 by aruiz-mo         ###   ########.fr       */
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

t_game	*init_game(t_data **data, t_player **player, t_game *game)
{
	*player = init_player(data, *player);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (EXIT_SUCCESS);
	game->player = *player;
	game->data = *data;
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
	player->pos = (t_vector){i + 0.5, j + 0.5};
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
		player->plane = (t_vector){1, 0};
	}
	else if ((*data)->map[i][j] == 'E')
	{
		player->dir = (t_vector){1, 0};
		player->plane = (t_vector){0, -1};
	}
	else if ((*data)->map[i][j] == 'S')
	{
		player->dir = (t_vector){0, 1};
		player->plane = (t_vector){-1, 0};
	}
	else if ((*data)->map[i][j] == 'W')
	{
		player->dir = (t_vector){-1, 0};
		player->plane = (t_vector){0, 1};
	}
	return (player);
}
