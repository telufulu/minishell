/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_builtings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:51:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/19 20:00:56 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"	// t_cmd
#include "libft.h"	//ft_putstr_fd

int	exit_built(t_cmd *c, char **env)
{
	if (c && env)
		ft_putstr_fd("exit\n", STDIN_FILENO);
	return (EXIT_SUCCESS);
}

int	env_built(t_cmd *c, char **env)
{
	if (env && c)
		ft_print_matrix(env, STDIN_FILENO);
	return (EXIT_SUCCESS);
}
