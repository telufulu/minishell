/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 00:28:47 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/12 01:39:32 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // strerror
#include "libft.h" // ft_calloc, ft_error, ft_matrix_len
#include "token.h" // OPER, INFD, OUTFD, PIPE, WORD

char	*redirs(char *res, char **params)
{
	int		i;

	i = 0;
	while (params && params[i] && *params[i])
	{
		if (i && !res[i] && *params[i] == '<')
		{
			res[i - 1] = INFD;
			res[i] = OPER;
		}
		else if (!res[i] && *params[i] == '>')
		{
			res[i + 1] = OUTFD;
			res[i] = OPER;
		}
		else if (!res[i] && *params[i] == PIPE)
			res[i] = PIPE;
		++i;
	}
	return (res);
}

char	*cmd_arg(char *res, char **params)
{
	int		i;
	t_bool	check;

	i = 0;
	check = false;
	while (params && params[i] && *params[i])
	{
		if (!check && !res[i])
		{
			res[i] = CMD;
			check = true;
		}
		else if (check && !res[i])
			res[i] = ARG;
		else if (check && res[i] == PIPE)
			check = false;
		++i;
	}
	return (res);
}

char	*tokenizer(char **params)
{
	char	*res;

	res = ft_calloc(sizeof(char), ft_matrix_len(params) + 1);
	if (!res)
		ft_error("malloc failed", strerror(errno));
	res = redirs(res, params);
	res = cmd_arg(res, params);
	return (res);
}
