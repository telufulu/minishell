/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:05:05 by telufulu          #+#    #+#             */
/*   Updated: 2023/11/16 22:05:10 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_base(int nb, char *base)
{
	unsigned int	nbr;
	unsigned int	bs;
	size_t			nb_chars;
	int				aux;

	nb_chars = 0;
	nbr = 0;
	bs = ft_strlen(base);
	if (nb < 0 && bs == 10)
	{
		nb_chars += write(1, "-", 1);
		nbr = nb * -1;
	}
	else
		nbr = nb;
	if (nbr > bs - 1)
		nb_chars += ft_putnbr_base((nbr / bs), base);
	aux = (nbr % bs);
	nb_chars += write(1, &base[aux], 1);
	return (nb_chars);
}
