/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:50:34 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/15 16:12:47 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// open_fd, WR, RD, redir_child, redir_father
#include "lexer.h"		// t_cmd
#include "builtings.h"	// expand_variables

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

static void	heredoc_sig_handler(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	handle_heredoc(t_cmd *cmd, int *h_pipe)
{
	int		quote;
	char	*line;

	signal(SIGINT, heredoc_sig_handler);
	close(h_pipe[0]);
	quote = check_delim(cmd);
	while (1)
	{
		line = readline("> ");
		if (!check_line(line, cmd->heredoc))
			break ;
		if (!quote)
			line = expand_variables(cmd->data, line);
		write(h_pipe[1], line, strlen(line));
		write(h_pipe[1], "\n", 1);
		free(line);
	}
	close(h_pipe[1]);
	exit(EXIT_SUCCESS);
}

int	create_heredoc(t_cmd *cmd)
{
	pid_t	pid;
	int		h_pipe[2];
	int		status;

	if (pipe(h_pipe) == -1)
		return (perror("h_pipe"), -1);
	ignore_signals_in_parent();
	pid = fork();
	if (pid < 0)
		return (close(h_pipe[0]), close(h_pipe[1]), perror("fork"), -1);
	if (pid == 0)
		handle_heredoc(cmd, h_pipe);
	else
	{
		close(h_pipe[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			cmd->data->exit_status = 130;
			restore_parent_signal_handlers();
			return (close(h_pipe[0]), -1);
		}
	}
	return (h_pipe[0]);
}
