/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:42:54 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/18 01:22:40 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// RD, WR
#include <fcntl.h>		// open
#include "parser.h"		// t_token, t_type
#include "libft.h"		// get_next_line, ft_putstr_fd

char	**get_argv(t_token **input)
{
	t_token	**aux;
	char	**res;

	res = NULL;
	while (input && (*input)->type != COMMAND)
		++input;
	aux = input;
	while (aux && (*aux)->type == COMMAND)
		++aux;
	if (aux && (*aux)->str)
	{
		free((*aux)->str);
		(*aux)->str = NULL;
	}
	return (res);
}

void	write_fd(int old, int new)
{
	char	*str;

	str = get_next_line(old);
	while (str)
	{
		ft_putstr_fd(str, new);
		free(str);
		str = get_next_line(old);
	}
}
