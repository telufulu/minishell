/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/02 01:00:07 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// libc, t_data, init_shell
#include "libft.h"		// ft_strncmp, ft_free_matrix
#include "parser.h"		// main_parser
#include "lexer.h"		// free_cmds
#include "executor.h"	// executor_main

void	handle_input(t_data *d)
{
	add_history(d->input);
	d->tokens = main_parser(d);
	if (!d->tokens)
		return ;
	main_lexer(d, d->tokens);
	main_executor(d, d->cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	d = init_shell(NULL, envp, argv, argc);
	signal_handlers();
	d->input = readline(PROMPT);
	if (!d->input)
		ft_error("readline failed", strerror(errno));
	while (d->input)
	{
		if (*d->input)
			handle_input(d);
		free(d->input);
		d->cmd = NULL;
		d->input = readline(PROMPT);
	}
	d->env = ft_free_matrix(d->env);
	free(d);
	return (0);
}
