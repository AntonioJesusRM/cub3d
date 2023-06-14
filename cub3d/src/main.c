/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/14 12:12:36 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	hook(mlx_key_data_t keydata, t_game **game)
{
	double	newx;
	double	newy;

	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		mlx_close_window((*game)->mlx);
	move_player_vert(keydata, game, newx, newy);
	move_player_hor(keydata, game, newx, newy);
	move_cam_left(keydata, game);
	move_cam_right(keydata, game);
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
