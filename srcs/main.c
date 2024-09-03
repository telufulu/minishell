/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/04 00:22:00 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	good_exit(t_data *d)
{
	free(d->input);
	d->input = NULL;
	d->params = (char **)ft_free_matrix((void **)d->params);
	d->env = (char **)ft_free_matrix((void **)d->env);
	free(d->tokens);
	d->tokens = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	d;

	init_shell(&d, envp, argv, argc);
	d.input = readline(PROMPT);
	while (d.input && ft_strncmp(d.input, "exit", 5))
	{
		add_history(d.input);
		d.params = main_parser(d.input, d.exit_status);
		d.tokens = tokenizer(d.params);
		if (d.params)
		{
			ft_print_matrix(d.params, 1);
			d.params = (char **)ft_free_matrix((void **)d.params);
		}
		free(d.input);
		d.input = readline(PROMPT);
	}
	if (!d.input)
		ft_error("readline failed", strerror(errno));
	good_exit(&d);
	return (0);
}
