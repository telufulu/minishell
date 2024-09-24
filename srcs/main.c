/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/24 16:31:45 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" //libc, t_data
#include "libft.h" //ft_strncmp, ft_free_matrix
#include "utils.h" // init_shell
#include "parser.h" // main_parser
#include "token.h" // tokenizer
#include "executor.h" // executor

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
	t_data	*d;
	// SACAR CMD PARA LIBERAR

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
	//ft_printf("exit\n");
	//good_exit(d);
	return (0);
}
