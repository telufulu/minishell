/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <Lufu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:07:28 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/08 17:14:20 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"

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
