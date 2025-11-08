/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:10:07 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/06 20:56:07 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*aux;
	int		i;

	aux = (char *)s;
	i = 0;
	while (aux[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (aux[i] == (char)c)
			return (aux + i);
		i--;
	}
	return (0);
}
