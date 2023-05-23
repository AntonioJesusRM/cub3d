/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_array_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:46:01 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/23 16:47:48 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_get_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**ft_copy(char **new_array, char **array)
{
	int	i;
	int	j;

	i = -1;
	while (array[++i])
	{
		j = -1;
		new_array[i] = malloc (sizeof(char) * (ft_strlen(array[i]) + 1));
		if (!new_array[i])
			return (0);
		while(array[i][++j])
			new_array[i][j] = array[i][j];
		new_array[i][j]='\0';
		free(array[i]);
	}
	return (new_array);
}

char	**ft_free_table(char **array)
{
	int	i;

	i = 0;
	if (array [i] && array[i] != NULL)
	{
		while (array[i] && array[i] != NULL)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
	}
	if (array [i])
		free(array);
	array = NULL;
	return (array);
}

char	**duplicate_array(char **map)
{
	int		len;
	char	**new_array;

	len = ft_get_len(map);
	new_array = malloc(sizeof(char *) * (len + 1));
	new_array = ft_copy(new_array, map);
	if (new_array == NULL)
		return (NULL);
	new_array[len] = NULL;
	return (new_array);
}

char	**ft_add_item(char **array, char *item)
{
	int		len;
	int		i;
	char	**new_array;

	len = ft_get_len(array);
	new_array = malloc(sizeof(char *) * (len + 2));
	if (!new_array)
		return (NULL);
	i = -1;
	(void)item;
	new_array = ft_copy(new_array, array);
	free(array);
	new_array[len] = malloc (sizeof(char) * (ft_strlen(item) + 1));
	if (!new_array[len])
		return (0);
	while(item[++i])
		new_array[len][i] = item[i];
	new_array[len][i] = '\0';
	new_array[len + 1] = NULL;
	return (new_array);
}
