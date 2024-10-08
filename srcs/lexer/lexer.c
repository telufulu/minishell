/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:22:30 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/08 18:58:06 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, ft_shell_error
#include "parser.h"		// t_token
#include "lexer.h"		// t_token, num_cmd
#include "libft.h"		// ft_printf

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
		if (!index && tokens[i]->type == COMMAND)
			return (tokens[i]->str);
		++i;
	}
	return (NULL);
}

char	**split_path(char **env)
{
	char	*path_env;
	char	**sp_path;
	char	*aux;
	int		i;

	i = 0;
	path_env = get_env(env, "PATH");
	sp_path = ft_split(path_env, ':');
	while (sp_path && sp_path[i])
	{
		aux = sp_path[i];
		sp_path[i] = ft_strjoin(sp_path[i], "/");
		free(aux);
		++i;
	}
	return (sp_path);
}

char	*get_path(char **sp_path, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (sp_path[i] && access(path, X_OK) == -1)
	{
		path = ft_strjoin(sp_path[i], cmd);
		if (!access(path, X_OK))
			return (path);
		free(path);
		++i;
	}
	return (NULL);
}

// si "ls | wc | " se abre >
t_cmd	*main_lexer(t_data *d)
{
	size_t	n_cmd;
	size_t	i;
	char	**sp_path;
	t_cmd	*last;

	i = 0;
	n_cmd = num_cmd(d->tokens);
	sp_path = split_path(d->env);
	while (i < n_cmd)
	{
		add_cmd(d);
		last = last_cmd(d->cmd);
		last->cmd = next_cmd(d->tokens, i);
		last->path = get_path(sp_path, last->cmd);
		last-infd 
		ft_printf("cmd: %s\n", last->cmd);
		ft_printf("path: %s\n", last->path);
		last->index = i;
		i++;
	}
	ft_free_matrix((void **)sp_path);
	return (NULL);
}
