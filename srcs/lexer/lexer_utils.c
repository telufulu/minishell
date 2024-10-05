/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:47:57 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/05 15:30:09 by telufulu         ###   ########.fr       */
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

void	add_cmd(t_cmd *c)
{
	t_cmd *last;

	last = last_cmd(c);
	last->next = new_cmd();
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
