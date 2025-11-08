/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:24:29 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/11 17:50:22 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrixjoin(char **matrix, char *node)
{
	size_t	len;
	char	**res;

	len = ft_matrix_len(matrix);
	res = ft_calloc(sizeof(char *), len + 2);
	if (!res)
		return (NULL);
	res = ft_matrixcpy(matrix, res, len);
	if (res)
		res[len] = ft_strdup(node);
	return (res);
}
