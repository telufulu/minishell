/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/12 20:04:16 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" //libc, t_data
#include "libft.h" //ft_strncmp, ft_free_matrix
#include "utils.h" // init_shell
#include "parser.h" // main_parser
#include "token.h" // tokenizer

void	good_exit(t_data *d)
{
	d->env = (char **)ft_free_matrix((void **)d->env);
	d->params = (char **)ft_free_matrix((void **)d->params);
	free(d->tokens);
	free(d->input);
	d->tokens = NULL;
	d->input = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	d;

	init_shell(&d, envp, argv, argc);
	d.input = readline(PROMPT);
	while (d.input && ft_strncmp(d.input, "exit", 5))
	{
		add_history(d.input);
		d.params = main_parser(&d);
		d.tokens = tokenizer(d.params);
		free(d.input);
		d.input = readline(PROMPT);
	}
	if (!d.input)
		ft_error("readline failed", strerror(errno));
	//good_exit(&d);
	return (0);
}
