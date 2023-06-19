/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:01:51 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/19 10:38:04 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_game(t_game *game)
{
	game->data = free_data(game->data);
	if (game->textures)
		game->textures = free_texture(game->textures);
	free(game->textures);
	//free(game->data);
	//free(game->player);
}

t_data	*free_data(t_data *data)
{
	free (data->no);
	free (data->so);
	free (data->we);
	free (data->ea);
	ft_free_table(data->c);
	free(data->c);
	ft_free_table(data->f);
	free(data->f);
	ft_free_table(data->map);
	free(data->map);
	return (data);
}

t_texture	*free_texture(t_texture *texture)
{
	int	i;

	free(texture->texture);
	i = 0;
	if (texture->buffer[i] && texture->buffer[i] != NULL)
	{
		while (texture->buffer[i] && texture->buffer[i] != NULL)
		{
			free(texture->buffer[i]);
			texture->buffer[i] = NULL;
			i++;
		}
	}
	if (texture->buffer [i])
		free(texture->buffer);
	texture->buffer = NULL;
	return (texture);
}
