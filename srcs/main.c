/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/01 19:03:28 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_term(char **envp)
{
	char	*tty;

	if (isatty(STDIN_FILENO) && envp)
	{
		tty = ttyname(STDIN_FILENO);
		if (get_env(envp, "SHELL"))
			printf("Shell: %s\n", get_env(envp, "SHELL"));
		if (get_env(envp, "USER"))
			printf("User: %s ", get_env(envp, "USER"));
		if (tty)
			printf("is succesfully logged on %s\n", tty);
		else
			perror("ttyname");
	}
	else
	{
		printf("Error: stdin is not a terminal - %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	d;

	d.env = init_env(envp);
	if (!d.env)
		return (0);
	d.exit_status = 0;
	check_term(d.env);
	while (argc && argv)
	{
		d.input = readline(PROMPT);
		if (d.input == NULL || ft_strncmp(d.input, "exit", 5) == 0)
		{
			if (d.input)
				free(d.input);
			break ;
		}
		if (ft_strlen(d.input) > 0)
		{
			add_history(d.input);
			d.tokens = main_parser(d.input, d.exit_status);
			if (d.tokens)
			{
				ft_print_matrix(d.tokens, 1);
				ft_free_matrix((void **)d.tokens);
			}
		}
		free(d.input);
	}
	return (0);
}
