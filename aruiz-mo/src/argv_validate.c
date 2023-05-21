/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:48:07 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/21 16:25:45 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_file(char *file_name)
{
	char	**file_split;
	int		ctrl;

	file_split = ft_split(file_name, '.');
	ctrl = 1;
	if (!file_split[1] || ft_strncmp(file_split[1], "cub", 3) != 0
		|| ft_strlen(file_split[1]) != 3)
		ctrl = 0;
	free(file_split[0]);
	free(file_split[1]);
	free(file_split);
	return (ctrl);
}

int	read_file(char *file_name, t_game **game)
{
	int		fd;
	int		ctrl;
	char	*line;

	if (open(file_name, O_RDONLY) > 0)
	{
		ctrl = 1;
		fd = open(file_name, O_RDONLY);
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("ERROR: file empty.\n");
			ctrl = 0;
		}
		ctrl = parse_file(fd, game, line);
		close (fd);
	}
	else
	{
		printf("ERROR: file not found.\n");
		ctrl = 0;
	}
	return (ctrl);
}

int	parse_file(int fd, t_game **game, char	*line)
{
	int	ctrl;
	int	i;
	int ini_map;
	int	ctrl_data[6];

	ctrl = 1;
	i = -1;
	ini_map = 0;
	while (++i < 6)
		ctrl_data[i] = 0;
	while (line != NULL && ctrl == 1)
	{
		ctrl = texture_data(line, game, ctrl_data, &ini_map);
		if (ini_map == 1 && ctrl == 1)
			break ;
		line = get_next_line(fd);
	}
	while (line != NULL && ctrl == 1)
	{
		read_map(line, &(*game)->map, &ini_map);
		line = get_next_line(fd);
	}
	if (ctrl == 1)
		ctrl = map_validate((*game)->map, ini_map);
	return (ctrl);
}
