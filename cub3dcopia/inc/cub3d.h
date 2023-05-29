/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:11:15 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/29 10:14:54 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"
# define WIDTH 800
# define PI 3.1416
# define HEIGHT 600

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**f;
	char	**c;
	char	**map;
	int		mc;
	int		mf;
}	t_data;

typedef struct s_player
{
	int				x;
	int				y;
	int				grade;
	mlx_image_t		*img;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_data		*data;
	t_player	*player;
}	t_game;

//functions argv_validate

int		argv_validate(int argc, char **argv, t_data **data);
int		read_file(char *file_name, t_data **data);
int		check_file(char *file_name);
int		parse_file(int fd, t_data **data, char *line);
char	*parse_file_aux(int fd, t_data **data, char *line, int ctrl);

//functions color_validate

int		put_color(char ***tex, char *line);
int		rgb_text(char **tex);
int		init_color(char ***tex, char *line, int i);
int		test_number(char *line, int i);
void	set_color(char ***tex, char *line, int i);

//functions texture_validate

int		texture_data(char *line, t_data **data, int *ctrl_data, int *ini_map);
int		set_texture(t_data **data, int **ctrl_data, char *line, int i);
int		put_texture(char **str, char *line);
int		is_map(char *line, int *ctrl_data, int *ini_map);

//functions read_map

int		init_map(int *ctrl_data, int *ini_map);
void	read_map(char *line, char ***map, int *ini_map);
void	add_line(char ***map, char *line, int nl);

//functions map_validate

int		map_validate(char **map, int ini_map, int *mf, int *mc);
int		text_border(char l);
int		text_int(char l, int i, int j, char **map);
char	**norm_map(char **map, int *mf, int *mc);
int		player_exist(char **map);

//functions char_array_utils

int		ft_get_len(char **array);
char	**ft_copy(char **dest, char **src);
char	**ft_free_table(char **array);
char	**duplicate_array(char **map);
char	**ft_add_item(char **array, char *item);

//functions wall_operation

double 	calc_rad(double g);

#endif