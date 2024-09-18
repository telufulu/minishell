/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/18 20:03:49 by telufulu         ###   ########.fr       */
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

size_t	next_pipe(char *tokens)
{
	size_t	res;

	res = 0;
	while (tokens && tokens[res] && tokens[res] != PIPE)
		++res;
	return (res);
}
