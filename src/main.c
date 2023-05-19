/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:53:19 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/19 09:51:58 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	checkFile(char *fileName)
{
	char	**fileSplit;
	int		ctrl;

	fileSplit = ft_split(fileName, '.');
	ctrl = 1;
	if	( !fileSplit[1] || ft_strncmp(fileSplit[1], "cub", 3) != 0 || ft_strlen(fileSplit[1]) != 3 )
		ctrl = 0;
	free(fileSplit[0]);
	free(fileSplit[1]);
	free(fileSplit);
	return (ctrl);
}

void	readFile(char *fileName)
{
	int		fd;
	char	*line;

	if (access(fileName, R_OK) == 0)
	{	
		fd = open(fileName, O_RDONLY);
		line = get_next_line(fd);
		while (line != NULL)
		{
			printf("%s\n", line);
			line = get_next_line(fd);
		}
		close (fd);
	}
	else
		printf("ERROR: file not found.\n");
}

int main(int argc, char **argv)
{
	int	ctrl;

	if (argc != 2)
	{
		printf("ERROR: incorrect argument number.\n");
		return(EXIT_SUCCESS);
	}
	else
	{
		ctrl = checkFile(argv[1]);
		if (ctrl == 0)
			printf("ERROR: incorrect file name.\n");
		else
			readFile(argv[1]);
	}
	return (EXIT_SUCCESS);
}