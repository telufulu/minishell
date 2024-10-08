/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:28:44 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/10 19:47:22 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, ft_shell_error
#include "lexer.h"		// t_token, num_cmd
#include "libft.h"		// ft_printf
#include "parser.h"		// PIPE
#include <fcntl.h>		// open

char	*get_cmd(t_token **tokens)
{
	while (tokens && *tokens)
	{
		if ((*tokens)->type == COMMAND)
			return ((*tokens)->str);
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

void	open_fd(int *fd, t_token **tokens, t_type tp)
{
	*fd = -1;
	while (tokens && *tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == tp)
		{
			++tokens;
			if (tokens && *tokens && (*tokens)->type == FD)
			{
				if (*fd > 2)
					close(*fd);
				if (tp == REDIRECT_IN)
				{
					*fd = open((*tokens)->str, O_RDONLY, 0644);
					if (*fd == -1)
						ft_shell_error((*tokens)->str, strerror(errno));
				}
				else if (tp == REDIRECT_OUT)
					*fd = open((*tokens)->str, O_CREAT | O_RDONLY, 0644);
			}
			else if (!tokens || !*tokens)
				return ;
		}
		++tokens;
	}
}
