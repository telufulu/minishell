/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:26:35 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/05 19:27:35 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	is_outfl(char **res, char params, int i)
{
	if (params == '<')
	{
		*res[i + 1] = OUTFL;
		*res[i] = OPER;
	}
	else
		*res[i] = 42;
}

void	is_infl(char **res, char params, int i)
{
	if (params && params == '<')
	{
		*res[i] = INFL;
		*res[i + 1] = OPER;
	}
	else
		*res[i] = 42;
}

