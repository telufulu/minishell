/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/10/13 16:37:36 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	//libc, t_data, init_shell
#include "libft.h"		//ft_strncmp, ft_free_matrix
#include "parser.h"		// main_parser
#include "lexer.h"		//init_cmds, free_cmds

/*void	close_fds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->infd > 2)
			close(cmd->infd);
		if (cmd->outfd > 2)
			close(cmd->outfd);
		cmd = cmd->next;
	}
}*/

void	clean_loop(t_data *d)
{
	//close_fds(d->cmd);
	free_cmds(d->cmd);
	d->cmd = NULL;
	free_tokens(d->tokens);
	free(d->input);
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
			d->tokens = main_parser(d);
			main_lexer(d, d->tokens);
			printf("in: %s\tout: %s\n", d->cmd->infd, d->cmd->outfd);
			clean_loop(d);
		}
		d->input = readline(PROMPT);
	}
	if (errno != 0)
		ft_error("readline failed", strerror(errno));
	else if (!d->input)
		write(STDOUT_FILENO, "exit\n", 5);
	d->env = (char **)ft_free_matrix((void **)d->env);
	free(d);
	return (0);
}
