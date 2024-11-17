/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:21:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/17 15:30:49 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// chdir, access
#include "lexer.h"		// t_cmd
#include "minishell.h"	// ft_shell_error, get_env, strerror, errno
#include "libft.h"		// ft_matrixjoin, ft_strnstr, ft_strdup
#include "builtins.h"

void	check_path(t_cmd *c, char **env)
{
	char	*aux;

	if (c->ex_argv && !c->ex_argv[1] && get_env(env, "HOME"))
	{
		aux = c->ex_argv[1];
		c->ex_argv[1] = ft_strdup(get_env(env, "HOME"));
		free(aux);
	}
}

char	*relative_dots(char *env)
{
	size_t	len;
	char	*res;

	len = ft_strlen(env) - 1;
	if (env[len] == '.')
		len -= 2;
	while (env[len] != '/')
		--len;
	res = ft_calloc(sizeof(char), len + 1);
	if (!res)
		ft_error("malloc failed", strerror(errno));
	ft_strlcpy(res, env, len + 1);
	return (res);
}

int	check_env_error(char *env, t_bool one_dot)
{
	if (!env)
	{
		if (one_dot)
		{
			ft_putstr_fd("cd: error retrieving current directory: ", 2);
			ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
			ft_putstr_fd("No such file or directory\n", 2);
		}
		return (1);
	}
	return (0);
}

char	*check_dots(char *new, char *env, char **envi)
{
	char	*res;

	if (!ft_strncmp(new, ".", 2) || !ft_strncmp(new, "./", 3))
	{
		if (check_env_error(env, TRUE))
		{
			res = get_env(envi, "PWD");
			if (res[ft_strlen(res) - 1] == '.')
				return (ft_strdup(res));
			return (ft_strjoin(get_env(envi, "PWD"), "/."));
		}
		return (ft_strdup(env));
	}
	else if (!ft_strncmp(new, "..", 3) || !ft_strncmp(new, "../", 4))
	{
		if (check_env_error(env, FALSE))
			return (relative_dots(get_env(envi, "PWD")));
		return (relative_dots(env));
	}
	return (NULL);
}
