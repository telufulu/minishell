/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/01 21:26:49 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	good_exit(t_data *d)
{
	d->env = (char **)ft_free_matrix((void **)d->env);
	free(d->input);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	d;

	init_shell(&d, envp, argv, argc);
	d.input = readline(PROMPT);
	while (d.input && ft_strncmp(d.input, "exit", 5))
	{
		add_history(d.input);
		d.tokens = main_parser(&d);
		if (d.tokens)
		{
			ft_print_matrix(d.tokens, 1);
			d.tokens = (char **)ft_free_matrix((void **)d.tokens);
		}
		free(d.input);
		d.input = readline(PROMPT);
	}
	if (!d.input)
		ft_error("readline failed", strerror(errno));
	good_exit(&d);
	return (0);
}
