/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/24 21:17:40 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>		// execve
#include "minishell.h"	// t_data, access
#include "executor.h"	// t_cmd
#include "libft.h"		// ft_calloc, ft_error, strrerror
#include "token.h"		// PIPE, INFD, OUTFD

void	exec_cmds(t_cmd **c)
{
	int	i;

	i = 0;
	while (c && c[i])
	{
		if (execve(c[i]->path, c[i]->argv, c[i]->data->env) == -1)
			ft_error("execve failed", strerror(errno));
		//ft_printf("path: %s\n", c[i]->path);
		//ft_print_matrix(c[i]->argv, 1);
		++i;
	}
}

t_cmd **executor(t_data *d)
{
	t_cmd	**c;

	c = create_cmds(count_cmds(d->tokens), d);
	exec_cmds(c);
	return (c);
}
