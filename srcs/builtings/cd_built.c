/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:21:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/07 20:42:17 by telufulu         ###   ########.fr       */
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

/*static void	cd_export(t_cmd *c, char *key)
{
	char	*aux;

	if (key)
	{
		aux = key;
		key = ft_strjoin("PWD=", key);
		free(aux);
		c->data->env = ft_matrixjoin(c->data->env, key);
		free(key);
	}
}*/

static void	cd_reset(char **var, int i, char *content)
{
	char	*aux;
	int		j;

	j = 0;
	aux = var[i];
	while (var[i][j] && var[i][j] != '=' && \
			var[i][j + 1] && !is_quote(var[i][j + 1]))
		++j;
	var[i] = new_var(var[i], j);
	if (!var[i])
		ft_error("malloc failed", strerror(errno));
	free(aux);
	aux = var[i];
	var[i] = ft_strjoin(var[i], content);
	if (!var[i])
		ft_error("malloc failed", strerror(errno));
	free(aux);
}

int	cd_built(t_cmd *c, char **env)
{
	int	i;

	i = 0;
	check_path(c, env);
	if (!c->ex_argv[1] || access(c->ex_argv[1], R_OK) || chdir(c->ex_argv[1]))
		ft_shell_error(c->ex_argv[1], "no such file or directory", errno);
	while (!ft_strncmp(env[i], "PWD", 3))
		++i;
	cd_reset(env, i, c->ex_argv[i]);
	//aux = ft_strjoin(get_env(env, "PWD"), "/");
	//cd_export(c, ft_strjoin(aux, c->ex_argv[1]));

	/*aux = get_env(env, "PWD");
	if ((!ft_strncmp(c->ex_argv[1], ".", 2) || \
			!ft_strncmp(c->ex_argv[1], aux, ft_strlen(aux))))
	{
	
	}*/
	
	// actualizar el PWD del entorno y guardar el OLDPWD. Si el PWD nuevo es el
	// mismo que antes (cd .) no se crea/modifica el OLDPWD
	//pwd = get_env(env, "PATH");
	//if (ft_strncmp(pwd, aux, 100))
	//	oldpwd = pwd;
	return (EXIT_SUCCESS);
}
