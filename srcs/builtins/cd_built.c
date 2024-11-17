/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:21:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/17 15:32:51 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// chdir, access
#include "lexer.h"		// t_cmd
#include "minishell.h"	// ft_shell_error, get_env, strerror, errno
#include "libft.h"		// ft_matrixjoin, ft_strnstr, ft_strdup
#include "builtins.h"

static char	*new_pwd(char **envi, char *env, char *new)
{
	int		i;
	char	*res;

	i = 0;
	res = check_dots(new, env, envi);
	if (res)
		return (res);
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
	pwd = new_pwd(env, getcwd(buffer, 1000), c->ex_argv[1]);
	if (!pwd)
		return (free(old_pwd), EXIT_SUCCESS);
	if (!c->ex_argv[1] || access(c->ex_argv[1], R_OK) || chdir(c->ex_argv[1]))
	{
		if (pwd)
			free(pwd);
		if (old_pwd)
			free(old_pwd);
		return (ft_built_error(c->ex_argv[1], "no such file or directory", \
					1));
	}
	reset_var(c, "PWD", pwd, c->data->env);
	if (get_env(env, "OLDPWD"))
		reset_var(c, "OLDPWD", old_pwd, c->data->env);
	free(pwd);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
