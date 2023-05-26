/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:06:56 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/24 08:38:31 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_validate(char **map, int ini_map, int *mf, int *mc)
{
	int	i;
	int	ctrl;
	int	j;

	i = -1;
	ctrl = 1;
	if (ini_map == 0)
	{
		printf("Error: map not found.\n");
		return (0);
	}
	map = norm_map(map, mf, mc);
	while (map[++i] && ctrl == 1)
	{
		j = -1;
		while (map[i][++j] && ctrl == 1)
		{
			if ((i == 0 || i == ft_get_len(map) - 1)
				|| (j == 0 || j == (int)ft_strlen(map[i]) - 1))
				ctrl = text_border(map[i][j]);
			else
				ctrl = text_int(map[i][j], i, j, map);
		}
	}
	return (ctrl);
}

int	text_border(char l)
{
	if (l == '\n')
		return (1);
	else if (l == '1' || l == ' ')
		return (1);
	else
	{
		printf("Error: format map.\n");
		return (0);
	}
	return (1);
}

int	text_int(char l, int i, int j, char **map)
{
	if (player_exist(map) != 1)
	{
		printf("Error: format map.\n");
		return (0);
	}
	if (l == '\n' || l == '1' || l == ' ')
		return (1);
	else if (l == '0' || l == 'N' || l == 'S' || l == 'E' || l == 'W')
	{
		if ((map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' '
			|| map[i - 1][j + 1] == ' ')
			|| (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
			|| (map[i + 1][j - 1] == ' ' ||
			map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' '))
		{
			printf("Error: format map.\n");
			return (0);
		}
	}
	else
	{
		printf("Error: format map.\n");
		return (0);
	}
	return (1);
}

char	**norm_map(char **map, int *mf, int *mc)
{
	size_t	max_len;
	int		i;

	max_len = 0;
	i = -1;
	while (map[++i])
	{
		if (ft_strlen(map[i]) >= max_len)
			max_len = ft_strlen(map[i]);
	}
	i = -1;
	(*mc) = max_len;
	(*mf) = ft_get_len(map);
	while (map[++i])
	{
		while (ft_strlen(map[i]) < max_len)
			map[i] = ft_strjoin(map[i], " ");
	}
	return (map);
}

int	player_exist(char **map)
{
	int	i;
	int	j;
	int	ctrl;

	i = -1;
	ctrl = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
					ctrl++;
			}
		}
	}
	return (ctrl);
}
