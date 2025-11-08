/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:40:29 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/19 16:02:02 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;

	if (!src && !dst)
		return (NULL);
	s = (char *)src;
	d = (char *)dst;
	if (d > s)
	{
		while (n)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	else
		while (n--)
			*d++ = *s++;
	return (dst);
}
