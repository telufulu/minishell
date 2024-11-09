/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:29:06 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/09 13:39:15 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
//
static void	*my_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	if (!dst && !src)
		return (NULL);
	ptr_dst = (unsigned char *) dst;
	ptr_src = (unsigned char *) src;
	while (n-- > 0)
	{
		*ptr_dst = *ptr_src;
		ptr_dst++;
		ptr_src++;
	}
	return (dst);
}

static void	*my_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	if (!dst && !src)
		return (NULL);
	ptr_dst = (unsigned char *)dst;
	ptr_src = (const unsigned char *)src;
	if ((ptr_dst <= ptr_src) || (ptr_dst >= ptr_src + len))
		return (my_memcpy(ptr_dst, ptr_src, len));
	else
	{
		ptr_dst += len;
		ptr_src += len;
		while (len-- > 0)
			*(--ptr_dst) = *(--ptr_src);
	}
	return (dst);
}

void	*my_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*result;

	if (new_size == 0)
	{
		if (ptr != NULL)
			free((char *)ptr - sizeof(size_t));
		return (NULL);
	}
	result = malloc(new_size + 1);
	if (!result)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			my_memmove(result, ptr, old_size);
		else
			my_memmove(result, ptr, new_size);
		free(ptr);
	}
	return (result);
}
