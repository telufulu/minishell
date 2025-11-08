/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:27:21 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/12 14:16:57 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dest;

	i = 0;
	len_dest = ft_strlen(dst);
	if (len_dest >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (dstsize-- && dst[i] != '\0')
		i++;
	while (dstsize-- && *src != '\0')
		dst[i++] = *src++;
	dst[i] = '\0';
	if (len_dest <= dstsize || len_dest <= ft_strlen(src))
		return (ft_strlen(src) + ft_strlen(dst));
	return (i);
}
