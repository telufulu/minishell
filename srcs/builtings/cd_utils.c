/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:51:18 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/07 19:58:01 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"		// t_cmd
#include "builting.h"	// new_var, get_var
#include "libft.h"		// ft_matrixjoin

void	cd_export(t_cmd *c, char *key)
{
	char	*var;

	c->data->env = ft_matrixjoin(c->data->env, get_var(key));
	free(var);
}
