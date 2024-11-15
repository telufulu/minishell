/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:50:34 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/15 13:42:50 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD, redir_child, redir_father
#include "lexer.h"		// t_cmd
#include "builtings.h"	// expand_variables

volatile sig_atomic_t	g_heredoc_sig = 0;

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_sig = 1;
//	rl_done = 1;
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

char	*expand_variables(t_data *d, char *input)
{
	t_heredoc	hd;

	if (!input)
		return (NULL);
	hd.len = ft_strlen(input) + 1;
	hd.result = initialize_result(&hd);
	if (!hd.result)
		return (NULL);
	while (input[hd.i])
	{
		if (input[hd.i] == '$')
		{
			hd.i = process_variable(d, input, &hd);
			if (hd.i == -1)
				return (free(hd.result), NULL);
		}
		else
		{
			if (!add_char_to_result(&hd, input[hd.i]))
				return (free(hd.result), NULL);
			hd.i++;
		}
	}
	return (free(input), hd.result);
}

int	handle_heredoc(t_cmd *cmd)
{
	int		heredoc_pipe[2];
	int		quote;
	char	*line;

	if (pipe(heredoc_pipe) == -1)
		return (perror("pipe"), -1);
	setup_heredoc_signals();
	quote = check_delim(cmd);
	while (!g_heredoc_sig)
	{
		line = readline("> ");
		if (!check_line(line, cmd->heredoc))
			break ;
		if (!quote)
			line = expand_variables(cmd->data, line);
		write(heredoc_pipe[1], line, strlen(line));
		write(heredoc_pipe[1], "\n", 1);
		free(line);
	}
	restore_signals();
	return (close(heredoc_pipe[1]), heredoc_pipe[0]);
}
