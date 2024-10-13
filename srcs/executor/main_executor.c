/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/13 16:21:24 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, ft_shell_error
#include "lexer.h"		// t_cmd
#include <stdio.h>

void	redirect(t_data *d, t_cmd *c)
{
	if (c && c->index)
		if (dup2(c->infd, STDIN_FILENO) < 0)
			ft_shell_error();
}

void	main_executor(t_data *d, t_cmd *c)
{
	while (d && c)
	{
		redirect(c);
		c = c->next;
	}
}
