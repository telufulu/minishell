/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:53:41 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/09 22:01:19 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(sizeof(char), (ft_strlen(s1) + 1));
	if (!res)
		return (0);
	while (s1 && s1[i] != '\0')
	{
		res[i] = s1[i];
		++i;
	}
	return (res);
}
