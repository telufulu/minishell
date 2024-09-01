/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:16:55 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/01 21:20:39 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_term(char **envp)
{
	char	*tty;

	if (isatty(STDIN_FILENO) && envp)
	{
		tty = ttyname(STDIN_FILENO);
		if (get_env(envp, "SHELL"))
			printf("Shell: %s\n", get_env(envp, "SHELL"));
		if (get_env(envp, "USER"))
			printf("User: %s ", get_env(envp, "USER"));
		if (tty)
			printf("is succesfully logged on %s\n", tty);
		else
			perror("ttyname");
	}
	else
		ft_error("stdin is not a terminal", strerror(errno));
}

void	init_shell(t_data *d, char **envp, char **argv, int argc)
{
	if (argc > 1 && argv)
		ft_error("minishell doesn't get any arguments", NULL);
	d->env = init_env(envp);
	if (!d->env)
		ft_error("malloc failed", NULL);
	check_term(d->env);
	d->exit_status = 0;
}
