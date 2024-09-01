/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:15 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/01 10:56:42 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**false_tokenizer(char *input)
{
	char **res;
	
	res = ft_split(input, ' ');
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_cmd	*cmd;	

	if (argv)
		argc = argc + 3;
	//init data struct and create enviroment
	data = init_env(envp);
	if (!data)
		exit_shell(EXIT_FAILURE);
	data->input = "";
	while (data->input && !ft_strnstr(data->input, "exit", 4))
	{
		data->input = readline(PROMPT);
		add_history(data->input);
		// lexer (returns string with all the commands)
		if (!data->tokens)
			exit_shell(EXIT_FAILURE);
		// parser 

		//free(data->tokens);
		//data->tokens = NULL;

		// executer
		if (cmd)
			free(data->input);
		else
			free(data->input);
	}
	return (0);
}
