/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:47:05 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/07 12:53:49 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	//ft_shell_error
#include "lexer.h"		// t_cmd
#include "libft.h"		// ft_strcmp
#include "builtings.h"	// t_builts

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

static void	exit_execve(t_cmd *c)
{
	char	*msg_error;

	msg_error = NULL;
	if (access(c->ex_argv[0], R_OK) && ft_strchr(c->ex_argv[0], '/'))
	{
		msg_error = "No such file or directory";
		c->data->exit_status = errno;
	}
	else
	{
		msg_error = "command not found";
		c->data->exit_status = errno;
	}
	if (c->next)
		ft_shell_error(c->cmd, msg_error, errno);
	else
		printf("bash: %s: %s\n", c->cmd, msg_error);
}

int	my_execve(t_cmd *c, t_builts *builts, char **env)
{
	int	i;

	i = 0;
	if (!c->cmd)
		return (EXIT_SUCCESS);
	while (i < N_BUILTINGS)
	{
		if (!ft_strncmp(builts[i].cmd, c->cmd, 6))
			return (builts[i].built(c, env));
		++i;
	}
	if (!c->path)
	{
		exit_execve(c);
		return (c->data->exit_status);
	}
	return (execve(c->path, c->ex_argv, env));
}
