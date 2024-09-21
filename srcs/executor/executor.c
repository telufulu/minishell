/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:06:58 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/21 18:34:46 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // t_data, access
#include "executor.h" // t_cmd
#include "libft.h" // ft_calloc, ft_error, strrerror
#include "token.h" // PIPE, INFD, OUTFD
#include <fcntl.h> // open

void	executor(t_data *d)
{
	t_cmd	**c;

	ft_printf("tokens: %s\n", d->tokens);
	c = create_cmds(count_cmds(d->tokens), d);
	if (c[0]->path)
		ft_printf("%s\n", c[0]->path);
	//ft_free_matrix((void **)c);
}
