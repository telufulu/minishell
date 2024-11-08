/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:26:46 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/08 17:59:33 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handle_single_quote(t_parser *p)
{
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

//	tmp = ft_realloc(p->tokens[p->count]->str, p->length + ft_strlen(var));
	tmp = ft_realloc(p->tokens[p->count]->str, ft_strlen(var) + 1);
	if (!tmp)
		return (free(var));
	p->tokens[p->count]->str = tmp;
	p->l += ft_strlcpy(&p->tokens[p->count]->str[p->l], var, p->j + 1);
	free(var);
}
