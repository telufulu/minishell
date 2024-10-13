/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/13 18:14:31 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD
#include "lexer.h"		// t_cmd
#include "parser.h"		// t_token, REDIRECT_IN
#include "minishell.h"	// t_data, ft_shell_error, execve
#include "libft.h"		// ft_error

void	redir_files(t_cmd *c, int index, int pipe_in, int pipe_out)
{
	int	infd;
	int	outfd;

	if (!index && c->next)
		dup2(pipe_out, STDOUT_FILENO);
	else if (index && !c->next)
		dup2(STDOUT_FILENO, pipe_out);
	if (index)
		dup2(pipe_in, STDIN_FILENO);
	if (c->infd)
	{
		if (open_fd(&infd, c->input, REDIRECT_IN) < 0)
			ft_shell_error(c->infd, strerror(errno));
		if (index)
			dup2(infd, STDIN_FILENO);
	}
	if (c->outfd)
	{
		if (open_fd(&outfd, c->input, REDIRECT_OUT) < 0)
			ft_shell_error(c->outfd, strerror(errno));
		if (c->next)
			dup2(outfd, STDOUT_FILENO);
	}
}

void	main_executor(t_data *d, t_cmd *c)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];

	pid = 0;
	while (d && c)
	{
		if (pipe(pipefd) < 0)
			ft_error("Pipe command failed", strerror(errno));
		pid = fork();
		if (pid < 0)
			ft_error("fork failed", strerror(errno));
		else if (!pid)
		{
			redir_files(c, c->index, pipefd[RD], pipefd[WR]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			c = c->next;
			wait(&status);
		}
	}
}
