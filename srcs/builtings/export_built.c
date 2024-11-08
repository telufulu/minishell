/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:17 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/08 17:00:47 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"		// t_cmd
#include "libft.h"		// ft_strncmp, ft_strlen, t_bool, TRUE, FALSE
#include "minishell.h"	// strerror
#include "builtings.h"	// env_built

int	export_built(t_cmd *c, char **env)
{
	if (c && env)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
