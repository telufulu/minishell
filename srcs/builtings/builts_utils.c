/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <Lufu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:07:28 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/11 03:16:42 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include "minishell.h"	//get_env

t_bool	is_built(t_builts *builts, char *cmd)
{
	int	i;

	i = 0;
	while (i < N_BUILTINGS)
	{
		if (!ft_strncmp(builts[i].cmd, cmd, 6))
			return (TRUE);
		++i;
	}
	return (FALSE);
}

int	ft_built_error(char *var, char *msg_error, int exit_status)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	if (var && *var)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg_error && *msg_error)
		ft_putstr_fd(msg_error, 2);
	ft_putstr_fd("\n", 2);
	return (exit_status);
}

static void	check_var(char *var)
{
	if (!ft_strncmp(var, ".", 2) || \
			!ft_strncmp(var, "..", 3))
	{
		if (!ft_strncmp(var, ".", 2))
			return (get_env(env, "PWD"));
		else	
			return (get_env(env, "OLDPWD"));
	}
	return (var)
}

char	*reset_var(char *var, char *new_value, char **env)
{
	int		i;
	char	*var_env;

	i = 0;
	var = check_var(var);
	while (env[i] && ft_strncmp(env[i], var, ft_strlen(var)))
		++i;
	if (!env[i])
		return (NULL);
	free(env[i]);
	env[i] = ft_strjoin(var, "=");
	if (new_value)
	{
		var_env = env[i];
		env[i] = ft_strjoin(env[i], new_value);
		if (!env[i])
			return (NULL);
		free(var_env);
	}
	return (env[i]);
}
