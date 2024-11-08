/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:09:55 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/08 13:22:26 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtings.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handlers(void)
{
	struct termios		term;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	handle_empty_string(t_data *d)
{
	t_cmd	exit_cmd;

	exit_cmd.data = d;
	exit_cmd.next = NULL;
	exit_cmd.index = 0;
	if (!d->input && errno)
		return (ft_error("readline failed", strerror(errno)));
	else if (!d->input)
		exit_built(&exit_cmd, d->env);
	else
		return ;
}
