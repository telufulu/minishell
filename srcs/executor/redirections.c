/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:53:09 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/12 19:52:33 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>		// open
#include "executor.h"	// RD, WR

static void	handle_heredoc_fd(int *oldfd, int heredoc_fd)
{
	if (*oldfd != -1)
	{
		close(*oldfd);
		*oldfd = -1;
	}
	dup2(heredoc_fd, STDIN_FILENO);
	if (heredoc_fd != STDIN_FILENO)
		close(heredoc_fd);
}

static void	handle_infd(int *oldfd, t_cmd *c)
{
	int	infd;

	if (*oldfd != -1)
	{
		dup2(*oldfd, STDIN_FILENO);
		close(*oldfd);
		*oldfd = -1;
	}
	if (c->infd)
	{
		infd = open(c->infd, O_RDONLY);
		if (infd < 0)
		{
			ft_shell_error(c->infd, "Permission denied", errno);
			return ;
		}
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
}

void	redin_child(int *oldfd, t_cmd *c, int heredoc_fd)
{
	if (heredoc_fd != -1)
		handle_heredoc_fd(oldfd, heredoc_fd);
	else
		handle_infd(oldfd, c);
}

void	redout_child(int *pipefd, t_bool next, t_cmd *c)
{
	int	outfile_fd;

	if (c->outfd)
	{
		outfile_fd = open(c->outfd, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile_fd < 0)
			ft_shell_error(c->outfd, "Permission denied", errno);
		dup2(outfile_fd, STDOUT_FILENO);
		if (outfile_fd != STDOUT_FILENO)
			close(outfile_fd);
	}
	else if (next)
		dup2(pipefd[WR], STDOUT_FILENO);
}

int	redir_father(int oldfd, int *pipefd, t_bool next)
{
	if (oldfd != -1)
		close(oldfd);
	if (next)
	{
		close(pipefd[WR]);
		return (pipefd[RD]);
	}
	return (-1);
}
