/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/23 12:19:41 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	hook(mlx_key_data_t keydata, t_game **game)
{
	double	newx;
	double	newy;

	newx = 0;
	newy = 0;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		mlx_close_window((*game)->mlx);
	move_player_vert(keydata, game, newx, newy);
	if ((*game)->player->start_dir == 'N' || (*game)->player->start_dir == 'S')
	{
		move_player_hor_ns(keydata, game, newx, newy);
		move_cam_left_ns(keydata, game);
		move_cam_right_ns(keydata, game);
	}
	else
	{
		move_player_hor_we(keydata, game, newx, newy);
		move_cam_left_we(keydata, game);
		move_cam_right_we(keydata, game);
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
		free(game);
		free(player);
		free(data);
		return (EXIT_SUCCESS);
	}
	game = init_game(&data, &player, game);
	mlx_key_hook(game->mlx, (mlx_keyfunc)hook, &game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	free(game);
	return (EXIT_SUCCESS);
}
