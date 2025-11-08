/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:42:16 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/11 22:25:53 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	conv_char(va_list arg)
{
	int		c;
	size_t	i;

	c = va_arg(arg, int);
	i = write(1, &c, 1);
	return (i);
}

size_t	conv_string(va_list arg)
{
	char	*s;
	size_t	i;

	i = 0;
	s = va_arg(arg, char *);
	if (s)
		i = write(1, s, ft_strlen(s));
	else if (!s)
		i = write(1, "(null)", 6);
	return (i);
}

size_t	conv_addrss(va_list arg)
{
	long long int		i;
	long long int		x;
	unsigned long int	p;

	i = 0;
	p = va_arg(arg, unsigned long long);
	i = write(1, "0x", 2);
	if (i < 0)
		return (i);
	x = ft_putptr(p, "0123456789abcdef");
	if (x < 0)
		return (x);
	return ((size_t)(i + x));
}

size_t	conv_dec(va_list arg)
{
	size_t	i;
	int		d;

	d = va_arg(arg, int);
	i = ft_putnbr_base(d, "0123456789");
	return (i);
}

size_t	conv_unsig(va_list arg)
{
	size_t	i;
	int		d;

	d = va_arg(arg, unsigned int);
	i = ft_putunsig(d);
	return (i);
}
