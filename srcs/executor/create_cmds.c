/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/21 20:09:05 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h" // ft_shell_error
#include "minishell.h" // t_data, access, strerror
#include "executor.h" // t_cmd, get_ex_args, next_param
#include "libft.h" // ft_calloc, ft_error
#include "token.h" // PIPE, INFD, OUTFD
#include <fcntl.h> // open

int open_infiles(t_data *d, int in)
{
	int	i;

	i = 0;
	while (d->tokens && d->tokens[i] && d->tokens[i] != PIPE)
	{
		if (d->tokens[i] == INFD)
		{
			if (in)
				close(in);
			in = open(d->params[i], O_CREAT | O_RDONLY, 0644);
			if (in == -1)
				ft_error("unable to open infile", NULL);
		}
		++i;
	}
	return (in);
}

int open_outfiles(t_data *d, int out)
{
	int	i;

	i = 0;
	while (d->tokens && d->tokens[i] && d->tokens[i] != PIPE)
	{
		if (d->tokens[i] == OUTFD)
		{
			if (out)
				close(out);
			out = open(d->params[i], O_CREAT | O_WRONLY, 0644);
			if (out == -1)
				ft_error("unable to open outfd", NULL);
		}
		++i;
	}
	return (out);
}

t_cmd	*init_cmd(t_data *d, size_t n)
{
	t_cmd	*res;

	res = ft_calloc(sizeof(t_data), 1);
	if (!res)
		ft_error("malloc failed",strerror(errno));
	res->data = d;
	res->infd = open_infiles(res->data, res->infd);
	res->outfd = open_outfiles(res->data, res->outfd);
	res->argv = get_ex_args(next_params(d->params, n), d->tokens);
	res->path = get_path(ft_strjoin("/", res->argv[0]), d->env);
	return (res);
}

t_cmd	**create_cmds(size_t nb_cmds, t_data *d)
{
	t_cmd	**res;
	size_t	i;

	i = 0;
	res = ft_calloc(sizeof(t_cmd *), nb_cmds + 1);
	if (!res)
		ft_error("malloc failed", strerror(errno));
	while (i < nb_cmds)
	{
		res[i] = init_cmd(d, i);
		++i;
	}
	return (res);
}
