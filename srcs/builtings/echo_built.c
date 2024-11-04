/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:25:13 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/04 18:27:51 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"	// t_cmd
#include "libft.h"	//ft_putstr_fd, ft_putchar_fd, ft_strncmp

int	echo_built(t_cmd *c, char **env)
{
	int		i;
	t_bool	flag;

	i = 1;
	flag = 0;
	if (env && c->ex_argv && c->ex_argv[i])
	{
		flag = !ft_strncmp(c->ex_argv[i], "-n", 3);
		if (flag)
			++i;
		while (c->ex_argv[i])
		{
			if (*c->ex_argv[i])
				ft_putstr_fd(c->ex_argv[i], STDOUT_FILENO);
			++i;
			if (c->ex_argv[i])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (!flag || !c->ex_argv[1])
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
