/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/04 18:21:53 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD, redir_child, redir_father
#include "lexer.h"		// t_cmd
#include "parser.h"		// t_token, REDIRECT_IN
#include "minishell.h"	// t_data, ft_shell_error, execve
#include "libft.h"		// ft_error, ft_strcmp
#include "builtings.h"	// my_execve, is_built

static void	child_process(int *oldfd, int *pipefd, t_cmd *c, char **env)
{
	redin_child(oldfd, c);
	redout_child(pipefd, (c->next != NULL), c);
	if (!c->next && is_built(c->data->builts, c->cmd))
		exit(EXIT_SUCCESS);
	else
		c->data->exit_status = my_execve(c, c->data->builts, env);
	exit(c->data->exit_status);
}

static void	father_process(pid_t pid, int *oldfd, int *pipefd, t_cmd *c)
{
	waitpid(pid, &c->data->exit_status, 0);
	if (!c->next && is_built(c->data->builts, c->cmd))
		c->data->exit_status = my_execve(c, c->data->builts, c->data->env);
	*oldfd = redir_father(*oldfd, pipefd, (c->next != NULL));
}

void	main_executor(t_data *d, t_cmd *c)
{
	pid_t	pid;
	int		pipefd[2];
	int		oldfd;
	t_builts	builts[N_BUILTINGS];

	d->builts = init_builtings(builts, d->env);
	oldfd = -1;
	while (d && c)
	{
		d->exit_status = 0;
		if (pipe(pipefd) < 0)
			ft_error("pipe failed", strerror(errno));
		pid = fork();
		if (pid < 0)
			ft_error("fork failed", strerror(errno));
		else if (!pid)
			child_process(&oldfd, pipefd, c, d->env);
		else
			father_process(pid, &oldfd, pipefd, c);
		c = c->next;
	}
	close(oldfd);
}
