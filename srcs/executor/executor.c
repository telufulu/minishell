/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:50:41 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/02 02:03:26 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, strerror
#include "executor.h"	// t_cmd
#include "libft.h"		// ft_error

t_cmd	*init_cmd(t_data *d, size_t n)
{
	t_cmd	*res;

	res = ft_calloc(sizeof(t_data), 1);
	if (!res)
		ft_error("malloc failed", strerror(errno));
	res->data = d;
	res->infd = open_infiles(res->data, res->infd);
	res->outfd = open_outfiles(res->data, res->outfd);
	res->argv = get_ex_args(next_params(d->params, n), d->tokens);
	if (res->argv[0])
		res->path = get_path(ft_strjoin("/", res->argv[0]), d->env);
	else
		exit(EXIT_SUCCESS);
	return (res);
}

void	redirect(t_cmd *c, t_bool i, t_bool pipe, int *pipefd)
{
	if (c->infd)
		dup2(c->infd, STDIN_FILENO);
	else if (i)
		dup2(pipefd[0], STDIN_FILENO);
	if (c->outfd)
		dup2(c->outfd, STDOUT_FILENO);
	else if (pipe)
		dup2(pipefd[1], STDOUT_FILENO);
}

void	execute_cmd(t_data *d, size_t i, size_t cmd_num, int *pipefd)
{
	t_cmd	*c;

	c = init_cmd(d, i);
	if (c && (!c->path || !c->argv))
		exit(EXIT_SUCCESS);
	redirect(c, (i), (i < cmd_num - 1), pipefd);
	if (execve(c->path, c->argv, c->data->env) == -1)
		ft_error("execve failed", strerror(errno));
	ft_free_matrix((void **)c);
}

void	executor(t_data *d)
{
	int		status;
	size_t	i;
	size_t	cmd_num;
	int		pipefd[2];
	pid_t	pid;

	i = 0;
	cmd_num = count_cmds(d->tokens);
	while (i < cmd_num)
	{
		if (pipe(pipefd) == -1)
			ft_error("pipe creation failed", strerror(errno));
		pid = fork();
		if (pid < 0)
			ft_error("fork failed", strerror(errno));
		else if (!pid)
		{
			execute_cmd(d, i, cmd_num, pipefd);
			exit(EXIT_SUCCESS);
		}
		++i;
	}
	wait(&status);
}
