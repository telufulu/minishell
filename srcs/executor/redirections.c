/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:53:09 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/10 17:34:54 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>		// open
#include "executor.h"	// RD, WR

void	redin_child(int *oldfd, t_cmd *c)
{
	if (c->infd)
	{
		if (*oldfd != -1)
			close(*oldfd);
		*oldfd = open(c->infd, O_CREAT | O_RDONLY, 0644);
		if (*oldfd < 0)
			ft_shell_error(c->infd, "Permission denied", errno);
	}
	if (*oldfd != -1)
	{
		dup2(*oldfd, STDIN_FILENO);
		close(*oldfd);
		*oldfd = -1;
	}
}

void	redout_child(int *pipefd, t_bool next, t_cmd *c)
{
	if (c->outfd)
	{
		close(pipefd[WR]);
		pipefd[WR] = open(c->outfd, O_CREAT | O_WRONLY, 0644);
		if (pipefd[WR] < 0)
			ft_shell_error(c->outfd, "Permission denied", errno);
		dup2(pipefd[WR], STDOUT_FILENO);
		close(pipefd[WR]);
	}
	else if (next)
	{
		dup2(pipefd[WR], STDOUT_FILENO);
		close(pipefd[WR]);
	}
	if (pipefd[RD] != -1)
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
