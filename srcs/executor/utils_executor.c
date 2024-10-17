/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:42:54 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/17 21:50:10 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// RD, WR
#include <fcntl.h>		// open
#include "parser.h"		// t_token, t_type
int	open_fd(int *fd, t_token **tokens, t_type tp)
{
	while (tokens && *tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == tp)
		{
			++tokens;
			if (*fd > 2)
				close(*fd);
			if (tp == REDIRECT_IN)
				*fd = open((*tokens)->str, O_CREAT | O_RDONLY, 0644);
			else if (tp == REDIRECT_OUT)
				*fd = open((*tokens)->str, O_CREAT | O_WRONLY, 0644);
			if (*fd < 0)
				ft_shell_error((*tokens)->str, "Permission denied");
		}
		++tokens;
	}
	return (*fd);
}

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

void	redir_child(int oldfd, int *pipefd, t_bool next)
{
	if (oldfd != -1)
	{
		dup2(oldfd, STDIN_FILENO);
		close(oldfd);
	}
	if (next)
	{
		dup2(pipefd[WR], STDOUT_FILENO);
		close(pipefd[WR]);
	}
	close(pipefd[RD]);
}

int	redir_father(int oldfd, int *pipefd, t_bool next)
{
	if (oldfd != -1)
		close(oldfd);
	if (next)
		close(pipefd[WR]);
	return (pipefd[RD]);
}
