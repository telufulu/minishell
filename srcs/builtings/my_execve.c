/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:47:05 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/27 19:57:38 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	//ft_shell_error
#include "lexer.h"		// t_cmd
#include "libft.h"		// ft_strcmp
#include "builtings.h"	// t_builts

static void	init_builtings(t_builts *builtings, char **env)
{
	builtings[0] = (t_builts){"echo", &echo_built, env};
	builtings[1] = (t_builts){"env", &env_built, env};
	builtings[2] = (t_builts){"exit", &exit_built, env};
}

int	my_execve(t_cmd *c, char **env)
{
	int			i;
	t_builts	builts[N_BUILTINGS];

	i = 0;
	init_builtings(builts, env);
	while (i < N_BUILTINGS)
	{
		if (!ft_strncmp(builts[i].cmd, c->cmd, 6))
			return (builts[i].built(c, env));
		++i;
	}
	if (!c->path)
	{
		//ft_free_matrix((void **)c->ex_argv);
		ft_shell_error(c->cmd, "command not found", errno);
	}
	return (execve(c->path, c->ex_argv, env));
}
