/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_printf_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:24:13 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/12 20:17:36 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	conv_hex(va_list arg)
{
	size_t	i;
	int		d;

	d = va_arg(arg, int);
	i = ft_putnbr_base(d, "0123456789abcdef");
	return (i);
}

size_t	conv_heupx(va_list arg)
{
	size_t	i;
	int		d;

	d = va_arg(arg, int);
	i = ft_putnbr_base(d, "0123456789ABCDEF");
	return (i);
}

size_t	ft_putunsig(unsigned int nb)
{
	char	*base;
	size_t	nb_chars;
	int		aux;

	nb_chars = 0;
	base = "0123456789";
	if (nb > 9)
		nb_chars += ft_putunsig(nb / 10);
	aux = (nb % 10);
	nb_chars += write(1, &base[aux], 1);
	return (nb_chars);
}

size_t	ft_putptr(unsigned long long nb, char *base)
{
	unsigned long long	bs;
	size_t				nb_chars;
	int					aux;

	nb_chars = 0;
	bs = ft_strlen(base);
	if (nb > 15)
		nb_chars += ft_putptr((nb / bs), base);
	aux = (nb % bs);
	nb_chars += write(1, &base[aux], 1);
	return (nb_chars);
}

size_t	conv_perc(va_list arg)
{
	(void)arg;
	return (write(1, "%", 1));
}
