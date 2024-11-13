/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:50:34 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/12 22:20:18 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD, redir_child, redir_father
#include "lexer.h"		// t_cmd

volatile sig_atomic_t	g_heredoc_sig = 0;

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_sig = 1;
	rl_done = 1;
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	restore_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	g_heredoc_sig = 0;
}

int	handle_heredoc(t_cmd *cmd)
{
	int		heredoc_pipe[2];
	char	*line;

	if (pipe(heredoc_pipe) == -1)
		return (perror("pipe"), -1);
	setup_heredoc_signals();
	while (!g_heredoc_sig)
	{
		line = readline("> ");
		if (line == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		if (ft_strncmp(line, cmd->heredoc, 20) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc_pipe[1], line, strlen(line));
		write(heredoc_pipe[1], "\n", 1);
		free(line);
	}
	restore_signals();
	return (close(heredoc_pipe[1]), heredoc_pipe[0]);
}
