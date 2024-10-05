/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:35:36 by aude-la-          #+#    #+#             */
/*   Updated: 2024/10/04 18:49:20 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_meta_character(t_parser *p)
{
	if (*(p->s) == '<' && (*(p->s + 1) == *(p->s)))
		return (p->tokens[p->count]->type = HEREDOC, 2);
	else if (*(p->s) == '>' && (*(p->s + 1) == *(p->s)))
		return (p->tokens[p->count]->type = APPEND, 2);
	else if (*(p->s) == '<')
		return (p->tokens[p->count]->type = REDIRECT_IN, 1);
	else if (*(p->s) == '>')
		return (p->tokens[p->count]->type = REDIRECT_OUT, 1);
	else if (*(p->s) == '|')
		return (p->tokens[p->count]->type = PIPE, 1);
	else
		return (0);
}

int	is_heredoc(t_parser *p)
{
	if (p->count && !ft_strncmp(p->tokens[p->count - 1]->str, "<<", 2))
		return (1);
	return (0);
}

char	next_quote(const char *s)
{
	if (ft_strchr(s, '\'') && ft_strchr(s, '"'))
	{
		if (ft_strchr(s, '\'') < ft_strchr(s, '"'))
			return ('\'');
		else
			return ('"');
	}
	else if (ft_strchr(s, '\''))
		return ('\'');
	else if (ft_strchr(s, '"'))
		return ('"');
	else
		return ('\0');
}

int	check_quotes(t_parser *p)
{
	if (*(p->s) == '\'')
	{
		if (ft_strchr(++p->s, '\''))
			p->s = ft_strchr(p->s, '\'') + 1;
		else
		{
			ft_putstr_fd("minishell: single quote not closed.\n", 2);
			return (0);
		}
	}
	else if (*(p->s) == '"')
	{
		if (ft_strchr(++p->s, '"'))
			p->s = ft_strchr(p->s, '"') + 1;
		else
		{
			ft_putstr_fd("minishell: double quote not closed.\n", 2);
			return (0);
		}
	}
	else if (*(p->s) == '|')
		return (2);
	else
		p->s++;
	return (1);
}

int	define_length(t_parser *p)
{
	int	status;

	p->start = p->s;
	if (check_meta_character(p))
		p->s += check_meta_character(p);
	else
	{
		while (*(p->s) && (*(p->s) != ' ' && !check_meta_character(p)))
		{
			status = check_quotes(p);
			if (!status)
				return (0);
			else if (status == 2)
				break ;
		}
		p->tokens[p->count]->type = COMMAND;
	}
	p->end = p->s;
	p->length = p->end - p->start;
	return (1);
}