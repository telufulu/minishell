/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:34:01 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/17 21:06:36 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_num(unsigned int x)
{
	size_t	i;

	i = 0;
	if (x == 0)
		return (1);
	while (x)
	{
		x /= 10;
		i++;
	}
	return (i);
}

static unsigned int	get_num(unsigned int x, size_t len)
{
	while (len--)
		x /= 10;
	return (x);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	x;
	size_t			len;
	char			c;

	if (n < 0)
	{
		x = n * -1;
		write(fd, "-", 1);
	}
	else
		x = n;
	len = len_num(x);
	while (len)
	{
		c = (get_num(x, --len) % 10) + '0';
		write(fd, &c, 1);
	}
}
