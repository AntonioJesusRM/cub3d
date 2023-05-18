/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:17:14 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/03/16 10:01:45 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		len;
	int		i;

	len = ft_strlen(s) + 1;
	new_str = malloc(len * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (*(s + i) != '\0')
	{
		*(new_str + i) = *(s + i);
		i++;
	}
	*(new_str + i) = '\0';
	return (new_str);
}
