/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:57:49 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/21 16:19:20 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int init_map(int *ctrl_data, int *ini_map)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ctrl_data[i] == 0)
		{
			printf("Error: not all items found.\n");
			return (0);
		}
		i++;
	}
	(*ini_map) = 1;
	return (1);
}

void	read_map(char *line, char ***map, int *ini_map)
{
	int	i;

	i = -1;
	if (*ini_map == 1)
	{
		free (*map);
		(*map) = malloc(sizeof(char *) * (2));
		if (!(*map))
			return ;
		(*map)[0] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!(*map)[0])
			return ;
		while (line[++i])
			(*map)[0][i] = line[i];
		(*map)[0][i] = '\0';
		(*map)[1] = NULL;
	}
	else
		(*map) = ft_add_item(*map, line);
	(*ini_map) = (*ini_map) + 1;
}
