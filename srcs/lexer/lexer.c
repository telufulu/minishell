/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:22:30 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/09 15:40:03 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, ft_shell_error
#include "lexer.h"		// t_token, num_cmd, get_cmd, get_path
#include "libft.h"		// ft_printf
#include "parser.h"		// PIPE

t_token	**next_cmd(t_token **tokens)
{
	while (tokens && *tokens && (*tokens))
	{
		if ((*tokens)->type == PIPE)
			return (tokens + 1);
		++tokens;
	}
	return (NULL);
}

// si "ls | wc | " se abre >
t_cmd	*main_lexer(t_data *d, t_token **tokens)
{
	size_t	n_cmd;
	size_t	i;
	char	**sp_path;
	t_cmd	*last;

	i = 0;
	last = NULL;
	n_cmd = num_cmd(d->tokens);
	sp_path = split_path(d->env);
	while (i < n_cmd && tokens)
	{
		add_cmd(d);
		last = last_cmd(d->cmd);
		last->cmd = get_cmd(tokens);
		last->path = get_path(sp_path, last->cmd);
		//last->infd = open_infd(); 
		last->index = i++;
		ft_printf("cmd: %s\n", last->cmd);
		ft_printf("path: %s\n", last->path);
		tokens = next_cmd(tokens);//pointer moves to the next token before PIPE
	}
	ft_free_matrix((void **)sp_path);
	return (NULL);
}
