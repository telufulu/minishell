/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:42:54 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/13 17:05:33 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>	// open
#include "parser.h"	// t_token, t_type

void	open_fd(int *fd, t_token **tokens, t_type tp)
{
	while (tokens && *tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == tp)
		{
			++tokens;
			if (*fd > 2)
				close(*fd);
			*fd = open((*tokens)->str, O_CREAT | O_RDWR, 0644);
		}
		++tokens;
	}
}
