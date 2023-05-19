/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-mo <aruiz-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:14:13 by aruiz-mo          #+#    #+#             */
/*   Updated: 2023/02/17 11:01:26 by aruiz-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			cont;
	unsigned char	*ptr;	

	if (c == 0 && n == 0)
		return (0);
	ptr = (unsigned char *)s;
	cont = 0;
	while (cont < n)
	{
		if (ptr[cont] == (unsigned char)c)
			return ((void *)&ptr[cont]);
		cont ++;
	}
	return (NULL);
}
