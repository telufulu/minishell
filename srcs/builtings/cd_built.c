/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:21:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/11 03:17:51 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// chdir, access
#include "lexer.h"		// t_cmd
#include "minishell.h"	// ft_shell_error, get_env, strerror, errno
#include "libft.h"		// ft_matrixjoin, ft_strnstr, ft_strdup
#include "builtings.h"

static void	check_path(t_cmd *c, char **env)
{
	char	**aux;

	if (c->ex_argv && !c->ex_argv[1])
	{
		aux = c->ex_argv;
		c->ex_argv = ft_matrixjoin(c->ex_argv, get_env(env, "HOME"));
		ft_free_matrix(aux);
	}
}

static char	*new_pwd(char *env, char *new)
{
	int	i;

	i = 0;
	while (new && new[i] && env[i] == new[i])
		++i;
	if (!new[i])
		return (ft_strdup(new));
	else if ((new + i) && env[i])
	{
		if (env[ft_strlen(env) - 1] != '/')
			env = ft_strjoin(env, "/");
		if (!env)
			return (NULL);
		return (ft_strjoin(env, new + i));
	}
	else if (!env[i])
		return (ft_strdup(new + i));
	return (ft_strdup(env));
}

int	cd_built(t_cmd *c, char **env)
{
	char	*pwd;
	char	*old_pwd;
	
	check_path(c, env);
	if (!c->ex_argv[1] || access(c->ex_argv[1], R_OK) || chdir(c->ex_argv[1]))
		return (ft_built_error(c->ex_argv[1], "no such file or directory", \
					errno));
	old_pwd = ft_strdup(get_env(env, "PWD"));
	pwd = new_pwd(old_pwd, c->ex_argv[1]);
	//NOT WORKING reset_var("PWD", pwd, env);
	//NOT WORKING reset_var("OLDPWD", old_pwd, env);
	free(pwd);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
