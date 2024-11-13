/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:37:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/14 00:02:42 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"		// t_cmd
#include "builtings.h"	// t_builts
#include "minishell.h"	//get_env
#include "builtings.h"	// ft_built_error

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

int	unset_built(t_cmd *c, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (c->ex_argv[j] && *c->ex_argv[j])
	{
		if (ft_strchr(c->ex_argv[j], '=') || ft_strchr(c->ex_argv[j], '/'))
			ft_built_error(c->ex_argv[j], "not a valid identifier", errno);
		i = find_arg(env, c->ex_argv[j]);
		if (i < 0)
			return (EXIT_SUCCESS);
		while (env[i])
		{
			free(env[i]);
			env[i] = ft_strdup(env[i + 1]);
			if (env[i])
				++i;
		}
		free(env[i]);
		env[i] = NULL;
		++j;
	}
	return (EXIT_SUCCESS);
}
