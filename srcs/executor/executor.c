/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/14 12:02:52 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // t_data, access
#include "executor.h" // t_cmd
#include "libft.h" // ft_calloc, ft_error, strrerror
#include "token.h" // PIPE, INFD, OUTFD
#include <fcntl.h> // open

size_t	count_cmds(char *tokens)
{
	size_t	n;

	n = 1;
	while (tokens && *tokens)
	{
		if (*tokens == PIPE)
			++n;
		++tokens;
	}
	return (n);
}

int open_infiles(t_data *d, int in)
{
	int	i;

	i = 0;
	while (d->tokens && d->tokens[i] && d->tokens[i] != PIPE)
	{
		if (d->tokens[i] == INFD)
		{
			in = open(d->params[i], O_RDWR | O_CREAT | 744);
			return (in);
		}
		++i;
	}
	return (0);
}

int open_outfiles(t_data *d, int out)
{
	int	i;

	i = 0;
	while (d->tokens[i] && d->tokens[i] != INFD && d->tokens[i] != PIPE)
	{
		if (d->tokens[i] == OUTFD)
		{
			if (out)
				close(out);
			out = open(d->params[i], O_RDWR | O_CREAT | 744);
			return (out);
		}
		++i;
	}
	return (0);
}
t_cmd	*init_cmd(t_data *d)
{
	t_cmd	*res;

	res = ft_calloc(sizeof(t_data), 1);
	if (!res)
		ft_error("malloc failed", strerror(errno));
	res->data = d;
	res->infd = open_infiles(d, res->infd);
	res->outfd = open_infiles(d, res->outfd);
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
		res[i] = init_cmd(d);
		i++;
	}
	return (res);
}

void	executor(t_data *d)
{
	t_cmd	**c;

	c = create_cmds(count_cmds(d->tokens), d);
	ft_printf("tokens: %s\n", c[0]->data->tokens);
	ft_printf("fd in: %i\n", c[0]->infd);
	ft_printf("fd out: %i\n", c[0]->outfd);
}
