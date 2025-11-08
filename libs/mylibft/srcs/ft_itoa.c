/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 23:14:14 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/17 21:03:07 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_num(int n)
{
	size_t			i;
	unsigned int	num;

	i = 0;
	num = n;
	if (n == 0)
		i++;
	else if (n < 0)
	{
		num = n * -1;
		i++;
	}
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*set_num(char *s, int n, size_t len)
{
	unsigned int	num;
	size_t			i;

	i = 0;
	if (n < 0)
	{
		num = n * -1;
		s[i++] = '-';
	}
	else
		num = n;
	while (len-- > i)
	{
		s[len] = (num % 10) + '0';
		num /= 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	len_nb;

	len_nb = len_num(n);
	res = ft_calloc(sizeof(char), len_nb + 1);
	if (!res)
		return (NULL);
	return (set_num(res, n, len_nb));
}
