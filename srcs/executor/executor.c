/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:50:41 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/25 20:17:25 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, strerror
#include "executor.h"	// t_cmd
#include "libft.h"		// ft_error

void	execute_cmd(t_data *d, size_t i)
{
	t_cmd	*c;

	c = init_cmd(d, i);
	if (c && c->path && c->argv && \
		execve(c->path, c->argv, c->data->env) == -1)
		ft_error("execve failed", strerror(errno));
	ft_free_matrix((void **)c);
}

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

void	executor(t_data *d)
{
	int		status;
	size_t	i;
	size_t	cmd_num;
	pid_t	pid;

	i = 0;
	cmd_num = count_cmds(d->tokens);
	while (i < cmd_num)
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork failed", strerror(errno));
		else if (!pid)
		{
			execute_cmd(d, i);
			exit(EXIT_SUCCESS);
		}
		++i;
	}
	if (pid)
		wait(&status);
}
