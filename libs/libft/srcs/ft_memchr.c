/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:19:17 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/19 15:39:22 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*aux;

	aux = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*aux == (unsigned char)c)
			return ((void *)aux);
		aux++;
	}
	return (NULL);
}
