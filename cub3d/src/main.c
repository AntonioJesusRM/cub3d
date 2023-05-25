/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/24 09:34:14 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_game	*init_game(t_game *game)
{
	game->no = (char *) malloc(sizeof(char));
	game->no[0] = '\0';
	game->so = (char *) malloc(sizeof(char));
	game->so[0] = '\0';
	game->we = (char *) malloc(sizeof(char));
	game->we[0] = '\0';
	game->ea = (char *) malloc(sizeof(char));
	game->ea[0] = '\0';
	game->c = (char **) malloc(sizeof(char *));
	game->c[0] = NULL;
	game->f = (char **) malloc(sizeof(char *));
	game->f[0] = NULL;
	game->map = (char **) malloc(sizeof(char *));
	game->map[0] = NULL;
	return (game);
}

t_game	*free_game(t_game *game)
{
	free (game->no);
	free (game->so);
	free (game->we);
	free (game->ea);
	ft_free_table(game->c);
	free(game->c);
	ft_free_table(game->f);
	free(game->f);
	ft_free_table(game->map);
	free(game->map);
	return (game);
}

void	hook(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->instances[0].y += 5;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->instances[0].x += 5;
}

void	init_images(t_game *game)
{
	game->mlx = mlx_init(256, 256, "cub3d", true);
	if (!game->mlx)
		exit(EXIT_FAILURE);
	game->texture = mlx_load_png("/Users/barbizu-/Downloads/wall.png");
	if (!game->texture)
		exit(EXIT_FAILURE);
	game->wall = mlx_texture_to_image(game->mlx, game->texture);
	game->texture = mlx_load_png("/Users/barbizu-/Downloads/flat.png");
	if (!game->texture)
		exit(EXIT_FAILURE);
	game->space = mlx_texture_to_image(game->mlx, game->texture);
	game->texture = mlx_load_png("/Users/barbizu-/Downloads/dino.png");
	if (!game->texture)
		exit(EXIT_FAILURE);
	game->player = mlx_texture_to_image(game->mlx, game->texture);
	mlx_delete_texture(game->texture);
	print_map(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_SUCCESS);
	game = init_game(game);
	if (argv_validate(argc, argv, &game) == 0)
	{
		game = free_game(game);
		free(game);
		return (EXIT_SUCCESS);
	}
	init_images(game);
	mlx_key_hook(game->mlx, (mlx_keyfunc)hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	game = free_game(game);
	free(game);
	return (EXIT_SUCCESS);
}
