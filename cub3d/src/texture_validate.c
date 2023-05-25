/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:48:55 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/24 08:47:53 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	texture_data(char *line, t_game **game, int *ctrl_data, int *ini_map)
{
	int	ctrl;

	ctrl = 1;
	if (ft_strncmp(line, "NO", 2) == 0)
		ctrl = set_texture(game, &ctrl_data, line, 0);
	else if (ft_strncmp(line, "SO", 2) == 0)
		ctrl = set_texture(game, &ctrl_data, line, 1);
	else if (ft_strncmp(line, "WE", 2) == 0)
		ctrl = set_texture(game, &ctrl_data, line, 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		ctrl = set_texture(game, &ctrl_data, line, 3);
	else if (ft_strncmp(line, "F", 1) == 0)
		ctrl = set_texture(game, &ctrl_data, line, 4);
	else if (ft_strncmp(line, "C", 1) == 0)
		ctrl = set_texture(game, &ctrl_data, line, 5);
	else
		ctrl = is_map (line, ctrl_data, ini_map);
	return (ctrl);
}

int	set_texture(t_game **game, int **ctrl_data, char *line, int i)
{
	int	ctrl;

	ctrl = 1;
	if ((*ctrl_data)[i] == 0)
	{
		(*ctrl_data)[i] = (*ctrl_data)[i] + 1;
		if (i == 0)
			ctrl = put_texture(&(*game)->no, line);
		else if (i == 1)
			ctrl = put_texture(&(*game)->so, line);
		else if (i == 2)
			ctrl = put_texture(&(*game)->we, line);
		else if (i == 3)
			ctrl = put_texture(&(*game)->ea, line);
		if (i == 4)
			ctrl = put_color(&(*game)->c, line);
		if (i == 5)
			ctrl = put_color(&(*game)->f, line);
	}
	else
	{
		ctrl = 0;
		printf("Error: excesive number of arguments.\n");
	}
	return (ctrl);
}

int	put_texture(char **tex, char *line)
{
	int	i;
	int	j;

	i = 2;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	j = i;
	while (line[j] != '\0')
		j++;
	free(*tex);
	(*tex) = (char *) malloc (sizeof(char) * (j - i + 1));
	if (!(*tex))
		return (0);
	j = -1;
	while (line[i] != '\0' && line[i] != '\n'
		&& line[i] != '	' && line[i] != ' ')
	{
		(*tex)[++j] = line[i];
		i++;
	}
	(*tex)[++j] = '\0';
	if (open((*tex), O_RDONLY) > 0)
		return (1);
	printf("Error: texture dont found.\n");
	return (0);
}

int	is_map(char *line, int *ctrl_data, int *ini_map)
{
	int	i;
	int	ctrl;

	i = -1;
	ctrl = 1;
	while (line[++i])
	{
		if (line[i] == '1' || line[i] == '0')
		{
			ctrl = init_map(ctrl_data, ini_map);
			break ;
		}
	}
	return (ctrl);
}
