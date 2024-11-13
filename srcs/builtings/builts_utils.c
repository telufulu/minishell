/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <Lufu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:07:28 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/14 00:15:11 by telufulu         ###   ########.fr       */
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

char	*reset_var(t_cmd *c, char *var, char *new_value, char **env)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strjoin(var, "=");
	if (!temp)
		ft_error("malloc failed", strerror(errno));
	new_value = ft_strjoin(temp, new_value);
	if (!get_env(env, var))
	{
		c->data->env = ft_matrixjoin(env, new_value);
		ft_free_matrix(env);
		env = c->data->env;
	}
	else
	{
		while (ft_strncmp(env[i], var, ft_strlen(var)))
			++i;
		free(env[i]);
		env[i] = ft_strdup(new_value);
	}
	free(temp);
	free(new_value);
	return (NULL);
}
