/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:47:24 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/26 14:13:32 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINGS_H
# define BUILTINGS_H

/******************************************************************************
 * Includes
 *****************************************************************************/
# include "lexer.h"	// t_cmd
# include <unistd.h>	// execve

/******************************************************************************
 * Includes
 *****************************************************************************/
# define N_BUILTINGS 3

/******************************************************************************
 * Structs
 *****************************************************************************/
typedef struct s_builts
{
	char	*cmd;
	int		(*built)(t_cmd *, char **env);
	char	**env;
}				t_builts;

/******************************************************************************
 * Files
 *****************************************************************************/
// builtings.c
int	my_execve(t_cmd *c, char **env);

// basic_builtings.c
int	exit_built(t_cmd *c, char **env);
int	env_built(t_cmd *c, char **env);

// echo_built.c
int	echo_built(t_cmd *c, char **env);

#endif
