/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:06:36 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/28 19:44:09 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double calc_rad(double g)
{
	return (g * (PI / 180));
}

int calc_wall_height(t_game *game)
{
	//int		r_heigt;
	double	ang;
	int		d_pproyec;
	//int		height;

	//r_heigt = 500;
	(void)game;
	ang = calc_rad(30);
	d_pproyec = (WIDTH / 2) * tan(ang);
	printf("%i\n",d_pproyec);
	//height = (r_heigt / d_ray) * d_pproyec;
	//return (height);
	return (0);
}

