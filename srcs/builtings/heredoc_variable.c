/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:34:40 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/14 17:34:42 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"

int	add_char_to_result(t_heredoc *hd, char c)
{
	size_t	current_len;
	char	*temp;

	current_len = ft_strlen(hd->result);
	if (current_len + 2 > hd->len)
	{
		temp = secured_realloc(hd->result, hd->len, hd->len + 1);
		if (!temp)
			return (0);
		hd->result = temp;
		hd->len++;
	}
	hd->result[hd->j++] = c;
	hd->result[hd->j] = '\0';
	return (1);
}

char	*initialize_result(t_heredoc *hd)
{
	char	*result;

	hd->i = 0;
	hd->j = 0;
	result = malloc(hd->len);
	if (!result)
		return (NULL);
	result[0] = '\0';
	return (result);
}

size_t	extract_varname(char *input, t_heredoc *hd)
{
	size_t	k;

	k = 0;
	while (input[hd->i] && (ft_isalnum(input[hd->i]) || input[hd->i] == '_'))
	{
		hd->varname[k] = input[hd->i];
		hd->i++;
		k++;
	}
	hd->varname[k] = '\0';
	return (hd->i);
}

size_t	process_variable(t_data *d, char *input, t_heredoc *hd)
{
	char	*env_value;

	hd->i++;
	if (input[hd->i] == '?')
	{
		env_value = ft_itoa(d->exit_status);
		hd->i++;
	}
	else
	{
		hd->i = extract_varname(input, hd);
		env_value = get_env(d->env, hd->varname);
	}
	if (env_value && !append_env_value(hd, env_value))
	{
		if (input[hd->i - 1] == '?')
			free(env_value);
		return (-1);
	}
	if (input[hd->i - 1] == '?')
		free(env_value);
	return (hd->i);
}

int	append_env_value(t_heredoc *hd, char *env_value)
{
	size_t	env_len;
	char	*temp;

	env_len = ft_strlen(env_value);
	temp = secured_realloc(hd->result, hd->len, hd->len + env_len);
	if (!temp)
		return (0);
	hd->result = temp;
	ft_strlcat(hd->result, env_value, hd->len + env_len + 1);
	hd->j += env_len;
	hd->len += env_len;
	return (1);
}
