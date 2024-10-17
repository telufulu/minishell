/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/17 20:22:31 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD
#include "lexer.h"		// t_cmd
#include "parser.h"		// t_token, REDIRECT_IN
#include "minishell.h"	// t_data, ft_shell_error, execve
#include "libft.h"		// ft_error

void	main_executor(t_data *d, t_cmd *c)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];
	int		oldfd;

	while (d && c)
	{
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			ft_error("fork failed", strerror(errno));
		else if (!pid)
		{
			if (c->next)
			{
				close(pipefd[RD]);
				dup2(pipefd[WR], STDOUT_FILENO);
				close(pipefd[WR]);
			}
			if (c->index)
			{
				dup2(oldfd, STDIN_FILENO);
			}
			execve(c->path, c->ex_argv, d->env);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
			oldfd = dup(pipefd[RD]);
			c = c->next;
		}
	}
}
