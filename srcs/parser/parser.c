/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:03:07 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/09 14:12:14 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_args(t_parser *p)
{
	if (*(p->s))
	{
		p->tokens[p->count] = malloc(sizeof(t_token));
		if (!p->tokens[p->count] || !define_length(p))
			return (p->tokens[p->count]->str = NULL, 0);
		if (p->length > 0)
		{
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
			p->tokens[p->count]->str[p->l] = '\0';
			(p->count)++;
		}
	}
	return (1);
}

int	check_tokens(t_parser *p)
{
	if (p->tokens[0]->type == PIPE
		|| p->tokens[p->count - 1]->type == PIPE)
		ft_putstr_fd
			("minishell: syntax error near unexpected token `|'\n", 2);
	else if (p->tokens[p->count - 1]->type == FD)
		return (1);
	else if (p->tokens[p->count - 1]->type == END_HEREDOC)
		return (1);
	else if (p->tokens[p->count - 1]->type != COMMAND)
		ft_putstr_fd
			("minishell: syntax error near unexpected token `newline'\n", 2);
	else
		return (1);
	return (0);
}

t_token	**main_parser(t_data *d)
{
	t_parser	p;

	p.s = d->input;
	p.env = d->env;
	p.exit_code = d->exit_status;
	p.input_size = ft_strlen(d->input);
	p.tokens = ft_calloc(p.input_size + 1, sizeof(t_token *));
	if (!p.tokens)
		return (NULL);
	p.count = 0;
	while (*(p.s) && p.count < MAX_TOKENS)
	{
		while (*(p.s) == ' ' || (*(p.s) >= 9 && *(p.s) <= 13))
			(p.s)++;
		if (!handle_args(&p))
			return (free_tokens(p.tokens));
	}
	p.tokens[p.count] = NULL;
	if (!check_tokens(&p))
		return (free_tokens(p.tokens));
	p.tokens = realloc(p.tokens, (p.count + 1) * sizeof(t_token *));
	return (p.tokens);
}
