/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:52:12 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/22 11:22:23 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_game	*free_game(t_game *game)
{
	free(game->no);
	free(game->so);
	free(game->we);
	free(game->ea);
	ft_free_table(game->c);
	ft_free_table(game->f);
	ft_free_table(game->map);
	return (game);
}
