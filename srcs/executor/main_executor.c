/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:37 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/13 17:05:14 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, ft_shell_error
#include "lexer.h"		// t_cmd
#include <stdio.h>		// printf

void	main_executor(t_data *d, t_cmd *c)
{
	while (d && c)
	{
		c = c->next;
	}
}
