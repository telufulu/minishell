/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:22:30 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/06 17:30:48 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	// t_data
#include "lexer.h"		// t_token, num_cmd
#include "libft.h"		// ft_printf

// si ls | wc |  se abre >
t_cmd	*main_lexer(t_data *d)
{
	size_t	n_cmd;
	size_t	i;
	t_cmd	*last;

	i = 0;
	n_cmd = num_cmd(d->tokens);
	while (i < n_cmd)
	{
		last = add_cmd(d);
		last->index = i++;
	}
	return (NULL);
}
