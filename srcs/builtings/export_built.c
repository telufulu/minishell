/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:17 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/15 17:39:01 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"		// t_cmd
#include "libft.h"		// ft_strncmp, ft_strlen, t_bool, TRUE, FALSE
#include "minishell.h"	// strerror
#include "builtings.h"	// env_built

static char	**order_env(char **env, size_t len)
{
	size_t	i;
	char	*ref;
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		i = 0;
		while (i < len - 1 && env && env[i])
		{
			if (env[i + 1] && ft_strcmp(env[i], env[i + 1]) > 0)
			{
				ref = ft_strdup(env[i]);
				free(env[i]);
				env[i] = ft_strdup(env[i + 1]);
				free(env[i + 1]);
				env[i + 1] = ft_strdup(ref);
				free(ref);
				flag = 1;
			}
			++i;
		}
	}
	return (env);
}

static void	print_export(char **env)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_matrix_len(env) + 1;
	env = order_env(env, len);
	while (i < len && env && env[i])
	{
		if (env[i] && *env[i])
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		++i;
	}
	ft_free_matrix(env);
}

static int	error_handler(char *args)
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

static int	var_exists(char **env, char **old_arg, char *arg)
{
	int		i;
	char	*aux;

	i = 0;
	aux = ft_strdup(arg);
	if (!aux)
		ft_error("malloc failed", strerror(errno));
	while (aux[i] && aux[i] != '=')
		++i;
	if (aux[i] == '=')
		aux[i] = 0;
	if (get_env(env, aux))
	{
		free(*old_arg);
		*old_arg = ft_strdup(arg);
		if (!*old_arg)
			ft_error("malloc failed", strerror(errno));
		ft_printf("old_arg: %s\n", *old_arg);
		free(aux);
		return (1);
	}
	free(aux);
	return (0);
}

int	export_built(t_cmd *c, char **env)
{
	int		i;
	char	*aux;

	i = 1;
	if (c->ex_argv && !c->ex_argv[1])
		print_export(ft_matrixdup(env, ft_matrix_len(env) + 1));
	while (c->ex_argv && c->ex_argv[i])
	{
		if (c->ex_argv[i] && error_handler(c->ex_argv[i]))
			return (EXIT_FAILURE);
		aux = get_env(env, c->ex_argv[i]);
		if (!var_exists(env, &aux, c->ex_argv[i]))
		{
			c->data->env = ft_matrixjoin(env, c->ex_argv[i]);
			ft_free_matrix(env);
			env = c->data->env;
		}
		++i;
	}
	return (EXIT_FAILURE);
}
