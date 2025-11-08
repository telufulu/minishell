/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:19:20 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/17 18:46:35 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	n;

	n = 0;
	res = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	while (s[n])
	{
		res[n] = (*f)(n, s[n]);
		n++;
	}
	return (res);
}
