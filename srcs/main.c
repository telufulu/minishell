/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:21:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/01 13:33:05 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void	check_term(void)
{
	char	*tty;

	if (isatty(STDIN_FILENO))
	{
		tty = ttyname(STDIN_FILENO);
		if (getenv("SHELL"))
			printf("Shell: %s\n", getenv("SHELL"));
		if (getenv("USER"))
			printf("User: %s ", getenv("USER"));
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

int	main(void)
{
	t_data	d;
	int		i;

	d.exit_status = 0;
	check_term();
	while (1)
	{
		d.input = readline("minishell> ");
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
				i = 0;
				while (d.tokens[i])
					printf("input: %s\n", d.tokens[i++]);
				free_array(d.tokens);
			}
		}
		free(d.input);
	}
	return (0);
}
