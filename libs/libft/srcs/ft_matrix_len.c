/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:18:45 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/02 01:15:16 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_matrix_len(char **matrix)
{
	size_t	len;

	len = 0;
	while (matrix && matrix[len])
		++len;
	return (len);
}
