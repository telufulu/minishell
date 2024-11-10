/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:47:05 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/10 15:46:04 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	//ft_shell_error
#include "lexer.h"		// t_cmd
#include "libft.h"		// ft_strcmp
#include "builtings.h"	// t_builts, ft_built_error

t_builts	*init_builtings(t_builts *builtings, char **env)
{
	builtings[0] = (t_builts){"echo", &echo_built, env};
	builtings[1] = (t_builts){"cd", &cd_built, env};
	builtings[2] = (t_builts){"export", &export_built, env};
	builtings[3] = (t_builts){"unset", &unset_built, env};
	builtings[4] = (t_builts){"env", &env_built, env};
	builtings[5] = (t_builts){"exit", &exit_built, env};
	return (builtings);
}

static void	exit_execve(t_cmd *c)
{
	if (c->next)
		ft_shell_error(c->cmd, "ERROR", errno);
	if (access(c->ex_argv[0], R_OK) && ft_strchr(c->ex_argv[0], '/'))
		ft_built_error(c->cmd, "no such file or directory", errno);
	else
		ft_built_error(c->cmd, "command not found", errno);
}

int	my_execve(t_cmd *c, t_builts *builts, char **env)
{
	int	i;

	i = -1;
	if (!c->cmd)
		return (EXIT_SUCCESS);
	while (++i < N_BUILTINGS)
		if (!ft_strncmp(builts[i].cmd, c->cmd, 6))
			return (builts[i].built(c, env));
	if (!c->path)
	{
		exit_execve(c);
		return (127);
	}
	if (execve(c->path, c->ex_argv, env) == -1)
	{
		if (errno == EACCES)
			return (perror("Permission denied"), 126);
		else if (errno == ENOENT)
			return (perror("Command not found"), 127);
		else
			return (perror("Execution failed"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
