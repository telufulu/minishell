/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:03:07 by aude-la-          #+#    #+#             */
/*   Updated: 2024/08/30 16:04:55 by augustindelab    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_args(t_parser *p)
{
	if (*(p->s))
	{
		if (!define_length(p))
			return (0);
		if (p->length > 0)
		{
			p->tokens[p->count] = malloc(p->length + 1);
			if (!p->tokens[p->count])
				return (0);
			p->l = 0;
			while (p->start < p->s)
			{
				if (*(p->start) == '\'' && !is_heredoc(p))
					handle_single_quote(p);
				else if (*(p->start) == '"' && !is_heredoc(p))
					handle_double_quote(p);
				else
					handle_variable_expansion(p);
			}
			p->tokens[p->count][p->l] = '\0';
			(p->count)++;
		}
	}
	return (1);
}

char	**main_parser(t_data *d)
{
	t_parser	p;

	p.s = d->input;
	p.env = d->env;
	p.exit_code = d->exit_status;
	p.tokens = ft_calloc((ft_strlen(p.s) + 1), sizeof(char *));
	if (!p.tokens)
		return (NULL);
	p.count = 0;
	while (*(p.s) && p.count < MAX_TOKENS)
	{
		while (*(p.s) == ' ' || (*(p.s) >= 9 && *(p.s) <= 13))
			(p.s)++;
		p.check = handle_args(&p);
		if (!p.check)
			return ((char **)ft_free_matrix((void **)p.tokens));
	}
	p.tokens[p.count] = NULL;
	p.tokens = ft_realloc(p.tokens, (p.count + 1) * sizeof(char *));
	return (p.tokens);
}
