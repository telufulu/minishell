/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:21:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/02 01:28:59 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"	// t_cmd
#include <unistd.h>	// chdir

int	cd_built(t_cmd *c, char **env)
{
	// c->ex_argv[1] debería ser la ruta, si no existe, la ruta es HOME
	//
	// access a la ruta. Si no existe, "no such file or directory"
	//
	// moverme a la dirección con chdir
	//
	// actualizar el PWD del entorno y guardar el OLDPWD (¿?)
}
