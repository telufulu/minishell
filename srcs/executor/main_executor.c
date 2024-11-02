/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/27 19:54:10 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD, redir_child, redir_father
#include "lexer.h"		// t_cmd
#include "parser.h"		// t_token, REDIRECT_IN
#include "minishell.h"	// t_data, ft_shell_error, execve
#include "libft.h"		// ft_error, ft_strcmp
#include "builtings.h"	// my_execve

static void	child_process(int *oldfd, int *pipefd, t_cmd *c, char **env)
{
	redin_child(oldfd, c);
	redout_child(pipefd, (c->next != NULL), c);
	exit(my_execve(c, env));
}

void	father_process(pid_t pid, int *oldfd, int *pipefd, t_cmd *c)
{
	waitpid(pid, &c->data->exit_status, 0);
	*oldfd = redir_father(*oldfd, pipefd, (c->next != NULL));
}

void	main_executor(t_data *d, t_cmd *c)
{
	pid_t	pid;
	int		pipefd[2];
	int		oldfd;

	oldfd = -1;
	while (d && c)
	{
		if (!c->next && !ft_strncmp("exit", c->cmd, 5))
			exit(exit_built(c, d->env));
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			ft_error("fork failed", strerror(errno));
		else if (!pid)
			child_process(&oldfd, pipefd, c, d->env);
		else
			father_process(pid, &oldfd, pipefd, c);
		//ft_free_matrix((void **)c->ex_argv);
		c = c->next;
	}
	close(oldfd);
}
