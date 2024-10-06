/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:22:30 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/06 17:53:55 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, ft_shell_error
#include "parser.h"		// t_token
#include "lexer.h"		// t_token, num_cmd
#include "libft.h"		// ft_printf

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*path_env;
	char	**spl_path;
	int		i;

	i = 0;
	path = NULL;
	path_env = get_env(env, "PATH");
	spl_path = ft_split(path_env, ':');
	while (spl_path[i] && access(path, X_OK) == -1)
	{
		path = ft_strjoin(spl_path[i], cmd);
		if (!access(path, X_OK))
			return (free(cmd), path);
		free(path);
		++i;
	}
	ft_shell_error(cmd + 1, ": command not found");
	return (NULL);
}

char	*next_cmd(t_token **tokens, int index)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		while (index && tokens[i]->type)
		{
			if (tokens[i]->type == PIPE)
				--index;
			++i;
		}
		if (tokens[i]->type == COMMAND)
			return (tokens[i]->str);
		++i;
	}
	return (NULL);
}

// si ls | wc |  se abre >
t_cmd	*main_lexer(t_data *d)
{
	size_t	n_cmd;
	size_t	i;
	t_cmd	*last;

	i = 0;
	n_cmd = num_cmd(d->tokens);
	while (i < n_cmd)
	{
		last = add_cmd(d);
		last->cmd = next_cmd(d->tokens, i);
		//last->path = get_path(last->cmd, d->env);
		last->index = i++;
	}
	t_cmd	*aux = d->cmd;
	while (aux)
	{
		ft_printf("%s\n", aux->cmd);
		aux = aux->next;
	}
	return (NULL);
}
