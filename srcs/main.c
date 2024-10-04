/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/10/04 17:02:29 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	good_exit(t_data *d)
{
	d->env = (char **)ft_free_matrix((void **)d->env);
	free(d->input);
}

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
	t_data	d;

	init_shell(&d, envp, argv, argc);
	signal_handlers();
	d.input = readline(PROMPT);
	while (d.input && ft_strncmp(d.input, "exit", 5))
	{
		errno = 0;
		if (*d.input)
			add_history(d.input);
		d.tokens = main_parser(&d);
		if (d.tokens)
		{
			print_tokens(d.tokens, 1);
			d.tokens = free_tokens(d.tokens);
		}
		free(d.input);
		d.input = readline(PROMPT);
	}
	if (errno != 0)
		ft_error("readline failed", strerror(errno));
	else if (!d.input)
		write(STDOUT_FILENO, "exit\n", 5);
	good_exit(&d);
	return (0);
}
