/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/24 19:48:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD, redir_child, redir_father
#include "lexer.h"		// t_cmd
#include "parser.h"		// t_token, REDIRECT_IN
#include "minishell.h"	// t_data, ft_shell_error, execve
#include "libft.h"		// ft_error

static void	child_process(int *oldfd, int *pipefd, t_cmd *c, char **env)
{
	redin_child(oldfd, c);
	redout_child(pipefd, (c->next != NULL), c);
	execve(c->path, c->ex_argv, env);
	exit(EXIT_FAILURE);
}

static int	father_process(pid_t pid, int *oldfd, int *pipefd, t_cmd *c)
{
	int	status;

	waitpid(pid, &status, 0);
	*oldfd = redir_father(*oldfd, pipefd, (c->next != NULL));
	return (status);
}

void	main_executor(t_data *d, t_cmd *c)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];
	int		oldfd;

	(void)status;
	oldfd = -1;
	while (d && c)
	{
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			ft_error("fork failed", strerror(errno));
		else if (!pid)
			child_process(&oldfd, pipefd, c, d->env);
		else
			status = father_process(pid, &oldfd, pipefd, c);
		c = c->next;
	}
	close(oldfd);
}
