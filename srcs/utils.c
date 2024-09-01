/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:16:55 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/01 17:54:39 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*result;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	result = malloc(size);
	if (!result)
		return (NULL);
	if (ptr)
	{
		ft_memmove(result, ptr, size);
		free(ptr);
	}
	return (result);
}
