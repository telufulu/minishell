/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/12 21:31:33 by augustindelab    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// libc, t_data, init_shell
#include "libft.h"		// ft_strncmp, ft_free_matrix
#include "parser.h"		// main_parser
#include "lexer.h"		// free_cmds
#include "executor.h"	// executor_main

void	clean_loop(t_data *d)
{
	if (d->tokens)
		ft_free_matrix(d->cmd->ex_argv);
	free_cmds(d->cmd);
	d->cmd = NULL;
	free_tokens(d->tokens);
}

void	handle_input(t_data *d)
{
	add_history(d->input);
	d->tokens = main_parser(d);
	if (!d->tokens)
		return ;
	main_lexer(d, d->tokens);
	main_executor(d, d->cmd);
	clean_loop(d);
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
			handle_input(d);
		free(d->input);
		d->input = readline(PROMPT);
	}
	if (errno != 0)
		ft_error("readline failed", strerror(errno));
	else if (!d->input)
		write(STDOUT_FILENO, "exit\n", 5);
	d->env = ft_free_matrix(d->env);
	free(d);
	return (0);
}
