/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:17 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/18 01:10:07 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"		// t_cmd
#include "libft.h"		// ft_strncmp, ft_strlen, t_bool, TRUE, FALSE
#include "minishell.h"	// strerror
#include "builtins.h"	// env_built

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

static void	print_quotes(char *env)
{
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putstr_fd(env, STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
}

static void	print_export(char **env)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	len = ft_matrix_len(env) + 1;
	env = order_env(env, len);
	while (i < len && env && env[i])
	{
		if (env[i] && *env[i])
		{
			j = 0;
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			while (env[i][j] && env[i][j] != '=')
				ft_putchar_fd(env[i][j++], STDOUT_FILENO);
			ft_putchar_fd(env[i][j++], STDOUT_FILENO);
			if (env[i][j])
				print_quotes(env[i] + j);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		++i;
	}
	ft_free_matrix(env);
}

static char	*clean_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		ft_error("malloc failed", strerror(errno));
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+')
			arg[i] = 0;
		++i;
	}
	if (arg[i] == '=')
		arg[i] = 0;
	return (arg);
}

int	export_built(t_cmd *c, char **env)
{
	int		i;
	char	*aux;
	char	*clean;

	i = 1;
	if (c->ex_argv && !c->ex_argv[1])
		print_export(ft_matrixdup(env, ft_matrix_len(env) + 1));
	while (c->ex_argv && c->ex_argv[i])
	{
		if (c->ex_argv[i] && error_handler(c->ex_argv[i]))
			return (EXIT_FAILURE);
		clean = clean_arg(ft_strdup(c->ex_argv[i]));
		aux = get_env(env, clean);
		if (!aux)
		{
			c->data->env = ft_matrixjoin(env, c->ex_argv[i]);
			ft_free_matrix(env);
			env = c->data->env;
			free(clean);
		}
		else
			reset_arg(env, clean, c->ex_argv[i]);
		++i;
	}
	return (EXIT_FAILURE);
}
