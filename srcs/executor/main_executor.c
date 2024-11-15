/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/15 13:16:27 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD, redir_child, redir_father
#include "lexer.h"		// t_cmd
#include "parser.h"		// t_token, REDIRECT_IN
#include "minishell.h"	// t_data, ft_shell_error, execve
#include "libft.h"		// ft_error, ft_strcmp
#include "builtings.h"	// my_execve, is_built

static void	child_process(t_pipes *pip, t_cmd *c, char **env)
{
	reset_signal_handlers_to_default();
	redin_child(&pip->oldfd, c, c->heredoc_fd);
	redout_child(pip->pipefd, (c->next != NULL), c);
	if (!c->outfd && !c->appendfd && !c->next
		&& is_built(c->data->builts, c->cmd))
		exit(EXIT_SUCCESS);
	else
	{
		c->data->exit_status = my_execve(c, c->data->builts, env);
		exit(c->data->exit_status);
	}
}

static void	wait_for_children(t_pipes *pip, t_data *d)
{
	int	status;
	int	i;

	ignore_signals_in_parent();
	i = -1;
	while (++i < pip->cmd_count)
	{
		waitpid(pip->pid_array[i], &status, 0);
		d->exit_status = get_exit_status(status);
	}
	restore_parent_signal_handlers();
}

static void	create_child_process(t_pipes *pip, t_cmd *c, char **env)
{
	if (c->next)
		if (pipe(pip->pipefd) < 0)
			ft_error("pipe failed", strerror(errno));
	pip->pid = fork();
	if (pip->pid < 0)
		ft_error("fork failed", strerror(errno));
	else if (pip->pid == 0)
		child_process(pip, c, env);
}

static int	handle_command(t_data *d, t_pipes *pip, t_cmd *c, char **env)
{
	if (find_heredoc(c))
	{
		c->heredoc_fd = handle_heredoc(c);
		if (c->heredoc_fd == -1)
			return (d->exit_status = 1, -1);
	}
	create_child_process(pip, c, env);
	if (pip->pid > 0)
	{
		pip->pid_array[pip->cmd_count++] = pip->pid;
		if (!c->next && is_built(c->data->builts, c->cmd)
			&& !c->outfd && !c->appendfd)
			d->exit_status = my_execve(c, c->data->builts, d->env);
		pip->oldfd = redir_father(pip->oldfd, pip->pipefd, (c->next != NULL));
		if (c->heredoc_fd != -1)
		{
			close(c->heredoc_fd);
			c->heredoc_fd = -1;
		}
	}
	return (0);
}

void	main_executor(t_data *d, t_cmd *c)
{
	t_pipes		pip;
	t_builts	builts[N_BUILTINGS];

	d->builts = init_builtings(builts, d->env);
	pip.oldfd = -1;
	pip.cmd_count = 0;
	while (d && c)
	{
		d->exit_status = 0;
		c->heredoc_fd = -1;
		if (handle_command(d, &pip, c, d->env) == -1)
			return ;
		c = c->next;
	}
	if (pip.oldfd != -1)
		close(pip.oldfd);
	wait_for_children(&pip, d);
}
