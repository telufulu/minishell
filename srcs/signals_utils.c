/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:25:02 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/08 14:29:47 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_handler(int signum, void (*handler)(int))
{
	if (signal(signum, handler) == SIG_ERR)
		check_error(-1, "signal");
	else
		check_error(0, "signal");
}

void	reset_signal_handlers_to_default(void)
{
	set_signal_handler(SIGINT, SIG_DFL);
	set_signal_handler(SIGQUIT, SIG_DFL);
}

void	ignore_signals_in_parent(void)
{
	set_signal_handler(SIGINT, SIG_IGN);
}

void	restore_parent_signal_handlers(void)
{
	set_signal_handler(SIGINT, handle_sigint);
}

void	check_error(int retval, const char *msg)
{
	if (retval == -1)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
}
