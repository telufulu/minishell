/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 23:03:41 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/04 00:19:51 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" //t_data
#include "parser.h"

void	is_outfl(char **res, char params, int i)
{
	if (params == '<')
	{
		*res[i + 1] = OUTFL;
		*res[i] = OPER;
	}
	else
		*res[i] = 42;
}

void	is_infl(char **res, char params, int i)
{
	if (params && params == '<')
	{
		*res[i] = INFL;
		*res[i + 1] = OPER;
	}
	else
		*res[i] = 42;
}

char	*tokenizer(char **params)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(sizeof(char), ft_matrix_len(params) + 1);
	while (res && params[i] && params[i])
	{
		if (!res[i])
		{
			is_infl(&res, (*params)[i + 1], i);
			is_outfl(&res, (*params)[i], i);
		}
		++i;
		ft_putchar_fd(res[i], 1);
	}
	ft_putchar_fd('\n', 1);
	return (res);
}
