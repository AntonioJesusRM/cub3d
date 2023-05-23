/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/23 15:14:46 by aruiz-mo         ###   ########.fr       */
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
	game = free_game(game);
	free(game);
	return (EXIT_SUCCESS);
}
