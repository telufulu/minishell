/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:26:46 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/08 21:01:33 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handle_single_quote(t_parser *p)
{
	p->tokens[p->count]->str = ft_calloc(1, p->length + 1);
	if (!p->tokens[p->count]->str)
		return ;
	while (*(++p->start) != '\'')
		p->tokens[p->count]->str[p->l++] = *(p->start);
	p->start++;
}

void	handle_double_quote(t_parser *p)
{
	char	*var;

	if (*(++p->start) != '"')
	{
		var = handle_variable(p, '"');
		append_variable(p, var);
		p->start += p->i;
	}
	if (*p->start == '"')
		p->start++;
}

void	handle_variable_expansion(t_parser *p)
{
	char	*var;

	var = handle_variable(p, next_quote(p->start));
	if (!var)
		return ;
	append_variable(p, var);
	p->start += p->i;
}

void	append_variable(t_parser *p, char *var)
{
	char	*tmp;

//	tmp = ft_realloc(p->tokens[p->count]->str, ft_strlen(var));
	tmp = ft_calloc(1, ft_strlen(var) + 1);
	if (!tmp)
		return (free(var));
	p->tokens[p->count]->str = tmp;
	p->l += ft_strlcpy(p->tokens[p->count]->str, var, p->j + 1);
	free(var);
}
