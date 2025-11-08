/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:31:57 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/02 00:47:56 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			i++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (i);
}

static size_t	next_word(char const **s, char c)
{
	size_t	i;

	i = 0;
	while (**s == c)
		(*s)++;
	while (s[0][i] != c && s[0][i] != '\0')
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	nb_words;
	char	**res;
	size_t	i;
	size_t	len_word;

	i = 0;
	nb_words = count_words(s, c);
	if (!s)
		return (NULL);
	res = ft_calloc(sizeof(char *), nb_words + 1);
	if (!res)
		return (NULL);
	while (i < nb_words)
	{
		len_word = next_word(&s, c);
		res[i] = ft_calloc(sizeof(char), len_word + 1);
		if (!res[i])
			return (ft_free_matrix(res));
		ft_strlcpy(res[i++], s, len_word + 1);
		s += len_word;
	}
	return (res);
}
