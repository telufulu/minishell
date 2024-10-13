/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/13 23:55:42 by telufulu         ###   ########.fr       */
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
	//int		infd;
	//int		outfd;

	pid = 0;
	while (d && c)
	{
		if (pipe(pipefd) < 0)
			ft_error("Pipe command failed", strerror(errno));
		if (!c->index && c->next)
			dup2(pipefd[WR], STDOUT_FILENO);
		else if (c->index && c->next)
			dup2(STDOUT_FILENO, pipefd[WR]);
		if (c->index)
			dup2(pipefd[RD], STDIN_FILENO);
		/*if (c->infd)
			if (open_fd(&infd, c->input, REDIRECT_IN) < 0)
				ft_shell_error(c->infd, "Perminision denied");
		if (c->outfd)
			if (open_fd(&outfd, c->input, REDIRECT_OUT) < 0)
				ft_shell_error(c->outfd, "Perminision denied");
		*/

		pid = fork();
		if (pid < 0)
			ft_error("fork failed", strerror(errno));
		else if (!pid)
		{
			execve(c->path, c->ex_argv, d->env);
			exit(EXIT_SUCCESS);
		}
		else
		{
			c = c->next;
			wait(&status);
		}
	}
}
