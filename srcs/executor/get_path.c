/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:10:26 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/25 20:10:20 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h" // ft_shell_error, get_env
#include "minishell.h" // t_data, access, strerror, free
#include "executor.h" // t_cmd, get_ex_args, next_param
#include "libft.h" // ft_calloc, ft_error, ft_strjoin, ft_split

// ESTÁS HACIENDO UN CAMBIO PARA QUE COMPRUEBE QUE ES UN CMD EL ARGUMENTO
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
