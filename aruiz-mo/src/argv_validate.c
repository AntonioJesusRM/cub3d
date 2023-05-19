/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:48:07 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/19 11:16:30 by aruiz-mo         ###   ########.fr       */
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
			line = parse_file(fd, game, line);
		close (fd);
	}
	else
	{
		printf("ERROR: file not found.\n");
		ctrl = 0;
	}
	return (ctrl);
}

char	*parse_file(int fd, t_game **game, char	*line)
{
	(void)game;
	(void)fd;
	return (line);
}
