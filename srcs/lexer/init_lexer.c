/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:28:44 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/18 18:50:24 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, ft_shell_error
#include "lexer.h"		// t_token, num_cmd
#include "libft.h"		// ft_printf, ft_strdup, ft_strcmp
#include "parser.h"		// PIPE
#include <fcntl.h>		// open

char	*get_cmd(t_token **tokens)
{
	while (tokens && *tokens)
	{
		if ((*tokens)->type == COMMAND)
			return (ft_strdup((*tokens)->str));
		++tokens;
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
	if (!path_env)
		return (NULL);
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
	if (!access(cmd, X_OK) || !ft_strncmp(cmd, "exit", 4))
		return (ft_strdup(cmd));
	if (!cmd || !sp_path)
		return (NULL);
	while (sp_path[i])
	{
		path = ft_strjoin(sp_path[i], cmd);
		if (!access(path, X_OK))
			return (path);
		free(path);
		++i;
	}
	return (NULL);
}

char	*get_fd(t_token **tokens, t_type tp)
{
	char	*res;

	res = NULL;
	while (tokens && *tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == tp)
		{
			++tokens;
			if (tokens && (*tokens)->type == FD)
			{
				close(open((*tokens)->str, O_CREAT, 0644));
				res = (*tokens)->str;
			}
		}
		if (tokens)
			++tokens;
	}
	return (res);
}

char	*get_heredoc(t_token **tokens)
{
	char	*end_heredoc;

	end_heredoc = NULL;
	if (!is_token(tokens, HEREDOC))
		return (NULL);
	while (*tokens && ((*tokens)->type != HEREDOC && (*tokens)->type != PIPE))
		tokens++;
	if (*tokens && (*tokens)->type == HEREDOC)
	{
		tokens++;
		if (*tokens && (*tokens)->type == END_HEREDOC)
		{
			end_heredoc = ft_strdup((*tokens)->str);
			if (!end_heredoc)
				ft_error("malloc failed", strerror(errno));
			tokens++;
		}
		else
			ft_error("Syntax error: No Heredoc delimiter", strerror(errno));
	}
	return (end_heredoc);
}
