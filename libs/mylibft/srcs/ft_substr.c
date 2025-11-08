/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:01:59 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/27 14:53:13 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		i;
	size_t	s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (*s == '\0' || start >= s_len)
		return (ft_calloc(sizeof(char), 1));
	if (len > (s_len - start))
		len = s_len - start;
	res = ft_calloc(sizeof(char), (len) + 1);
	if (!res)
		return (NULL);
	while (s[start] && len--)
		res[i++] = s[start++];
	return (res);
}
