/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:22:30 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/13 17:10:59 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data, ft_shell_error
#include "lexer.h"		// t_token, num_cmd, get_cmd, get_path
#include "libft.h"		// ft_printf
#include "parser.h"		// PIPE

//pointer moves to the next token before PIPE
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

void	main_lexer(t_data *d, t_token **tokens)
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
		last = add_cmd(d);
		last->cmd = get_cmd(tokens);
		last->path = get_path(sp_path, last->cmd);
		last->infd = get_fd(tokens, REDIRECT_IN);
		last->outfd = get_fd(tokens, REDIRECT_OUT);
		last->index = i++;
		last->input = tokens;
		tokens = next_cmd(tokens);
	}
	ft_free_matrix((void **)sp_path);
}
