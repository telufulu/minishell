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
				if (*(p->start) == '\'')
					handle_single_quote(p);
				else if (*(p->start) == '"')
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

int	handle_singlequote(t_parser *p)
{
	p->start = ++(p->s);
	p->end = ft_strchr(p->s, '\'');
	if (p->end == p->s)
		return (++(p->s), 1);
	if (!p->end)
		return (ft_putstr_fd("minishell: single quote not closed.\n", 2), 0);
	if (is_heredoc(p))
	{
		p->start = --(p->s);
		p->end++;
	}
	p->length = p->end - p->start;
	p->tokens[p->count] = malloc(p->length + 1);
	if (!p->tokens[p->count])
		return (0);
	ft_strlcpy(p->tokens[p->count], p->start, p->length + 1);
	p->s = p->end;
	if (!is_heredoc(p))
		p->s = p->end + 1;
	(p->count)++;
	return (1);
}

int	handle_doublequote(t_parser *p)
{
	p->start = ++(p->s);
	p->end = ft_strchr(p->s, '"');
	if (p->end == p->s)
		return (++(p->s), 1);
	if (!p->end)
		return (ft_putstr_fd("minishell: double quote not closed.\n", 2), 0);
	if (is_heredoc(p))
	{
		p->start = --(p->s);
		p->end++;
	}
	p->length = p->end - p->start;
	p->tokens[p->count] = handle_variable(p, '"');
	if (!p->tokens[p->count])
		return (0);
	p->s = p->end;
	if (!is_heredoc(p))
		p->s = p->end + 1;
	(p->count)++;
	return (1);
}

char	**main_parser(const char *input, int exit_status)
{
	t_parser	p;

	p.s = input;
	p.exit_code = exit_status;
	p.tokens = ft_calloc((ft_strlen(p.s) + 1), sizeof(char *));
	if (!p.tokens)
		return (NULL);
	p.count = 0;
	while (*(p.s) && p.count < MAX_TOKENS)
	{
		while (*(p.s) == ' ' || (*(p.s) >= 9 && *(p.s) <= 13))
			(p.s)++;
		if (*(p.s) == '\'')
			p.check = handle_singlequote(&p);
		else if (*(p.s) == '"')
			p.check = handle_doublequote(&p);
		else
			p.check = handle_args(&p);
		if (!p.check)
			return (free_array(p.tokens));
	}
	p.tokens[p.count] = NULL;
	p.tokens = ft_realloc(p.tokens, (p.count + 1) * sizeof(char *));
	return (p.tokens);
}
