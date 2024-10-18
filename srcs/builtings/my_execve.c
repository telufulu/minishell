/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:47:05 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/18 02:27:26 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	//ft_shell_error
#include "lexer.h"		// t_cmd
#include "libft.h"		// ft_strcmp
#include "builtings.h"	// t_builts

static void	init_builtings(t_builts *builtings, char **env)
{
	builtings[0] = (t_builts){"ls", &ls_built, env};
}

int	my_execve(t_cmd * c, char **env)
{
	int			i;
	t_builts	builts[N_BUILTINGS];

	i = 0;
	init_builtings(builts, env);
	if (!c->path)
		ft_shell_error(c->cmd, "command not found");
	while (i < N_BUILTINGS)
	{
		if (!ft_strncmp(builts[i].cmd, c->cmd, ft_strlen(c->cmd)))
			return (builts[i].built(c, env));
		++i;
	}
	return (execve(c->path, c->ex_argv, env));
}
