/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:47:01 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/09 17:11:27 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_varname(t_parser *p, const char *s)
{
	size_t		k;

	k = 0;
	if (s[p->i] == '$' && (p->i + 1 < p->length))
	{
		if (ft_isalnum(s[p->i + 1]) || s[p->i + 1] == '_')
		{
			(p->i)++;
			while (p->i < p->length && (ft_isalnum(s[p->i]) || s[p->i] == '_'))
				p->varname[k++] = s[(p->i)++];
			p->varname[k] = '\0';
			p->env_value = get_env(p->env, p->varname);
			return (1);
		}
		else if (s[p->i + 1] == '?')
		{
			p->env_value = ft_itoa(p->exit_code);
			p->varname[k] = '\0';
			p->i += 2;
			return (1);
		}
		else if (s[p->i + 1] == '\'' || s[p->i + 1] == '"')
			p->i++;
	}
	return (0);
}

char	*substitute_variable(t_parser *p, char *result)
{
	size_t	env_length;
	size_t	k;

	if (p->env_value)
	{
		env_length = ft_strlen(p->env_value);
		result = secured_realloc(result, p->length, p->length + env_length);
		if (!result)
		{
			if (!p->varname[0])
				return (free(p->env_value), NULL);
			return (NULL);
		}
		p->length += env_length;
		k = 0;
		while (p->env_value[k])
			result[(p->j)++] = p->env_value[k++];
		result[p->j] = '\0';
		if (!p->varname[0])
			free(p->env_value);
	}
	return (result);
}

char	*handle_variable(t_parser *p, char limiter)
{
	char		*result;
	const char	*s;

	s = p->start;
	result = malloc(++p->length);
	if (!result)
		return (NULL);
	p->i = 0;
	p->j = 0;
	while (s[p->i] && (&s[p->i] < p->end))
	{
		if (!is_heredoc(p) && get_varname(p, s))
		{
			result = substitute_variable(p, result);
			if (!result)
				return (NULL);
		}
		else if (s[p->i] == limiter && !is_heredoc(p))
			break ;
		else
			result[(p->j)++] = s[(p->i)++];
	}
	result[p->j] = '\0';
	return (result);
}
