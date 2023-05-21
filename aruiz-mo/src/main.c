/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/20 17:22:37 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	argv_validate(int argc, char **argv, t_game **game)
{
	int	ctrl;

	if (argc != 2)
	{
		printf("ERROR: incorrect argument number.\n");
		ctrl = 0;
	}
	else
	{
		ctrl = check_file(argv[1]);
		if (ctrl == 0)
			printf("ERROR: incorrect file name.\n");
		else
			ctrl = read_file(argv[1], game);
	}
	return (ctrl);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->no = (char *) malloc(sizeof(char));
	game->no[0] = '\0';
	game->so = (char *) malloc(sizeof(char));
	game->so[0] = '\0';
	game->we = (char *) malloc(sizeof(char));
	game->we[0] = '\0';
	game->ea = (char *) malloc(sizeof(char));
	game->ea[0] = '\0';
	game->c = (char **) malloc(sizeof(char*));
	game->c[0] = "\0";
	game->f = (char **) malloc(sizeof(char*));
	game->f[0] = "\0";
	game->map = (char **) malloc(sizeof(char*));
	game->map[0] = "\0";
	if (argv_validate(argc, argv, &game) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
