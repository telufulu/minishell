/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:21:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/02 13:30:47 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// chdir, access
#include "lexer.h"		// t_cmd
#include "minishell.h"	// ft_shell_error, get_env, strerror, errno
#include "libft.h"		// ft_matrixjoin, ft_strnstr, ft_strdup

static void	check_path(t_cmd *c, char **env)
{
	char	**aux;

	// c->ex_argv[1] debería ser la ruta, si no existe, la ruta es HOME
	if (c->ex_argv && !c->ex_argv[1])
	{
		aux = c->ex_argv;
		c->ex_argv = ft_matrixjoin(c->ex_argv, get_env(env, "HOME"));
		ft_free_matrix(aux);
	}
	// access a la ruta. Si no existe, "no such file or directory"
	if (access(c->ex_argv[1], R_OK))
		ft_shell_error(c->ex_argv[1], "no such file or directory", errno);
}

int	cd_built(t_cmd *c, char **env)
{
	check_path(c, env);
	ft_printf("path: %s\n", c->ex_argv[1]);
	//
	// moverme a la dirección con chdir
	//
	// actualizar el PWD del entorno y guardar el OLDPWD. Si el PWD nuevo es el
	// mismo que antes (cd .) no se crea/modifica el OLDPWD
	return (EXIT_SUCCESS);
}
