/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:42:54 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/12 20:58:45 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// RD, WR
#include <fcntl.h>		// open
#include "parser.h"		// t_token, t_type
#include "libft.h"		// get_next_line, ft_putstr_fd

void	write_fd(int old, int new)
{
	char	*str;

	str = get_next_line(old);
	while (str)
	{
		ft_putstr_fd(str, new);
		free(str);
		str = get_next_line(old);
	}
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (status);
}

int	find_heredoc(t_cmd *c)
{
	t_cmd	*tmp;

	tmp = c;
	while (tmp)
	{
		if (tmp->heredoc)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
