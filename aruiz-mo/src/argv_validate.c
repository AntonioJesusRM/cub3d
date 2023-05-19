/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:48:07 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/19 12:23:10 by aruiz-mo         ###   ########.fr       */
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

	if (access(file_name, R_OK) == 0)
	{
		ctrl = 1;
		fd = open(file_name, O_RDONLY);
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("ERROR: file empty.\n");
			ctrl = 0;
		}
		while (line != NULL)
			ctrl = parse_file(fd, game, &line);
		close (fd);
	}
	else
	{
		printf("ERROR: file not found.\n");
		ctrl = 0;
	}
	return (ctrl);
}

int	parse_file(int fd, t_game **game, char	**line)
{
	int	ctrl;
	int	ctrl_data[4];

	(void)game;
	ctrl_data[0, 0, 0, 0];
	ctrl = 1;
	ctrl = texture_data(line);
	if (ft_strncmp((*line), "NO", 2) == 0)
		printf("%s", (*line));
	if (ft_strncmp((*line), "SO", 2) == 0)
		printf("%s", (*line));
	if (ft_strncmp((*line), "WE", 2) == 0)
		printf("%s", (*line));
	if (ft_strncmp((*line), "EA", 2) == 0)
		printf("%s", (*line));
	*line = get_next_line(fd);
	return (ctrl);
}
