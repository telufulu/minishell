/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/16 14:10:58 by aude-la-         ###   ########.fr       */
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
//	char	buffer[3];

//	buffer[2] = 0;
	while (d && c)
	{
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			ft_error("fork failed", strerror(errno));
		else if (!pid)
		{
			close(pipefd[RD]);
			if ((!c->index && c->next) || (c->index && c->next))
				dup2(STDOUT_FILENO, pipefd[WR]);
			else if ((c->next && c->index) || c->index)
				dup2(STDIN_FILENO, pipefd[RD]);
			execve(c->path, c->ex_argv, d->env);
			exit(EXIT_SUCCESS);
		}
		else
		{
			c = c->next;
			close(pipefd[WR]);
			wait(&status);
		}
	}
}
