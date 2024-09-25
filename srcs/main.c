/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/25 19:59:19 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	//libc, t_data
#include "libft.h"		//ft_strncmp, ft_free_matrix
#include "utils.h"		// init_shell
#include "parser.h"		// main_parser
#include "token.h"		// tokenizer
#include "executor.h"	// executor

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	d = init_shell(NULL, envp, argv, argc);
	d->input = readline(PROMPT);
	while (d->input && ft_strncmp(d->input, "exit", 5))
	{
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
	if (!d->input)
		ft_error("readline failed", strerror(errno));
	ft_printf("exit\n");
	free(d);
	return (0);
}
