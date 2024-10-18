/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:06:38 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/18 02:21:40 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"	// t_cmd

int	ls_built(t_cmd *c, char **env)
{
	if (env)
		return (printf("%p\n", c));
	return (0);
}
