/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/15 18:45:17 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // t_data, access
#include "executor.h" // t_cmd
#include "libft.h" // ft_calloc, ft_error, strrerror
#include "token.h" // PIPE, INFD, OUTFD
#include <fcntl.h> // open

size_t	count_cmds(char *tokens)
{
	size_t	n;

	n = 1;
	while (tokens && *tokens)
	{
		if (*tokens == PIPE)
			++n;
		++tokens;
	}
	return (n);
}

size_t	count_args(char *tokens)
{
	size_t	res;

	res = 0;
	while (tokens && *tokens && *tokens != PIPE)
	{
		if (*tokens == ARG || *tokens == CMD)
			++res;
		++tokens;
	}
	return (res);
}

// This function moves params and tokens to the next cmd, in other words,
// it moves params and tokens behind the next PIPE
void	mv_params(char *tokens, char **params, size_t i, t_cmd *c)
{
	if (i > 0)
	{
		ft_printf("ENTRO\n");
		while (tokens && *tokens && *tokens != PIPE && i > 0)
		{
			++tokens;
			++params;
			if (*tokens == PIPE)
				--i;
		}
		c->params = params + 1;
		c->tokens = tokens + 1;
	}
	else
	{
		c->params = params;
		c->tokens = tokens;
	}
}

size_t	next_pipe(char *tokens)
{
	size_t	res;

	res = 0;
	while (tokens && tokens[res] && tokens[res] != PIPE)
		++res;
	return (res);
}
