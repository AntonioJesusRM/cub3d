/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:48:42 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/24 09:00:44 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	put_color(char ***tex, char *line)
{
	int	i;

	i = 1;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	if (init_color(tex, line, i) == 0)
		return (0);
	set_color(tex, line, i);
	i = rgb_text((*tex));
	return (i);
}

int	rgb_text(char **tex)
{
	int	i;

	i = -1;
	while (tex[++i])
	{
		if (ft_atoi(tex[i]) < 0 || ft_atoi(tex[i]) > 255)
		{
			printf("Error: the color is not RGB.\n");
			return (0);
		}
	}
	return (1);
}

int	init_color(char ***tex, char *line, int i)
{
	int	j;
	int	k;

	if (test_number(line, i) == 0)
		return (0);
	free (*tex);
	(*tex) = (char **) malloc (sizeof(char *) * 4);
	if (!(*tex))
		return (0);
	k = -1;
	i--;
	while (++k < 3)
	{
		j = 0;
		while (line[++i] != ',' && line[i] != '\0' && line[i]
			!= '\n' && line[i] != '	' && line[i] != ' ')
			j++;
		(*tex)[k] = (char *) malloc (sizeof(char) * (j + 1));
		if (!(*tex)[k])
			return (0);
	}
	(*tex)[3] = NULL;
	return (1);
}

int	test_number(char *line, int i)
{
	int	cont;
	int	ctrl;

	ctrl = 1;
	cont = 0;
	while (line[i] != '\0' && line[i] != '\n'
		&& line[i] != '	' && line[i] != ' ')
	{
		if (line[i] == ',')
			cont++;
		else if (line[i] < 48 || line[i] > 57)
			ctrl = 0;
		i++;
	}
	if (cont != 2 || ctrl == 0)
	{
		printf("Error: format RGB\n");
		return (0);
	}
	return (1);
}

void	set_color(char ***tex, char *line, int i)
{
	int	j;
	int	k;

	j = 0;
	k = -1;
	while (line[i] != '\0' && line[i] != '\n'
		&& line[i] != '	' && line[i] != ' ')
	{
		if (line[i] == ',')
		{
			(*tex)[j][++k] = '\0';
			j++;
			k = -1;
		}
		else
			(*tex)[j][++k] = line[i];
		i++;
	}
	(*tex)[j][++k] = '\0';
}
