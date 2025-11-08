/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:34:19 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/02 00:48:39 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrixcpy(char **org, char **new, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && org[i])
	{
		new[i] = ft_strdup(org[i]);
		if (!new[i])
		{
			ft_free_matrix(new);
			return (NULL);
		}
		++i;
	}
	return (new);
}

char	**ft_matrixdup(char **org, size_t len)
{
	char	**new;

	new = ft_calloc(sizeof(char *), len);
	if (!new)
		return (NULL);
	new = ft_matrixcpy(org, new, len);
	return (new);
}
