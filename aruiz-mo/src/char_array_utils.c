/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_array_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:46:01 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/05/22 12:27:58 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_get_len(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**ft_copy(char **dest, char **src)
{
	int		i;
	int		j;

	i = 0;
	while (src[i])
	{
		j = -1;
		dest[i] = malloc(sizeof(char) * ft_strlen(src[i]));
		if (!dest[i])
			return (NULL);
		dest[i] = src[i];
		/*while (src[i][++j] != '\0')
			dest[i][j] = src[i][j];
		dest[i][j] = '\0';*/
		//free(src[i]);
		i++;
	}
	free(src);
	return (dest);
}

char	**ft_free_table(char **array)
{
	int	i;

	i = 0;
	if (array [i] && array[i] != NULL)
	{
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
	}
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
	new_array = malloc(sizeof(char *) * (len + 1));
	if (!new_array)
		return (NULL);
	new_array = ft_copy(new_array, array);
	new_array[len] = malloc(sizeof(char) * ft_strlen(item) + 1);
	if (!new_array[len])
		return (NULL);
	i = -1;
	while (item[++i])
		new_array[len][i] = item[i];
	new_array[len][i] = '\0';
	new_array[len + 1] = NULL;
	return (new_array);
}
