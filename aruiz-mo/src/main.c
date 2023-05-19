/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/19 11:08:03 by aruiz-mo         ###   ########.fr       */
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

	if (argv_validate(argc, argv, &game) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
