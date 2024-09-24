/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ex_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:27:48 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/21 19:56:12 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h" // count_args
#include "token.h" // PIPE, CMD, ARG
#include "libft.h" // ft_calloc, ft_error
#include "minishell.h" // strerror

char	**next_params(char **params, size_t n)
{
	while (n && params && *params && **params)
	{
		if (**params == PIPE)
		{
			if (!n)
				return (params + 1);
			--n;
		}
		++params;
	}
	return (params);
}

char **get_ex_args(char **params, char *tok)
{
	char	**res;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	res = ft_calloc(sizeof(char *), count_args(tok));
	if (!res)
		ft_error("malloc failed", strerror(errno));
	while (tok && tok[i] && tok[i] != PIPE)
	{
		if (tok[i] == CMD || tok[i] == ARG)
			res[x++] = params[i];
		++i;
	}
	return (res);
}

