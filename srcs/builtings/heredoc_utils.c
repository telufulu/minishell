/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:34:54 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/14 17:39:11 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD, redir_child, redir_father
#include "lexer.h"		// t_cmd
#include "builtings.h"	// expand_variables

void	handle_quote(char *result, char **start, size_t *i, char c)
{
	(*start)++;
	while (**start != c)
	{
		result[(*i)++] = **start;
		(*start)++;
	}
	(*start)++;
}

int	check_delim(t_cmd *cmd)
{
	char	*start;
	char	*result;
	size_t	i;

	if (!ft_strchr(cmd->heredoc, '\'') && !ft_strchr(cmd->heredoc, '"'))
		return (0);
	i = 0;
	start = cmd->heredoc;
	result = malloc(ft_strlen(cmd->heredoc) + 1);
	if (!result)
		return (-1);
	while (*start)
	{
		if (*start == '\'')
			handle_quote(result, &start, &i, '\'');
		else if (*start == '"')
			handle_quote(result, &start, &i, '"');
		else
			result[i++] = *start++;
	}
	result[i] = '\0';
	free(cmd->heredoc);
	cmd->heredoc = result;
	return (1);
}

int	check_line(char *line, char *end)
{
	if (line == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (ft_strncmp(line, end, 20) == 0)
		return (free(line), 0);
	return (1);
}
