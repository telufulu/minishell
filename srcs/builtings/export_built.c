/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:17 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/07 20:29:22 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"		// t_cmd
#include "libft.h"		// ft_strncmp, ft_strlen, t_bool, TRUE, FALSE
#include "minishell.h"	// strerror
#include "builtings.h"	// env_built

t_bool	is_quote(char c)
{
	if (c == 39 || c == 34)
		return (TRUE);
	return (FALSE);
}

char	*new_var(char *input, int len)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(sizeof(char), len + 1);
	if (!res)
		ft_error("malloc failed", strerror(errno));
	while (i <= len && input[i])
	{
		res[i] = input[i];
		++i;
	}
	return (res);
}

char	*get_var(char *arg)
{
	int	j;
	char	*aux;
	char	*res;

	j = 0;
	while (arg[j] && arg[j] != '=' && arg[j + 1] && !is_quote(arg[j + 1]))
		++j;
	// FALTA UNSET SI LA VARIABLE YA EXISTE
	if ((size_t)j + 1 < ft_strlen(arg))
	{
		aux = new_var(arg, j);
		res = ft_strjoin(aux, arg + j + 1);
		free(aux);
		return (res);
	}
	else
		return (new_var(arg, j));
}

int	export_built(t_cmd *c, char **env)
{
	int		i;
	char	*var;

	i = 1;
	var = NULL;
	if (!c->ex_argv[1])
		ft_print_matrix(env, STDOUT_FILENO);
	while (c->ex_argv[i])
	{
		if (c->ex_argv[1] && *c->ex_argv[1] == '=')
		{
			printf("bash: export: '%s': not a valid identifier\n", \
					c->ex_argv[1]);
			return (EXIT_FAILURE);
		}
		if (ft_strchr(c->ex_argv[i], '='))
			var = get_var(c->ex_argv[i]);
		c->data->env = ft_matrixjoin(c->data->env, var);
		if (var)
			free(var);
		++i;
	}
	return (EXIT_SUCCESS);
}
