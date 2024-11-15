/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/15 16:04:17 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// libc, t_data, init_shell
#include "libft.h"		// ft_strncmp, ft_free_matrix
#include "parser.h"		// main_parser
#include "lexer.h"		// free_cmds
#include "executor.h"	// executor_main

static void	*free_cmd(t_cmd *cmd)
{
	t_cmd	*aux;

	while (cmd)
	{
		aux = cmd;
		secure_free((void **)&cmd->cmd);
		ft_free_matrix(cmd->ex_argv);
		secure_free((void **)&cmd->path);
		secure_free((void **)&cmd->heredoc);
		cmd = cmd->next;
		secure_free((void **)&aux);
	}
	return (NULL);
}

static void	handle_input(t_data *d)
{
	add_history(d->input);
	d->tokens = main_parser(d);
	if (!d->tokens)
		return ;
	main_lexer(d, d->tokens);
	main_executor(d, d->cmd);
	free_tokens(d->tokens);
	d->cmd = free_cmd(d->cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	d = init_shell(NULL, envp, argv, argc);
	signal_handlers();
	d->input = readline(PROMPT);
	handle_empty_string(d);
	while (d->input)
	{
		if (*d->input)
			handle_input(d);
		free(d->input);
		d->input = readline(PROMPT);
		handle_empty_string(d);
	}
//	rl_clear_history();
	d->env = ft_free_matrix(d->env);
	free(d);
	return (0);
}
