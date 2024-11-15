/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <Lufu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:07:28 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/15 18:35:13 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include "minishell.h"	//get_env

int	error_handler(char *args)
{
	int	j;

	j = 1;
	if (args && !ft_isalpha(*args) && *args != '_')
		return (ft_built_error(args, "not a valid identifier", errno));
	while (args && args[j])
	{
		if (args[j] == '=')
			++j;
		else if (!ft_isalnum(args[j]) && args[j] != '_')
			return (ft_built_error(args, "not a valid identifier", errno));
		else
			++j;
	}
	return (0);
}

void	reset_arg(char **env, char *var, char *arg)
{
	char	*aux;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], var, ft_strlen(arg) - 1))
		++i;
	aux = env[i];
	env[i] = ft_strdup(arg);
	if (aux)
		free(aux);
	if (!env[i])
		ft_error("malloc failed", strerror(errno));
	if (var)
		free(var);
}

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
	ft_printf("env: %s\n", get_env(env, var));
	if (!get_env(env, var))
	{
		c->data->env = ft_matrixjoin(env, new_value);
		ft_free_matrix(env);
	}
	else if (new_value)
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
