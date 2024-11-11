/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:10:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/11 20:41:24 by telufulu         ###   ########.fr       */
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
	int		j;

	i = 0;
	j = 0;
	res = ft_calloc(sizeof(char *), ft_matrix_len(envp) + 1);
	if (!res)
		return (NULL);
	while (envp && envp[j])
	{
		if (ft_strnstr(envp[j], "OLDPWD", 6))
			++j;
		else
		{
			//if (ft_strnstr(envp[j], "SHLVL", 5))
			//	res[i] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(res[i] + 6) + 1));
			//else
				res[i] = ft_strdup(envp[j]);
			if (!res[i])
				return (ft_free_matrix(res));
			++i;
			++j;
		}
	}
	res[i] = NULL;
	return (res);
}
