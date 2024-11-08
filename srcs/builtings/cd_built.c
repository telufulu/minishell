/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:21:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/08 17:44:07 by telufulu         ###   ########.fr       */
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

int	cd_built(t_cmd *c, char **env)
{
	int	i;

	i = 0;
	check_path(c, env);
	if (!c->ex_argv[1] || access(c->ex_argv[1], R_OK) || chdir(c->ex_argv[1]))
		return (ft_built_error(c->ex_argv[1], "no such file or directory", \
					errno));
	while (!ft_strncmp(env[i], "PWD", 3))
		++i;
	return (EXIT_SUCCESS);
}
