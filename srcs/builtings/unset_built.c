/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:37:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/09 14:23:36 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"		// t_cmd
#include "builtings.h"	// t_builts
#include "minishell.h"	//get_env

int	find_arg(char **env, char *var)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strnstr(env[i], var, ft_strlen(env[i])))
			return (i);
		++i;
	}
	return (-1);
}

static int	not_valid(char *env)
{
	char	*aux;

	aux = NULL;
	if (!ft_strncmp(env, "PATH", 4) || !ft_strncmp(env, "HOME", 4) || \
			!ft_strncmp(env, "SHELL", 5) || !ft_strncmp(env, "PWD", 3))
	{
		aux = env;
		while (*aux != '=')
			++aux;
//		ft_built_error(c->cmd, "not a valid identifier", errno);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	unset_built(t_cmd *c, char **env)
{
	int		i;

	i = 0;
	if (c->ex_argv[1] && *c->ex_argv[1])
	{
		i = find_arg(env, c->ex_argv[1]);
		if (i < 0)
			return (EXIT_SUCCESS);
		while (env[i])
		{
			if (not_valid(env[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			free(env[i]);
			env[i] = ft_strdup(env[i + 1]);
			if (env[i])
				++i;
		}
		free(env[i]);
		env[i] = NULL;
	}
	return (EXIT_SUCCESS);
}
