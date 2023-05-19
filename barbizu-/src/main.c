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

void	print_map(t_game *game)
{
	int32_t	i;
	int32_t	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
			mlx_image_to_window(game->mlx, game->space, i * 30, j * 30);
	}
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == WALL)
				mlx_image_to_window(game->mlx, game->wall, i * 30, j * 30);
			else if (game->map[i][j] == NORTH)
				mlx_image_to_window(game->mlx, game->player, i * 30, j * 30);
		}
	}
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(256, 256, "Test", true);
	game->height = 256;
	game->width = 256;
	if (!game->mlx)
		exit(EXIT_FAILURE);
	game->texture = mlx_load_png("/Users/barbizu-/Downloads/wall.png");
	if (!game->texture)
		exit(EXIT_FAILURE);
	game->wall = mlx_texture_to_image(game->mlx, game->texture);
	game->texture = mlx_load_png("/Users/barbizu-/Downloads/flat.png");
	if (!game->texture)
		exit(EXIT_FAILURE);
	game->space = mlx_texture_to_image(game->mlx, game->texture);
	game->texture = mlx_load_png("/Users/barbizu-/Downloads/dino.png");
	if (!game->texture)
		exit(EXIT_FAILURE);
	game->player = mlx_texture_to_image(game->mlx, game->texture);
	mlx_delete_texture(game->texture);
	print_map(game);
}

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

void	readFile(char *fileName, t_game *game)
{
	int		fd;
	char	*line;
	char	*str;
	char	*temp;

	if (access(fileName, R_OK) == 0)
	{	
		fd = open(fileName, O_RDONLY);
		game->map = (char **)malloc(sizeof(char *) * 5);
		str = ft_strdup("");
		line = get_next_line(fd);
		while (line != NULL)
		{
			temp = ft_strjoin(str, line);
			str = temp;
			printf("%s\n", line);
			line = get_next_line(fd);
		}
		close (fd);
		game->map = ft_split(str, '\n');
		init_game(game);
	}
	else
		printf("ERROR: file not found.\n");
}

void	hook(mlx_key_data_t keydata, t_game	*game)
{
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->instances[0].y += 5;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		game->player->instances[0].x += 5;
}

int main(int argc, char **argv)
{
	int	ctrl;
	t_game	*game;

	game = malloc(sizeof(t_game));
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
			readFile(argv[1], game);
	}
	mlx_key_hook(game->mlx, (mlx_keyfunc)hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}