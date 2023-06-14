/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:52:05 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/13 13:43:24 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

uint32_t	get_rgba(char **rgb)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	return (r << 24 | g << 16 | b << 8 | 255);
}

double	calc_rad(double g)
{
	return (g * (PI / 180));
}

int	is_wall(int x, int y, char **map)
{
	if (map[y][x] == '1')
		return (1);
	return (0);
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

void	draw_line(t_game *game, t_ray ray)
{
	int	i;

	i = 0;
	while (i < ray.y_init)
	{
		mlx_put_pixel(ray.img, ray.x, i, get_rgba(game->data->c));
		i++;
	}
	while (i < ray.y_end)
	{
		mlx_put_pixel(ray.img, ray.x, i, ray.color);
		i++;
	}
	while (i < HEIGHT)
	{
		mlx_put_pixel(ray.img, ray.x, i, get_rgba(game->data->f));
		i++;
	}
}
