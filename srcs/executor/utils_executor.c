/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:42:54 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/08 18:43:35 by augustindelab    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"	// RD, WR
#include <fcntl.h>		// open
#include "parser.h"		// t_token, t_type
#include "libft.h"		// get_next_line, ft_putstr_fd

void	write_fd(int old, int new)
{
	char	*str;

	str = get_next_line(old);
	while (str)
	{
		ft_putstr_fd(str, new);
		free(str);
		str = get_next_line(old);
	}
}

void	restore_terminal_settings(void)
{
	struct termios	termios_p;

	check_error(tcgetattr(STDIN_FILENO, &termios_p), "tcgetattr");
	termios_p.c_lflag |= ECHOCTL;
	check_error(tcsetattr(STDIN_FILENO, TCSANOW, &termios_p), "tcsetattr");
}
