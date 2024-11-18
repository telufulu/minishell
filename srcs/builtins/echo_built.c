/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:25:13 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/17 15:41:03 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"	// t_cmd
#include "libft.h"	//ft_putstr_fd, ft_putchar_fd, ft_strncmp

static void	print_var(char **argv, int *i)
{
	char	*to_print;

	while (argv[*i])
	{
		to_print = ft_strtrim(argv[*i], " ");
		if (!to_print)
			ft_error("malloc failed", strerror(errno));
		if (*to_print)
			ft_putstr_fd(to_print, STDOUT_FILENO);
		++(*i);
		if (argv[*i])
			ft_putchar_fd(' ', STDOUT_FILENO);
		free(to_print);
	}
}

int	echo_built(t_cmd *c, char **env)
{
	int		i;
	t_bool	flag;

	i = 1;
	flag = 0;
	if (env && c->ex_argv && c->ex_argv[i])
	{
		flag = !ft_strncmp(c->ex_argv[i], "-n", 2);
		if (flag)
			++i;
		print_var(c->ex_argv, &i);
	}
	if (!flag || !c->ex_argv[1])
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
