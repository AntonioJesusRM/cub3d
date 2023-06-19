/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:11:15 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/06/19 10:08:16 by aruiz-mo         ###   ########.fr       */
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
# define SPEED 0.20
# define TEXWIDTH 64
# define TEXHEIGHT 64

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

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	double			turn;
}	t_player;

typedef struct s_texture
{
	mlx_texture_t	*texture;
	int				**buffer;
}	t_texture;

typedef struct s_game
{
	mlx_t		*mlx;
	t_data		*data;
	t_player	*player;
	t_texture	*textures;
}	t_game;

typedef struct s_ray
{
	mlx_image_t	*img;
	uint32_t	color;
	int			x;
	int			y;
	int			y_init;
	int			y_end;
	int			map_x;
	int			map_y;
	double		camera_x;
	double		ray_x;
	double		ray_y;
	double		delta_x;
	double		delta_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_h;
	double		perp_wall_dist;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
}	t_ray;

//functions argv_validate

int			argv_validate(int argc, char **argv, t_data **data);
int			read_file(char *file_name, t_data **data);
int			check_file(char *file_name);
int			parse_file(int fd, t_data **data, char *line);
char		*parse_file_aux(int fd, t_data **data, char *line, int ctrl);

//functions color_validate

int			put_color(char ***tex, char *line);
int			rgb_text(char **tex);
int			init_color(char ***tex, char *line, int i);
int			test_number(char *line, int i);
void		set_color(char ***tex, char *line, int i);

//functions texture_validate

int			texture_data(char *line, t_data **data,
				int *ctrl_data, int *ini_map);
int			set_texture(t_data **data, int **ctrl_data, char *line, int i);
int			put_texture(char **str, char *line);
int			is_map(char *line, int *ctrl_data, int *ini_map);

//functions read_map

int			init_map(int *ctrl_data, int *ini_map);
void		read_map(char *line, char ***map, int *ini_map);
void		add_line(char ***map, char *line, int nl);

//functions map_validate

int			map_validate(char **map, int ini_map, int *mf, int *mc);
int			text_border(char l);
int			text_int(char l, int i, int j, char **map);
char		**norm_map(char **map, int *mf, int *mc);
int			player_exist(char **map);

//functions char_array_utils

int			ft_get_len(char **array);
char		**ft_copy(char **dest, char **src);
char		**ft_free_table(char **array);
char		**duplicate_array(char **map);
char		**ft_add_item(char **array, char *item);

//functions cub3d_utils

uint32_t	get_rgba(char **rgb);
uint32_t	get_color(int r, int g, int b, int a);
int			is_wall(int x, int y, char **map);
int			**texture_to_color(mlx_texture_t *texture);

//functions init_cub3d

t_data		*init_data(t_data *data);
t_game		*init_textures(t_game *game);
t_game		*init_game(t_data **data, t_player **player, t_game *game);
t_player	*init_player(t_data **data, t_player *player);
t_player	*init_player_aux(t_data **data, t_player *player, int i, int j);

//functions printer

void		print_map(t_game *game);
t_ray		print_col(t_ray ray, t_game *game);
void		draw_line(t_game *game, t_ray ray);

//functions  move
void		move_player_vert(mlx_key_data_t keydata, t_game **game,
				double newx, double newy);
void		move_player_hor(mlx_key_data_t keydata, t_game **game,
				double newx, double newy);
void		move_cam_left(mlx_key_data_t keydata, t_game **game);
void		move_cam_right(mlx_key_data_t keydata, t_game **game);

//functions calc_print

double		calc_rad(double g);
t_ray		calc_step_dist(t_game *game, t_ray ray);
t_ray		dda(t_game *game, t_ray	ray);
void		calc_wall_height(t_ray *ray, t_game *game);

//functions free_all

void		free_game(t_game *game);
t_data		*free_data(t_data *data);
t_texture	*free_texture(t_texture *texture);

//functions main
void		hook(mlx_key_data_t keydata, t_game **game);
int			main(int argc, char **argv);

#endif