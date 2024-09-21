/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/21 17:52:34 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h" // ft_shell_error
#include "minishell.h" // t_data, access
#include "executor.h" // t_cmd
#include "libft.h" // ft_calloc, ft_error, strrerror
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
				ft_error("something happend (infd)", NULL);
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
				ft_error("something happend (outfd)", NULL);
		}
		++i;
	}
	return (out);
}

char **get_ex_args(char **params, char *tok)
{
	char	**res;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	res = ft_calloc(sizeof(char *), count_args(tok));
	if (!res)
		ft_error("malloc failed", strerror(errno));
	while (tok && tok[i] && tok[i] != PIPE)
	{
		if (tok[i] == CMD || tok[i] == ARG)
			res[x++] = params[i];
		++i;
	}
	return (res);
}

t_cmd	*init_cmd(t_data *d)
{
	t_cmd	*res;

	res = ft_calloc(sizeof(t_data), 1);
	if (!res)
		ft_error("malloc failed",strerror(errno));
	res->data = d;
	//res->infd = open_infiles(res, res->infd);
	//res->outfd = open_outfiles(res, res->outfd);
	res->argv = get_ex_args(d->params, d->tokens);
	res->path = get_path(ft_strjoin("/", res->argv[0]), d->env);
	if (!res->path)
		ft_shell_error(res->argv[0], ": command not found");
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
		res[i++] = init_cmd(d);
	return (res);
}
