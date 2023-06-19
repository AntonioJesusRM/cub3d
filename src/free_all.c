/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:01:51 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/19 11:43:58 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_game(t_game *game)
{
	game->data = free_data(game->data);
	game->textures = free_texture(game->textures);
	free(game->textures);
	free(game->data);
	free(game->player);
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

int	**free_mat(int	**mat)
{
	int	i;

	i = 0;
	if (mat [i] && mat[i] != NULL)
	{
		while (mat[i] && mat[i] != NULL)
		{
			free(mat[i]);
			mat[i] = NULL;
			i++;
		}
	}
	return (mat);
}

t_texture	*free_texture(t_texture *texture)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_delete_texture(texture[i].texture);
		texture[i].buffer = free_mat(texture[i].buffer);
		free(texture[i].buffer);
		texture[i].buffer = NULL;
		i++;
	}
	return (texture);
}
