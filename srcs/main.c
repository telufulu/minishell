/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/10/01 23:53:57 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// libc, t_data
#include "libft.h"		// ft_strncmp, ft_free_matrix
#include "utils.h"		// init_shell
#include "parser.h"		// main_parser
#include "token.h"		// tokenizer
#include "executor.h"	// executor

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	d = init_shell(NULL, envp, argv, argc);
	signal_handlers();
	d->input = readline(PROMPT);
	while (d->input && ft_strncmp(d->input, "exit", 5))
	{
		errno = 0;
		if (*d->input)
		{
			add_history(d->input);
			d->params = main_parser(d);
			d->tokens = tokenizer(d->params);
			executor(d);
		}
		free(d->input);
		d->input = readline(PROMPT);
	}
	if (errno != 0)
		ft_error("readline failed", strerror(errno));
	else if (!d->input)
		write(STDOUT_FILENO, "exit\n", 5);
	return (0);
}
