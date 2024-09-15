/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/15 13:39:12 by telufulu         ###   ########.fr       */
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

int open_infiles(t_cmd *d, int in)
{
	int	i;

	i = 0;
	while (d->tokens && d->tokens[i] && d->tokens[i] != PIPE)
	{
		if (d->tokens[i] == INFD)
		{
			if (in)
				close(in);
			ft_printf("in: %i\n", in);
			in = open(d->params[i], O_CREAT | O_RDONLY, 0644);
			if (in == -1)
				ft_error("something happend (infd)", NULL);
		}
		++i;
	}
	return (in);
}

int open_outfiles(t_cmd *d, int out)
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

size_t	count_args(char *tok)
{
	size_t	res;

	res = 0;
	while (tok && *tok && *tok != PIPE)
	{
		if (*tok == ARG || *tok == CMD)
			++res;
		++tok;
	}
	return (res);
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

// This function moves params and tokens to the next cmd, in other words,
// it moves params and tokens behind the next PIPE
void	mv_params(char *tokens, char **params, size_t i, t_cmd *c)
{
	if (i)
	{
		while (tokens && *tokens && *tokens != PIPE && i)
		{
			++tokens;
			++params;
			if (*tokens == PIPE)
				--i;
		}
		c->params = params + 1;
		c->tokens = tokens + 1;
	}
	else
	{
		c->params = params;
		c->tokens = tokens;
	}
}

t_cmd	*init_cmd(t_data *d, size_t i)
{
	t_cmd	*res;

	res = ft_calloc(sizeof(t_data), 1);
	if (!res)
		ft_error("malloc failed", strerror(errno));
	res->data = d;
	mv_params(d->tokens, d->params, i, res);
	res->infd = open_infiles(res, res->infd);
	res->outfd = open_outfiles(res, res->outfd);
	res->argv = get_ex_args(res->params, res->tokens);
	//res->path = get_path(res->argv[0]);
	return (res);
}

size_t	next_pipe(char *tokens)
{
	size_t	res;

	res = 0;
	while (tokens && tokens[res] && tokens[res] != PIPE)
		++res;
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

void	executor(t_data *d)
{
	t_cmd	**c;

	ft_printf("%s\n", d->tokens);
	c = create_cmds(count_cmds(d->tokens), d);
	ft_print_matrix(c[0]->argv, 1);
	ft_printf("------------\n");
	if (c[1])
		ft_print_matrix(c[1]->argv, 1);
	// si path está vacío saltará el error de cmd no encontrado
	ft_free_matrix((void **)c);
}
