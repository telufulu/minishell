/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:47:57 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/09 15:28:09 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"	// t_cmd
#include "parser.h"	// PIPE
#include "libft.h"	//ft_error, strerror, errno

t_cmd	*last_cmd(t_cmd *c)
{
	while (c && c->next)
		c = c->next;
	return (c);
}

t_cmd	*new_cmd(void)
{
	t_cmd *res;

	res = ft_calloc(sizeof(t_cmd), 1);
	if (!res)
		ft_error("malloc failed", strerror(errno));
	return (res);
}

t_cmd	*add_cmd(t_data *d)
{
	t_cmd	*last;

	last = last_cmd(d->cmd);
	if (!last)
	{
		d->cmd = new_cmd();
		last = d->cmd;
	}
	else
		last->next = new_cmd();
	return (last);
}

size_t	num_cmd(t_token **tokens)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 1;
	if (!tokens)
		return (0);
	while (tokens && tokens[i])
	{
		if (tokens[i]->type == PIPE)
			++len;
		++i;
	}
	return (len);
}
