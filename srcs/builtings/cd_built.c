/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:21:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/12 20:42:16 by telufulu         ###   ########.fr       */
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

	if (c->ex_argv && !c->ex_argv[1] && get_env(env, "HOME"))
	{
		aux = c->ex_argv;
		c->ex_argv = ft_matrixjoin(c->ex_argv, get_env(env, "HOME"));
		ft_free_matrix(aux);
	}
}

static char	*relative_dots(char *env)
{
	size_t	len;
	char	*res;

	len = ft_strlen(env) - 1;
	while (env[len] != '/')
		--len;
	res = ft_calloc(sizeof(char), len + 1);
	if (!res)
		ft_error("malloc failed", strerror(errno));
	ft_strlcpy(res, env, len + 1);
	return (res);
}

static char	*new_pwd(char *env, char *new)
{
	int		i;

	i = 0;
	if (!ft_strncmp(new, ".", 2) || !ft_strncmp(new, "./", 3))
		return (ft_strdup(env));
	else if (!ft_strncmp(new, "..", 3) || !ft_strncmp(new, "../", 4))
		return (relative_dots(env));
	while (env && env[i] && new && new[i] && env[i] == new[i])
		++i;
	if (!new[i])
		return (ft_strdup(new));
	env = ft_strjoin(env, "/");
	new = ft_strjoin(env, new + i);
	free(env);
	return (new);
}

int	cd_built(t_cmd *c, char **env)
{
	char	*pwd;
	char	*old_pwd;
	char	buffer[1000];

	check_path(c, env);
	old_pwd = ft_strdup(get_env(env, "PWD"));
	pwd = new_pwd(getcwd(buffer, 1000), c->ex_argv[1]);
	if (!c->ex_argv[1] || access(c->ex_argv[1], R_OK) || chdir(c->ex_argv[1]))
		return (ft_built_error(c->ex_argv[1], "no such file or directory", \
					errno));
	reset_var(c, "PWD", pwd, c->data->env);
	reset_var(c, "OLDPWD", old_pwd, env);
	free(pwd);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
