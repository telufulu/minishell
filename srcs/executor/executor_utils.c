/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/25 20:03:12 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"		// ft_shell_error
#include "executor.h"	// t_cmd
#include "token.h"		// PIPE, INFD, OUTFD
#include "minishell.h"	// size_t
#include "libft.h"		// ft_calloc, ft_error
#include <fcntl.h>		// open

int open_infiles(t_data *d, int in)
{
	int	i;

	i = 0;
	while (d->tokens && d->tokens[i] && d->tokens[i] != PIPE)
	{
		if (d->tokens[i] == INFD)
		{
			if (in)
				close(in);
			in = open(d->params[i], O_CREAT | O_RDONLY, 0644);
			if (in == -1)
				ft_error("unable to open infile", NULL);
		}
		++i;
	}
	return (in);
}

int open_outfiles(t_data *d, int out)
{
	int	i;

	i = 0;
	while (d->tokens && d->tokens[i] && d->tokens[i] != PIPE)
	{
		if (d->tokens[i] == OUTFD)
		{
			if (out)
				close(out);
			out = open(d->params[i], O_CREAT | O_WRONLY, 0644);
			if (out == -1)
				ft_error("unable to open outfd", NULL);
		}
		++i;
	}
	return (out);
}

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

size_t	next_pipe(char *tokens)
{
	size_t	res;

	res = 0;
	while (tokens && tokens[res] && tokens[res] != PIPE)
		++res;
	return (res);
}
