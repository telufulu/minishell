/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:15:45 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/11 22:52:14 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_realloc creates a new allocation, copies as much of the old data pointed
// to by ptr as will fit to the new allocation, frees the old allocation, and 
// returns a pointer to the allocated memory.
//
// If ptr is NULL, ft_realloc is identical to a call to ft_malloc for size bytes
//
// If size is zero and ptr is not NULL, a new, minimum sized object is allocated
// and the original object is freed.

void	*ft_realloc(void *ptr, size_t size)
{
	void	*res;

	if (!size && ptr)
	{
		free(ptr);
		return (ft_strdup(""));
	}
	res = ft_calloc(1, size);
	if (ptr)
	{
		ft_memmove(res, ptr, size);
		free(ptr);
	}
	return (res);
}
