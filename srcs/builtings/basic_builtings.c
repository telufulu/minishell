/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_builtings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:51:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/08 17:51:29 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"	// t_cmd
#include "libft.h"	//ft_putstr_fd

int	exit_built(t_cmd *c, char **env)
{
	if (!c->next && !c->index && env)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		c->data->exit_status = EXIT_SUCCESS;
		exit(c->data->exit_status);
	}
	return (EXIT_SUCCESS);
}

int	env_built(t_cmd *c, char **env)
{
	if (env && c)
		ft_print_matrix(env, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
