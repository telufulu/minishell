/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:10:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/08 11:55:55 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" //t_data
#include "libft.h" // ft_calloc, ft_strdup, ft_strnstr, ft_strlen, 
					// ft_free_matrix

char	*get_env(char **env, char *var)
{
	size_t	var_len;

	var_len = ft_strlen(var);
	while (*env)
	{
		if (ft_strncmp(*env, var, var_len) == 0 && (*env)[var_len] == '=')
			return (*env + var_len + 1);
		env++;
	}
	return (NULL);
}

char	**init_env(char **envp)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_calloc(sizeof(char *), ft_matrix_len(envp) + 1);
	if (!res)
		return (NULL);
	while (envp && envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
			return (ft_free_matrix(res));
		if (ft_strnstr(res[i], "SHLVL", 5))
			res[i][6]++;
		i++;
	}
	res[i] = NULL;
	return (res);
}
