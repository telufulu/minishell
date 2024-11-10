/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/10 18:06:47 by aude-la-         ###   ########.fr       */
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
	reset_signal_handlers_to_default();
	redin_child(oldfd, c);
	redout_child(pipefd, (c->next != NULL), c);
	if (!c->outfd && !c->next && is_built(c->data->builts, c->cmd))
		exit(EXIT_SUCCESS);
	else
	{
		c->data->exit_status = my_execve(c, c->data->builts, env);
		exit(c->data->exit_status);
	}
}

//static void	father_process(pid_t pid, int *oldfd, int *pipefd, t_cmd *c)
//{
//	if (!c->next && is_built(c->data->builts, c->cmd) && !c->outfd)
//		c->data->exit_status = my_execve(c, c->data->builts, c->data->env);
//	*oldfd = redir_father(*oldfd, pipefd, (c->next != NULL));
//}

void wait_for_children(pid_t *pid_array, int cmd_count, t_data *d)
{
    int status;
	int	i;

	ignore_signals_in_parent();
	i = -1;
    while (++i < cmd_count)
    {
        waitpid(pid_array[i], &status, 0);
        d->exit_status = get_exit_status(status);
    }
	restore_parent_signal_handlers();
}

void main_executor(t_data *d, t_cmd *c)
{
    pid_t      pid_array[256];
    pid_t      pid;
    int        cmd_count = 0;
    int        pipefd[2];
    int        oldfd;
    t_builts   builts[N_BUILTINGS];

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
        {
            pid_array[cmd_count++] = pid;
//            father_process(pid, &oldfd, pipefd, c);
			if (!c->next && is_built(c->data->builts, c->cmd) && !c->outfd)
				c->data->exit_status = my_execve(c, c->data->builts, c->data->env);
			oldfd = redir_father(oldfd, pipefd, (c->next != NULL));
        }
        c = c->next;
    }
	if (oldfd != -1)
		close(oldfd);
	wait_for_children(pid_array, cmd_count, d);
}


//void	main_executor(t_data *d, t_cmd *c)
//{
//	pid_t		pid;
//	int			pipefd[2];
//	int			oldfd;
//	t_builts	builts[N_BUILTINGS];
//
//	d->builts = init_builtings(builts, d->env);
//	oldfd = -1;
//	while (d && c)
//	{
//		d->exit_status = 0;
//		if (pipe(pipefd) < 0)
//			ft_error("pipe failed", strerror(errno));
//		pid = fork();
//		if (pid < 0)
//			ft_error("fork failed", strerror(errno));
//		else if (!pid)
//			child_process(&oldfd, pipefd, c, d->env);
//		else
//			father_process(pid, &oldfd, pipefd, c);
//		c = c->next;
//	}
//	close(oldfd);
//}
