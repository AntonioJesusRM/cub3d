/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:52:05 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/19 10:02:24 by aruiz-mo         ###   ########.fr       */
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
	return (get_color(r, g, b, 255));
}

uint32_t	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	is_wall(int x, int y, char **map)
{
	if (map[y][x] == '1')
		return (1);
	return (0);
}

int	**texture_to_color(mlx_texture_t *texture)
{
	int	**buffer;
	int	i;
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	buffer = malloc(sizeof(int *) * (texture->height + 1));
	if (!buffer)
		printf("Error\n");
	while ((uint32_t)i < texture->height)
	{
		j = 0;
		buffer[i] = malloc(sizeof(int) * (texture->width + 1));
		while ((uint32_t)j < texture->width)
		{
			buffer[i][j] = get_color(texture->pixels[cnt],
					texture->pixels[cnt + 1],
					texture->pixels[cnt + 2], texture->pixels[cnt + 3]);
			j++;
			cnt += 4;
		}
		i++;
	}
	return (buffer);
}
