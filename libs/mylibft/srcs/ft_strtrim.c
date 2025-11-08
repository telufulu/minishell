/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:42:53 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/13 16:17:02 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*res;

	start = 0;
	end = ft_strlen(s1) - 1;
	i = 0;
	if (!*s1)
		return (ft_calloc(sizeof(char), 1));
	while (ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[end]))
		end--;
	while ((i + start) <= end)
		i++;
	i++;
	res = ft_calloc(sizeof(char), i);
	if (!res)
		return (NULL);
	ft_strlcpy(res, (s1 + start), i);
	return (res);
}
